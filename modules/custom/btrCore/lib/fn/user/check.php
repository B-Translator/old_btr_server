<?php
/**
 * @file
 * Function user_check()
 */

namespace BTranslator;

/**
 * Check the give $uid and make sure that it has a correct value.
 */
function user_check($uid = NULL) {
  // Get the current user, if no user is given.
  if ($uid == NULL)  $uid = $GLOBALS['user']->uid;

  // Make sure to use admin instead of anonymous user (for drush commands).
  if ($uid == 0)  $uid = 1;

  return $uid;
}
