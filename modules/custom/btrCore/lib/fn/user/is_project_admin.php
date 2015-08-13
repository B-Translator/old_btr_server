<?php
/**
 * @file
 * Definition of function user_is_project_admin().
 */

namespace BTranslator;

/**
 * Return TRUE if the current user can administrate the given project.
 */
function user_is_project_admin($origin, $project) {
  // If user has global admin permission,
  // he can administrate this project as well.
  if (user_access('btranslator-admin'))  return TRUE;

  // Check whether the user is an admin of the given project.
  if (in_array("$origin/$project", $GLOBALS['user']->admin_projects)) return TRUE;

  // Otherwise he cannot administrate.
  return FALSE;
}
