<?php
/**
 * @file
 * Definition of function user_is_project_admin().
 */

namespace BTranslator;

/**
 * Return TRUE if the user can administrate the given project.
 */
function user_is_project_admin($origin, $project, $lng = NULL, $uid = NULL) {
  // Get the user account.
  if ($uid === NULL)  $uid = $GLOBALS['user']->uid;
  $account = user_load($uid);

  // If user has global admin permission,
  // he can administrate this project as well.
  if (user_access('btranslator-admin', $account))  return TRUE;

  // Check that the project language matches translation_lng of the user.
  if ($lng !== NULL and $lng != $account->translation_lng) return FALSE;

  // Check whether the user is an admin of the given project.
  if (in_array("$origin/$project", $account->admin_projects)) return TRUE;

  // Otherwise he cannot administrate.
  return FALSE;
}
