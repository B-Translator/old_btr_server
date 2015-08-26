<?php
/**
 * @file
 * Definition of the function project_users(), which returns the users of a
 * project with a certain role (admin, moderator, etc.)
 */

namespace BTranslator;
use \btr;

/**
 * Get the users of a project with a certain role (admin, moderator, etc.)
 *
 * @param role
 *   Role of the users
 *
 * @param origin
 *   Origin of the project.
 *
 * @param project
 *   The name of the project.
 *
 * @param lng
 *   Translation to be exported.
 */
function project_users($role, $origin, $project, $lng) {
  $get_project_users = "
    SELECT u.uid, u.name, u.umail as email
    FROM {btr_user_project_roles} r
    JOIN {btr_users} u ON (u.umail = r.umail AND u.ulng = r.ulng)
    WHERE r.pguid = :pguid AND r.ulng = :ulng AND r.role = :role
  ";
  $params = [
    ':pguid' => sha1($origin . $project),
    ':ulng' => $lng,
    ':role' => $role,
  ];
  $users = btr::db_query($get_project_users, $params)->fetchAllAssoc('uid');
  return $users;
}
