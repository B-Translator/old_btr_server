<?php
/**
 * @file
 * Function project_add_admin().
 */

namespace BTranslator;
use \btr;

/**
 * Add the user ($ulng, $umail) as admin of ($origin, $project).
 */
function project_add_admin($origin, $project, $ulng, $umail) {
  $pguid = sha1($origin . $project);

  // Delete it first, if he exists.
  btr::db_delete('btr_user_project_roles')
    ->condition('umail', $umail)
    ->condition('ulng', $ulng)
    ->condition('role', 'admin')
    ->execute();

  // Add as admin.
  btr::db_insert('btr_user_project_roles')
    ->fields([
        'umail' => $umail,
        'ulng' => $ulng,
        'pguid' => $pguid,
        'role' => 'admin',
      ])
    ->execute();
}
