<?php
/**
 * @file
 * btranslator_btranslator.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function btranslator_btranslator_user_default_permissions() {
  $permissions = array();

  // Exported permission: btranslator-admin.
  $permissions['btranslator-admin'] = array(
    'name' => 'btranslator-admin',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'l10n_feedback',
  );

  // Exported permission: btranslator-export.
  $permissions['btranslator-export'] = array(
    'name' => 'btranslator-export',
    'roles' => array(
      0 => 'translator',
    ),
    'module' => 'l10n_feedback',
  );

  // Exported permission: btranslator-flag.
  $permissions['btranslator-flag'] = array(
    'name' => 'btranslator-flag',
    'roles' => array(
      0 => 'contributor',
      1 => 'moderator',
      2 => 'translator',
    ),
    'module' => 'l10n_feedback',
  );

  // Exported permission: btranslator-import.
  $permissions['btranslator-import'] = array(
    'name' => 'btranslator-import',
    'roles' => array(
      0 => 'translator',
    ),
    'module' => 'l10n_feedback',
  );

  // Exported permission: btranslator-resolve.
  $permissions['btranslator-resolve'] = array(
    'name' => 'btranslator-resolve',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'l10n_feedback',
  );

  // Exported permission: btranslator-stats.
  $permissions['btranslator-stats'] = array(
    'name' => 'btranslator-stats',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'l10n_feedback',
  );

  // Exported permission: btranslator-suggest.
  $permissions['btranslator-suggest'] = array(
    'name' => 'btranslator-suggest',
    'roles' => array(
      0 => 'contributor',
      1 => 'moderator',
      2 => 'translator',
    ),
    'module' => 'l10n_feedback',
  );

  // Exported permission: btranslator-vote.
  $permissions['btranslator-vote'] = array(
    'name' => 'btranslator-vote',
    'roles' => array(
      0 => 'contributor',
      1 => 'moderator',
      2 => 'translator',
    ),
    'module' => 'l10n_feedback',
  );

  return $permissions;
}
