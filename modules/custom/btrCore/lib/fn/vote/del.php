<?php
namespace BTranslator;
use \btr;

/**
 * Delete a vote for the given translation from the given user.
 *
 * @param $tguid
 *   ID of the translation.
 *
 * @param $uid
 *   ID of the user.
 */
function vote_del($tguid, $uid = NULL) {
  // Get the account of the user.
  if ($uid === NULL)  $uid = $GLOBALS['user']->uid;
  $account = user_load($uid);

  // Check access permissions.
  if (!user_access('btranslator-vote', $account)
    and !user_access('btranslator-admin', $account))
    {
      $msg = t('No rights for deleting votes!');
      btr::messages($msg, 'error');
      return;
    }

  // Fetch the translation details from the DB.
  $trans = btr::db_query(
    'SELECT * FROM {btr_translations} WHERE tguid = :tguid',
    [':tguid' => $tguid])
    ->fetchObject();

  // If there is no such translation, return NULL.
  if (empty($trans)) {
    $msg = t('Translation does not exist.');
    btr::messages($msg, 'error');
    return;
  }

  // Clean any previous vote.
  $umail = $account->init;    // email used for registration
  include_once(dirname(__FILE__) . '/del_previous.php');
  $nr = _vote_del_previous($tguid, $umail, $trans->sguid, $trans->lng);
}
