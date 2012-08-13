<?php

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function btranslator_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = 'B-Translator';
}

/**
 * Implements hook_install_tasks().
 */
function btranslator_install_tasks($install_state) {

  include 'profiles/btranslator/modules/smtp/smtp.admin.inc';
  //include 'profiles/btranslator/modules/disqus/disqus.admin.inc';

  $tasks = array(
    'btranslator_smtp' => array(
      'display_name' => st('SMTP Settings'),
      'type' => 'form',
      'run' => INSTALL_TASK_RUN_IF_REACHED,
      'function' => 'smtp_admin_settings',
    ),
    /*
    'btranslator_disqus' => array(
      'display_name' => st('Disqus Settings'),
      'type' => 'form',
      'run' => INSTALL_TASK_RUN_IF_REACHED,
      'function' => 'disqus_admin_settings',
    ),
    */
  );

  return $tasks;
}