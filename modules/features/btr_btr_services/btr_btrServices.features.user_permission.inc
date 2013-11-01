<?php
/**
 * @file
 * btr_btrServices.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function btr_btrServices_user_default_permissions() {
  $permissions = array();

  // Exported permission: use oauth2 server.
  $permissions['use oauth2 server'] = array(
    'name' => 'use oauth2 server',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'oauth2_server',
  );

  return $permissions;
}
