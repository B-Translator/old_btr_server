<?php
/**
 * @file
 * Function: utils_user_has_project_role()
 */

namespace BTranslator;
use \btr;

/**
 * Check whether the current user has a certain role on the projects of the
 * given string.
 *
 * @param $role
 *   The role to be checked (admin|moderator).
 *
 * @param $sguid
 *   The id of the string.
 *
 * @return
 *   TRUE if the string belongs to projects where user has the role.
 */
function utils_user_has_project_role($role, $sguid) {
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
  switch ($role) {
    case 'admin':
      $user_projects = $GLOBALS['user']->admin_projects;
      break;
    case 'moderator':
      $user_projects = $GLOBALS['user']->moderate_projects;
      break;
    default:
      $user_projects = array();
      break;
  }

  // Check and return.
  $arr_diff = array_diff($string_projects, $user_projects);
  return empty($arr_diff);
}
