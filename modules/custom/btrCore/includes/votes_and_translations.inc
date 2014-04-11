<?php

/**
 * Add a vote for the given translation from the current user.
 * Make sure that any previous vote is cleaned first
 * (don't allow multiple votes for the same translation).
 *
 * @param $tguid
 *   ID of the translation.
 *
 * @return
 *   array($vid, $messages)
 *   - $vid is the ID of the new vote, or NULL
 *   - $messages is an array of notification messages; each notification
 *               message is an array of a message and a type, where
 *               type can be one of 'status', 'warning', 'error'
 */
function btr_add_vote($tguid) {
  // Check access permissions.
  if (!user_access('btranslator-vote')) {
    $msg = t('You do not have enough rights for submitting votes!');
    return array(NULL, array(array($msg, 'error')));
  }

  // Fetch the translation details from the DB.
  $sql = 'SELECT * FROM {btr_translations} WHERE tguid = :tguid';
  $args = array(':tguid' => $tguid);
  $trans = btr_query($sql, $args)->fetchObject();

  // If there is no such translation, return NULL.
  if (empty($trans)) {
    $msg = t('The given translation does not exist.');
    return array(NULL, array(array($msg, 'error')));
  }

  // Get the mail and lng of the user.
  $user = user_load($GLOBALS['user']->uid);
  $umail = $user->init;    // email used for registration
  $ulng = $user->translation_lng;

  // Make sure that the language of the user
  // matches the language of the translation.
  if ($ulng != $trans->lng) {
    $msg = t('You cannot vote the translations of language <strong>!lng</strong>', array('!lng' => $trans->lng));
    return array(NULL, array(array($msg, 'error')));
  }

  // Clean any previous vote.
  $nr = _btr_clean_previous_votes($tguid, $umail, $trans->sguid, $trans->lng);

  // Add the vote.
  $vid = btr_insert('btr_votes')
    ->fields(array(
        'tguid' => $tguid,
        'umail' => $umail,
        'ulng' => $ulng,
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();

  // Update vote count of the translation.
  $sql = 'SELECT COUNT(*) FROM {btr_votes} WHERE tguid = :tguid';
  $count = btr_query($sql, $args)->fetchField();
  btr_update('btr_translations')
    ->fields(array('count' => $count))
    ->condition('tguid', $tguid)
    ->execute();

  return array($vid, array());
}


/**
 * Delete a vote for the given translation from the current user.
 *
 * This is useful only when the voting mode is 'multiple'.
 *
 * @param $tguid
 *   ID of the translation.
 *
 * @return
 *   array($messages)
 *     $messages is an array of notification messages; each notification
 *     message is an array of a message and a type, where type can be
 *     one of 'status', 'warning', 'error'
 */
function btr_del_vote($tguid) {
  // Check access permissions.
  if (!user_access('btranslator-vote')) {
    $msg = t('You do not have enough rights for submitting votes!');
    return array(array($msg, 'error'));
  }

  // Get the mail and lng of the user.
  $user = user_load($GLOBALS['user']->uid);
  $umail = $user->init;    // email used for registration
  $ulng = $user->translation_lng;

  // Fetch the translation details from the DB.
  $sql = 'SELECT * FROM {btr_translations} WHERE tguid = :tguid';
  $args = array(':tguid' => $tguid);
  $trans = btr_query($sql, $args)->fetchObject();

  // If there is no such translation, return NULL.
  if (empty($trans)) {
    $msg = t('The given translation does not exist.');
    return array(array($msg, 'error'));
  }

  // Clean any previous vote.
  $nr = _btr_clean_previous_votes($tguid, $umail, $trans->sguid, $trans->lng);

  return array();
}


/**
 * Clean any previous vote by this user for this translation.
 *
 * This depends on the voting mode option (set by the admin).
 * If the voting mode is 'single', then the user can select
 * only one translation for a given string (at most one vote
 * per string).
 * If the voting mode is 'multiple', then the user can approve
 * several translations for a string (at most one vote per
 * translation).
 *
 * @param $tguid
 *   ID of the translation.
 *
 * @param $umail
 *   The mail of the user.
 *
 * @param $sguid
 *   ID of the source string.
 *
 * @param $lng
 *   Language code of the translation.
 *
 * @return
 *   Number of previous votes that were deleted.
 *   (Normally should be 0, but can also be 1. If it is >1,
 *   something must be wrong.)
 */
function _btr_clean_previous_votes($tguid, $umail, $sguid, $lng) {
  // Get the voting mode.
  $voting_mode = variable_get('btr_voting_mode', 'single');

  $arr_tguid = array();
  if ($voting_mode == 'multiple') {
    $arr_tguid = array($tguid);
  }
  else { // ($voting_mode == 'single')
    // Get the other sibling translations (translations of the same
    // string and the same language) which the user has voted.
    $sql = '
      SELECT DISTINCT t.tguid FROM {btr_translations} t
      LEFT JOIN {btr_votes} v ON (v.tguid = t.tguid)
      WHERE t.sguid = :sguid AND t.lng = :lng AND v.umail = :umail AND v.ulng = :ulng
    ';
    $params = array(':sguid' => $sguid, ':lng' => $lng, ':umail' => $umail, ':ulng' => $lng);
    $arr_tguid = btr_query($sql, $params)->fetchCol();
  }

  if (empty($arr_tguid))  return 0;

  // Insert to the trash table the votes that will be removed.
  $query = btr_select('btr_votes', 'v')
    ->fields('v', array('vid', 'tguid', 'umail', 'ulng', 'time', 'active'))
    ->condition('umail', $umail)
    ->condition('ulng', $lng)
    ->condition('tguid', $arr_tguid, 'IN');
  $query->addExpression('NOW()', 'd_time');
  btr_insert('btr_votes_trash')->from($query)->execute();

  // Remove any votes by the user for each translation in $arr_tguid.
  $num_deleted = btr_delete('btr_votes')
    ->condition('umail', $umail)
    ->condition('ulng', $lng)
    ->condition('tguid', $arr_tguid, 'IN')
    ->execute();

  // Decrement the vote count for each translation in $arr_tguid.
  $num_updated = btr_update('btr_translations')
    ->expression('count', 'count - 1')
    ->condition('tguid', $arr_tguid, 'IN')
    ->execute();

  return $num_deleted;
}


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
function btr_add_translation($sguid, $lng, $translation) {
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
  $translation = btr_pack_string($translation);
  $translation = str_replace(t('<New translation>'), '', $translation);
  if (trim($translation) == '')  {
    $msg = t('The given translation is empty.');
    return array(NULL, array(array($msg, 'warning')));
  }

  // Make spacing and newlines the same in translation as in the source.
  $string = btr_get_string($sguid);
  $matches = array();
  preg_match("/^(\s*).*\S(\s*)\$/s", $string, $matches);
  $translation = $matches[1] . trim($translation) . $matches[2];

  // Look for an existing translation, if any.
  $tguid = sha1($translation . $lng . $sguid);
  $existing = btr_get_translation($tguid);

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
  if (! user_access('btranslator-import')) {
    _btr_remove_old_translation($sguid, $lng, $umail, $tguid);
  }

  // Add also a vote for the new translation.
  list($vid, $messages) = btr_add_vote($tguid);

  // Notify previous voters of this string that a new translation has been
  // suggested. Maybe they would like to review it and change their vote.
  _btr_notify_voters_on_new_translation($sguid, $lng, $tguid, $string, $translation);

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
function _btr_remove_old_translation($sguid, $lng, $umail, $tguid) {
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

  _btr_notify_voters_on_translation_change($notification_list, $sguid, $old_trans->translation, $tguid);
}

/**
 * Notify the voters of a translation that the author has changed
 * the translation and their votes count now for the new translation.
 */
function _btr_notify_voters_on_translation_change($voters, $sguid, $old_translation, $tguid) {

  if (empty($voters))  return;

  $string = btr_get_string($sguid);
  $new_translation = btr_get_translation($tguid);

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

  btr_queue_notifications($notifications);
}

/**
 * Notify the previous voters of a string that a new translation has been
 * submitted. Maybe they would like to review it and change their vote.
 */
function _btr_notify_voters_on_new_translation($sguid, $lng, $tguid, $string, $translation) {

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

  btr_queue_notifications($notifications);
}


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
function btr_del_translation($tguid) {
  // Get the mail and lng of the user.
  $user = user_load($GLOBALS['user']->uid);
  $umail = $user->init;    // email used for registration
  $ulng = $user->translation_lng;

  // Before deleting, get the author and voters (for notifications).
  list($author, $voters) = _btr_get_author_and_voters($tguid);

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
  _btr_notify_voters_on_translation_del($tguid, $author, $voters);

  return array();
}

/**
 * Before deleting a translation, get the author and voters (for notifications).
 */
function _btr_get_author_and_voters($tguid) {
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
function _btr_notify_voters_on_translation_del($tguid, $author, $voters) {
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
