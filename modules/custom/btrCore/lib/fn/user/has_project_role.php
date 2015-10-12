<?php
/**
 * @file
 * Function: user_has_project_role()
 */

namespace BTranslator;
use \btr;

/**
 * Check whether the user has a role on the projects of the given string.
 *
 * @param $role
 *   The role to be checked (admin|moderator).
 *
 * @param $sguid
 *   The id of the string.
 *
 * @param $uid (optional)
 *   The id of the user.
 *
 * @return
 *   TRUE if the string belongs to projects where user has the role.
 */
function user_has_project_role($role, $sguid, $uid = NULL) {
  if ($uid === NULL)  $uid = $GLOBALS['user']->uid;

  // Get the projects to which the string belongs.
  $query = "
      SELECT CONCAT(p.origin, '/', p.project) AS project
      FROM btr_locations l
      LEFT JOIN btr_templates t ON (t.potid = l.potid)
      LEFT JOIN btr_projects p ON (p.pguid = t.pguid)
      WHERE sguid = :sguid
  ";
  $string_projects = btr::db_query($query, array(':sguid' => $sguid))->fetchCol();

  // Get the projects where the user has that role.
  $account = user_load($uid);
  switch ($role) {
    case 'admin':
      $user_projects = $account->admin_projects;
      break;
    case 'moderator':
      $user_projects = $account->moderate_projects;
      break;
    default:
      $user_projects = array();
      break;
  }

  // Check and return.
  $arr_diff = array_diff($string_projects, $user_projects);
  return empty($arr_diff);
}
