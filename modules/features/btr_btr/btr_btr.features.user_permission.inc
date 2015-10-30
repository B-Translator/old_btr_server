<?php
/**
 * @file
 * btr_btr.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function btr_btr_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'btranslator-admin'.
  $permissions['btranslator-admin'] = array(
    'name' => 'btranslator-admin',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'btrUser',
  );

  // Exported permission: 'btranslator-export'.
  $permissions['btranslator-export'] = array(
    'name' => 'btranslator-export',
    'roles' => array(
      'translator' => 'translator',
    ),
    'module' => 'btrUser',
  );

  // Exported permission: 'btranslator-flag'.
  $permissions['btranslator-flag'] = array(
    'name' => 'btranslator-flag',
    'roles' => array(
      'contributor' => 'contributor',
      'moderator' => 'moderator',
      'translator' => 'translator',
    ),
    'module' => 'btrUser',
  );

  // Exported permission: 'btranslator-import'.
  $permissions['btranslator-import'] = array(
    'name' => 'btranslator-import',
    'roles' => array(
      'translator' => 'translator',
    ),
    'module' => 'btrUser',
  );

  // Exported permission: 'btranslator-resolve'.
  $permissions['btranslator-resolve'] = array(
    'name' => 'btranslator-resolve',
    'roles' => array(
      'moderator' => 'moderator',
    ),
    'module' => 'btrUser',
  );

  // Exported permission: 'btranslator-stats'.
  $permissions['btranslator-stats'] = array(
    'name' => 'btranslator-stats',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'moderator' => 'moderator',
    ),
    'module' => 'btrUser',
  );

  // Exported permission: 'btranslator-suggest'.
  $permissions['btranslator-suggest'] = array(
    'name' => 'btranslator-suggest',
    'roles' => array(
      'contributor' => 'contributor',
      'moderator' => 'moderator',
      'translator' => 'translator',
    ),
    'module' => 'btrUser',
  );

  // Exported permission: 'btranslator-vote'.
  $permissions['btranslator-vote'] = array(
    'name' => 'btranslator-vote',
    'roles' => array(
      'contributor' => 'contributor',
      'moderator' => 'moderator',
      'translator' => 'translator',
    ),
    'module' => 'btrUser',
  );

  return $permissions;
}
