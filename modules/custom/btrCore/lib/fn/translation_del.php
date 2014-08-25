<?php
namespace BTranslator;

/**
 * Delete the translation with the given id and any related votes.
 *
 * @param $tguid
 *   ID of the translation.
 *
 * @return
 *   Array of notification messages; each notification message
 *   is an array of a message and a type, where type can be
 *   one of 'status', 'warning', 'error'
 */
function translation_del($tguid) {
  // Get the mail and lng of the user.
  $user = user_load($GLOBALS['user']->uid);
  $umail = $user->init;    // email used for registration
  $ulng = $user->translation_lng;

  // Before deleting, get the author and voters (for notifications).
  list($author, $voters) = _get_author_and_voters($tguid);

  // Check that the current user has the right to delete translations.
  $is_own = ($umail == $author->umail);
  if (!$is_own and !user_access('btranslator-resolve')) {
    $msg = t('You are not allowed to delete this translation!');
    return array(array($msg, 'error'));
  }

  // Copy to the trash table the translation that will be deleted.
  $query = btr_select('btr_translations', 't')
    ->fields('t', array('sguid', 'lng', 'translation', 'tguid', 'count', 'umail', 'ulng', 'time', 'active'))
    ->condition('tguid', $tguid);
  $query->addExpression(':d_umail', 'd_umail', array(':d_umail' => $umail));
  $query->addExpression(':d_ulng', 'd_ulng', array(':d_ulng' => $ulng));
  $query->addExpression('NOW()', 'd_time');
  btr_insert('btr_translations_trash')->from($query)->execute();

  // Copy to the trash table the votes that will be deleted.
  $query = btr_select('btr_votes', 'v')
    ->fields('v', array('vid', 'tguid', 'umail', 'ulng', 'time', 'active'))
    ->condition('tguid', $tguid);
  $query->addExpression('NOW()', 'd_time');
  btr_insert('btr_votes_trash')->from($query)->execute();

  // Delete the translation and any votes related to it.
  btr_delete('btr_translations')->condition('tguid', $tguid)->execute();
  btr_delete('btr_votes')->condition('tguid', $tguid)->execute();

  // Notify the author of a translation and its voters
  // that it has been deleted.
  _notify_voters_on_translation_del($tguid, $author, $voters);

  return array();
}

/**
 * Before deleting a translation, get the author and voters (for notifications).
 */
function _get_author_and_voters($tguid) {
  $get_author =
    "SELECT u.uid, u.name, u.umail
     FROM {btr_translations} t
     LEFT JOIN {btr_users} u
         ON (u.umail = t.umail AND u.ulng = t.ulng)
     WHERE t.tguid = :tguid";

  $get_voters =
    "SELECT u.uid, u.name, u.umail
     FROM {btr_votes} v
     LEFT JOIN {btr_users} u
         ON (u.umail = v.umail AND u.ulng = v.ulng)
     WHERE v.tguid = :tguid";

  $args = array(':tguid' => $tguid);

  $author = btr_query($get_author, $args)->fetchObject();
  $voters = btr_query($get_voters, $args)->fetchAll();

  return array($author, $voters);
}


/**
 * Notify the author of a translation and its voters
 * that it has been deleted.
 */
function _notify_voters_on_translation_del($tguid, $author, $voters) {
  // get the sguid, string and translation
  $sql = 'SELECT sguid FROM {btr_translations} WHERE tguid = :tguid';
  $args = array(':tguid' => $tguid);
  $sguid = btr_query($sql, $args)->fetchField();
  $string = btr_get_string($sguid);
  $translation = btr_get_translation($tguid);

  $notifications = array();

  // Notify the author of the translation about the deletion.
  $notification = array(
    'type' => 'notify-author-on-translation-deletion',
    'uid' => $author->uid,
    'username' => $author->name,
    'recipient' => $author->name . ' <' . $author->umail . '>',
    'sguid' => $sguid,
    'string' => $string,
    'translation' => $translation,
  );
  $notifications[] = $notification;

  // Notify the voters of the translation as well.
  foreach ($voters as $voter) {
    if ($voter->name == $author->name)  continue;  // don't send a second message to the author
    $notification = array(
      'type' => 'notify-voter-on-translation-deletion',
      'uid' => $voter->uid,
      'username' => $voter->name,
      'recipient' => $voter->name . ' <' . $voter->umail . '>',
      'sguid' => $sguid,
      'string' => $string,
      'translation' => $translation,
    );
    $notifications[] = $notification;
  }

  btr_queue_notifications($notifications);
}
