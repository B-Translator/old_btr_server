<?php
/**
 * @file
 * btr_btr.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function btr_btr_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => '2',
  );

  // Exported role: contributor.
  $roles['contributor'] = array(
    'name' => 'contributor',
    'weight' => '4',
  );

  // Exported role: moderator.
  $roles['moderator'] = array(
    'name' => 'moderator',
    'weight' => '5',
  );

  // Exported role: translator.
  $roles['translator'] = array(
    'name' => 'translator',
    'weight' => '3',
  );

  return $roles;
}
