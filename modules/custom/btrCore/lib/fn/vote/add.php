<?php
namespace BTranslator;

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
function vote_add($tguid) {
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
  include_once(dirname(__FILE__) . '/del_previous.php');
  $nr = _vote_del_previous($tguid, $umail, $trans->sguid, $trans->lng);

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
