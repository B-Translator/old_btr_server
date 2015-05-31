<?php
namespace BTranslator;
use \btr;

/**
 * Add a new translation to a source string.
 *
 * @param $sguid
 *   The string ID for which a new translation should be added.
 * @param $lng
 *   The language (code) of the new translation.
 * @param $translation
 *   The new translation as a string. If the string has plural
 *   version(s) as well, they are concatenated with NULL bytes ("\0")
 *   between them.
 * @return
 *   array($tguid, $messages)
 *   - $tguid is the ID of the new translation,
 *               or NULL if no translation was added
 *   - $messages is an array of notification messages; each notification
 *               message is an array of a message and a type, where
 *               type can be one of 'status', 'warning', 'error'
 */
function translation_add($sguid, $lng, $translation) {
  // Check access permissions.
  if (!user_access('btranslator-suggest')) {
    $msg = t('You do not have enough rights for making suggestions!');
    return array(NULL, array(array($msg, 'error')));
  }

  // Make sure that the current user can make
  // translations for the given language.
  $user = user_load($GLOBALS['user']->uid);
  if ($lng != $user->translation_lng) {
    $msg = t('You cannot give translations for the language <strong>!lng</strong>', array('!lng' => $lng));
    return array(NULL, array(array($msg, 'error')));
  }

  // Don't add empty translations.
  $translation = btr::string_pack($translation);
  $translation = str_replace(t('<New translation>'), '', $translation);
  if (trim($translation) == '')  {
    $msg = t('The given translation is empty.');
    return array(NULL, array(array($msg, 'warning')));
  }

  // Make spacing and newlines the same in translation as in the source.
  $string = btr::string_get($sguid);
  $matches = array();
  preg_match("/^(\s*).*\S(\s*)\$/s", $string, $matches);
  $translation = $matches[1] . trim($translation) . $matches[2];

  // Look for an existing translation, if any.
  $tguid = sha1($translation . $lng . $sguid);
  $existing = btr::translation_get($tguid);

  // If this translation already exists, there is nothing to be added.
  if (!empty($existing))  {
    $msg = t('The given translation already exists.');
    return array(NULL, array(array($msg, 'warning')));
  }

  // Get the email of the author of the translation.
  $umail = $user->init;    // email used for registration

  // Insert the new suggestion.
  btr_insert('btr_translations')
    ->fields(array(
        'sguid' => $sguid,
        'lng' => $lng,
        'translation' => $translation,
        'tguid' => $tguid,
        'count' => 1,
        'umail' => $umail,
        'ulng' => $lng,
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();

  // If there is another translation for the same string, by the same user,
  // the new translation should replace the old one. This is useful when
  // the user wants to correct the translation, but it limits the user to
  // only one suggested translation per string.
  // However, translators (with the 'btranslator-import' access right)
  // do not have this limitation and can suggest more than one translation
  // for the same string.
  // The same is applied for the users with admin or moderator role in the
  // project of the string.
  if (!user_access('btranslator-import')
    and !btr::utils_user_has_project_role('admin', $sguid)
    and !btr::utils_user_has_project_role('moderator', $sguid))
    {
      _remove_old_translation($sguid, $lng, $umail, $tguid);
    }

  // Add also a vote for the new translation.
  list($vid, $messages) = btr::vote_add($tguid);

  // Notify previous voters of this string that a new translation has been
  // suggested. Maybe they would like to review it and change their vote.
  _notify_voters_on_new_translation($sguid, $lng, $tguid, $string, $translation);

  return array($tguid, $messages);
}


/**
 * If there is another translation for the same string, by the same user,
 * the new translation should replace the old one. This is useful when
 * the user wants to correct the translation, but it limits the user to
 * only one suggested translation per string.
 *
 * @param $sguid
 *   Id of the string being translated.
 * @param $lng
 *   Language of translation.
 * @param $umail
 *   Email that identifies the user who made the translation.
 * @param $tguid
 *   Id of the new translation.
 */
function _remove_old_translation($sguid, $lng, $umail, $tguid) {
  // Get the old translation (if any).
  $query = 'SELECT tguid, translation
            FROM {btr_translations}
            WHERE sguid = :sguid AND lng = :lng
              AND umail = :umail AND ulng = :ulng
              AND tguid != :tguid';
  $args = array(
    ':sguid' => $sguid,
    ':lng' => $lng,
    ':umail' => $umail,
    ':ulng' => $lng,
    ':tguid' => $tguid);
  $old_trans = btr_query($query, $args)->fetchObject();
  if (!$old_trans)  return;  // if there is no old translation, we are done

  // Copy to the trash table the old translation.
  $query = btr_select('btr_translations', 't')
    ->fields('t', array('sguid', 'lng', 'translation', 'tguid', 'count', 'umail', 'ulng', 'time', 'active'))
    ->condition('tguid', $old_trans->tguid);
  $query->addExpression(':d_umail', 'd_umail', array(':d_umail' => $umail));
  $query->addExpression(':d_ulng', 'd_ulng', array(':d_ulng' => $lng));
  $query->addExpression('NOW()', 'd_time');
  btr_insert('btr_translations_trash')->from($query)->execute();

  // Remove the old translation.
  btr_delete('btr_translations')
    ->condition('tguid', $old_trans->tguid)
    ->execute();

  // Get the votes of the old translation.
  $query = "SELECT v.tguid, v.time, u.umail, u.ulng, u.uid,
                   u.name AS user_name, u.status AS user_status
            FROM {btr_votes} v
            LEFT JOIN {btr_users} u ON (u.umail = v.umail AND u.ulng = v.ulng)
            WHERE v.tguid = :tguid AND v.umail != :umail";
  $args = array(':tguid' => $old_trans->tguid, ':umail' => $umail);
  $votes = btr_query($query, $args)->fetchAll();

  // Insert to the trash table the votes that will be deleted.
  $query = btr_select('btr_votes', 'v')
    ->fields('v', array('vid', 'tguid', 'umail', 'ulng', 'time', 'active'))
    ->condition('tguid', $old_trans->tguid);
  $query->addExpression('NOW()', 'd_time');
  btr_insert('btr_votes_trash')->from($query)->execute();

  // Delete the votes belonging to the old translation.
  btr_delete('btr_votes')->condition('tguid', $old_trans->tguid)->execute();

  // Associate these votes to the new translation.
  $notification_list = array();
  foreach ($votes as $vote) {
    // Associate the vote to the new translation.
    btr_insert('btr_votes')
      ->fields(array(
          'tguid' => $tguid,
          'umail' => $vote->umail,
          'ulng' => $vote->ulng,
          'time' => $vote->time,
        ))
      ->execute();

    if ($vote->user_status != 1)  continue;   // skip non-active voters

    // Add voter to the notification list.
    $notification_list[$uid] = array(
      'uid' => $uid,
      'name' => $vote->user_name,
      'umail' => $vote->umail,
    );
  }

  _notify_voters_on_translation_change($notification_list, $sguid, $old_trans->translation, $tguid);
}

/**
 * Notify the voters of a translation that the author has changed
 * the translation and their votes count now for the new translation.
 */
function _notify_voters_on_translation_change($voters, $sguid, $old_translation, $tguid) {

  if (empty($voters))  return;

  $string = btr::string_get($sguid);
  $new_translation = btr::translation_get($tguid);

  $notifications = array();
  foreach ($voters as $uid => $voter) {
    $notification = array(
      'type' => 'notify-voter-on-translation-change',
      'uid' => $voter['uid'],
      'username' => $voter['name'],
      'recipient' => $voter['name'] . ' <' . $voter['umail'] . '>',
      'sguid' => $sguid,
      'string' => $string,
      'old_translation' => $old_translation,
      'new_translation' => $new_translation,
    );
    $notifications[] = $notification;
  }

  btr::queue('notifications', $notifications);
}

/**
 * Notify the previous voters of a string that a new translation has been
 * submitted. Maybe they would like to review it and change their vote.
 */
function _notify_voters_on_new_translation($sguid, $lng, $tguid, $string, $translation) {

  $query = "SELECT u.umail, u.ulng, u.uid, u.name, u.status, t.translation
            FROM {btr_translations} t
            LEFT JOIN {btr_votes} v ON (v.tguid = t.tguid)
            LEFT JOIN {btr_users} u ON (u.umail = v.umail AND u.ulng = v.ulng)
            WHERE t.sguid = :sguid AND t.lng = :lng AND t.tguid != :tguid";
  $args = array(':sguid' => $sguid, ':lng' => $lng, ':tguid' => $tguid);
  $voters = btr_query($query, $args)->fetchAll();

  if (empty($voters))  return;

  $notifications = array();
  foreach ($voters as $voter) {
    $notification = array(
      'type' => 'notify-voter-on-new-translation',
      'uid' => $voter->uid,
      'username' => $voter->name,
      'recipient' => $voter->name . ' <' . $voter->umail . '>',
      'sguid' => $sguid,
      'string' => $string,
      'voted_translation' => $voter->translation,
      'new_translation' => $translation,
    );
    $notifications[] = $notification;
  }

  btr::queue('notifications', $notifications);
}
