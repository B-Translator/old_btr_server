<?php
/**
 * @file
 * btr_hybridauth.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function btr_hybridauth_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'use hybridauth'.
  $permissions['use hybridauth'] = array(
    'name' => 'use hybridauth',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'hybridauth',
  );

  return $permissions;
}
