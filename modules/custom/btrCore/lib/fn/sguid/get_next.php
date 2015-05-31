<?php
/**
 * @file
 * Get another sguid.
 */

namespace BTranslator;
use \btr;

/**
 * Return a sguid from the strings that should be reviewed.
 *
 * @param $uid
 *   Select according to the preferencies of this user.
 *   If no $uid is given, then the current user is assumed.
 *
 * @param $projects
 *   Array of projects to restrict selection.
 *
 * @return
 *   The sguid of another string and an array of messages.
 */
function sguid_get_next($uid =NULL, $projects =NULL) {
  // get the string-order preference for the user
  if ($uid == NULL)  { $uid = $GLOBALS['user']->uid; }
  $account = user_load($uid);
  $string_order = $account->string_order;

  // select the string according to the string-order preference
  if ($string_order == 'sequential') {
      return(sguid_get_sequential($uid));
  }
  else {  // $string_order == 'random'
      $sguid = btr::sguid_get_random($uid, $projects);
      return array($sguid, array());
  }
}

/**
 * Return a sequential sguid from the preferred projects of the user.
 *
 * @param $uid
 *   The user whose preferencies will be used.
 *   If no $uid is given, then the current user is assumed.
 *
 * @return
 *   The sguid of the next string in the PO file(s) and an array of messages.
 */
function sguid_get_sequential($uid =NULL) {

  // get the sequential data
  if ($uid == NULL)  { $uid = $GLOBALS['user']->uid; }
  $account = user_load($uid);
  $sequential = $account->data_sequential;

  // if sequential data are not set, then just return a random sguid
  if ($sequential == NULL) {
    $msg = t("It seems that there is something wrong with your preferences. Please <a href='@edit-profile'>check your profile</a>.",
           array('@edit-profile' => "/user/$uid/edit-profile"));
    return array(NULL, array(array($msg, 'warning')));
  }

  $lid = $sequential->lid;
  $idx = $sequential->idx;
  $proj = $sequential->projects[$idx];

  // get the id of the next string location
  $lid++;
  if ($lid > $proj->lmax) {
    $idx++;
    if ($idx >= sizeof($sequential->projects)) {
      $msg = t("You have reached the end of the preferred projects. Please <a href='@edit-profile'>visit your profile</a> and modify them.",
             array('@edit-profile' => "/user/$uid/edit-profile"));
      return array(NULL, array(array($msg, 'status')));
    }
    $proj = $sequential->projects[$idx];
    $lid = $proj->lmin;
  }

  // save the new index of the object $sequential
  $sequential->lid = $lid;
  $sequential->idx = $idx;
  $edit['data_sequential'] = $sequential;
  $edit['skip_presave'] = TRUE;
  user_save($account, $edit);

  // get and return the sguid
  $query = 'SELECT sguid FROM {btr_locations} WHERE lid=:lid';
  $args = array(':lid' => $lid);
  $sguid = btr::db_query($query, $args)->fetchField();
  return array($sguid, array());
}
