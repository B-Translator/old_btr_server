<?php
/**
 * @file
 * btranslator_mass_contact.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function btranslator_mass_contact_user_default_permissions() {
  $permissions = array();

  // Exported permission: mass contact administer.
  $permissions['mass contact administer'] = array(
    'name' => 'mass contact administer',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact archive messages.
  $permissions['mass contact archive messages'] = array(
    'name' => 'mass contact archive messages',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact change default sender information.
  $permissions['mass contact change default sender information'] = array(
    'name' => 'mass contact change default sender information',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact include attachments.
  $permissions['mass contact include attachments'] = array(
    'name' => 'mass contact include attachments',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact override archiving.
  $permissions['mass contact override archiving'] = array(
    'name' => 'mass contact override archiving',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact override bcc.
  $permissions['mass contact override bcc'] = array(
    'name' => 'mass contact override bcc',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact override text format.
  $permissions['mass contact override text format'] = array(
    'name' => 'mass contact override text format',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact send messages.
  $permissions['mass contact send messages'] = array(
    'name' => 'mass contact send messages',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact send to users in the All Users category.
  $permissions['mass contact send to users in the All Users category'] = array(
    'name' => 'mass contact send to users in the All Users category',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
      2 => 'translator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact send to users in the Translators category.
  $permissions['mass contact send to users in the Translators category'] = array(
    'name' => 'mass contact send to users in the Translators category',
    'roles' => array(),
    'module' => 'mass_contact',
  );

  return $permissions;
}
