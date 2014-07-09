<?php
/**
 * @file
 * Installation steps for the profile B-Translator Server.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function btr_server_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = 'B-Translator';
}

/**
 * Implements hook_install_tasks().
 */
function btr_server_install_tasks($install_state) {
  // Add our custom CSS file for the installation process
  drupal_add_css(drupal_get_path('profile', 'btr_server') . '/btr_server.css');

  module_load_include('inc', 'phpmailer', 'phpmailer.admin');
  module_load_include('inc', 'btrCore', 'includes/languages');
  module_load_include('inc', 'btrCore', 'btrCore.admin');

  $tasks = array(
    'btr_server_mail_config' => array(
      'display_name' => st('Mail Settings'),
      'type' => 'form',
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
      'function' => 'phpmailer_settings_form',
    ),
    'btr_server_config' => array(
      'display_name' => st('B-Translator Server Settings'),
      'type' => 'form',
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
      'function' => 'btrCore_config',
    ),
  );

  return $tasks;
}
