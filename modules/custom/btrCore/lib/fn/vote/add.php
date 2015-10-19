<?php
namespace BTranslator;
use \btr;

/**
 * Add a vote for the given translation from the current user.
 * Make sure that any previous vote is cleaned first
 * (don't allow multiple votes for the same translation).
 *
 * @param $tguid
 *   ID of the translation.
 *
 * @param $uid (optional)
 *   ID of the user.
 *
 * @return
 *   ID of the new vote, or NULL.
 */
function vote_add($tguid, $uid = NULL) {
  // Don't add a vote for anonymous and admin users.
  $uid = btr::user_check($uid);
  if ($uid == 1)  return NULL;

  // Fetch the translation details from the DB.
  $sql = 'SELECT * FROM {btr_translations} WHERE tguid = :tguid';
  $trans = btr::db_query($sql, [':tguid' => $tguid])->fetchObject();

  // If there is no such translation, return NULL.
  if (empty($trans)) {
    $msg = t('The given translation does not exist.');
    btr::messages($msg, 'error');
    return NULL;
  }

  // Get the mail and lng of the user.
  $account = user_load($uid);
  $umail = $account->init;    // email used for registration
  $ulng = $account->translation_lng;

  // Make sure that the language of the user matches the language of the translation.
  if ($ulng != $trans->lng and !user_access('btranslator-admin', $account)) {
    $msg = t('You cannot vote the translations of language <strong>!lng</strong>', ['!lng' => $trans->lng]);
    btr::messages($msg, 'error');
    return NULL;
  }

  // Clean any previous vote.
  include_once(dirname(__FILE__) . '/del_previous.php');
  $nr = _vote_del_previous($tguid, $umail, $trans->sguid, $trans->lng);

  // Add the vote.
  $vid = btr::db_insert('btr_votes')
    ->fields([
        'tguid' => $tguid,
        'umail' => $umail,
        'ulng' => $ulng,
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
      ])
    ->execute();

  // Update vote count of the translation.
  $sql = 'SELECT COUNT(*) FROM {btr_votes} WHERE tguid = :tguid';
  $count = btr::db_query($sql, [':tguid' => $tguid])->fetchField();
  btr::db_update('btr_translations')
    ->fields(['count' => $count])
    ->condition('tguid', $tguid)
    ->execute();

  return $vid;
}
