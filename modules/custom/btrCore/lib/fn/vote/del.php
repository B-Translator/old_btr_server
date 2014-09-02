<?php
namespace BTranslator;

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
function vote_del($tguid) {
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
  $trans = btr_query(
    'SELECT * FROM {btr_translations} WHERE tguid = :tguid',
    array(':tguid' => $tguid))
    ->fetchObject();

  // If there is no such translation, return NULL.
  if (empty($trans)) {
    $msg = t('The given translation does not exist.');
    return array(array($msg, 'error'));
  }

  // Clean any previous vote.
  include_once(dirname(__FILE__) . '/del_previous.php');
  $nr = _vote_del_previous($tguid, $umail, $trans->sguid, $trans->lng);

  return array();
}
