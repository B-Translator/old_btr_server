<?php
/**
 * @file
 * Installation steps for the profile B-Translator.
 */

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

  $tasks = array(
    'btranslator_config' => array(
      'display_name' => st('B-Translator Settings'),
      'type' => 'form',
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
      'function' => 'btranslator_config',
    ),
    'btranslator_mail_config' => array(
      'display_name' => st('Mail Settings'),
      'type' => 'form',
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
      'function' => 'btranslator_mail_config_form',
    ),
  );

  return $tasks;
}


/**
 * General configuration settings for B-Translator.
 *
 * @return
 *   An array containing form items to place on the module settings page.
 */
function btranslator_config() {

  $form['config'] = array(
    '#type'  => 'fieldset',
    '#title' => t('B-Translator configuration options'),
  );

  // get a list of available languages
  $languages = l10n_feedback_get_languages();
  foreach ($languages as $code => $lang)  $lang_options[$code] = $lang['name'];
  unset($lang_options['en']);

  // btr_translation_lng
  $form['config']['btr_translation_lng'] = array(
    '#type' => 'select',
    '#title' => t('Translation Language'),
    '#description' => t('The language of translations. This site is about collecting feedback for the translations of this language.'),
    '#options' => $lang_options,
    '#default_value' => variable_get('btr_translation_lng', 'fr'),
  );

  $voting_mode_options = array(
    'single'   => t('Single'),
    'multiple' => t('Multiple'),
  );
  $voting_mode_description = t('When voting mode is <em>Single</em>, only one translation can be voted as suitable for each string. When voting mode is <em>Multiple</em>, more than one translation can be selected as suitable for each string. <br/> <strong>Note:</strong> Switching back from <em>Multiple</em> to <em>Single</em> may have a bad impact on the existing votes.');

  $form['config']['btr_voting_mode'] = array(
    '#type'          => 'radios',
    '#title'         => t('Select Voting Mode'),
    '#default_value' => variable_get('btr_voting_mode', 'single'),
    '#options'       => $voting_mode_options,
    '#description'   => $voting_mode_description,
  );

  $form['defaults'] = array(
    '#type'  => 'fieldset',
    '#title' => t('B-Translator default settings'),
  );

  // btr_preferred_projects
  $preferred_projects_description = t("Select the projects that will be used for review and translations. Only strings from these projects will be presented to the users. <br/> You can enter projects in the form <em>origin/project</em>, for example: <em>KDE/kdeedu</em>, <em>Mozilla/browser</em>, etc. Or you can include all the projects from a certain origin, like this: <em>KDE</em>, <em>LibreOffice</em>, etc. <br/> Enter each project on a separate line. See a list of the imported projects <a href='@project-list' target='_blank'>here</a>.<br/> <strong>Note</strong>: The user can override the preferred projects on his profile/settings. If the user does not select any preferred projects on his profile, then the projects listed here will be used. If this list is empty, then all the imported projects will be used.",
                                    array('@project-list' => '/translations/project/list/*/*/txt'));
  $form['defaults']['btr_preferred_projects'] = array(
    '#type' => 'textarea',
    '#title' => t('The List of Projects that Will be Used for Voting and Translation'),
    '#description' => $preferred_projects_description,
    '#default_value' => variable_get('btr_preferred_projects', ''),
  );


  return system_settings_form($form);
}  //  End of l10n_feedback_config().

/**
 * Form builder for Mail and SMTP settings.
 */
function btranslator_mail_config_form($form, $form_state) {
  $form['smtp_on'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use PHPMailer to send e-mails'),
    '#default_value' => variable_get('smtp_on', 0),
    '#description' => t('When enabled, PHPMailer will be used to deliver all site e-mails.'),
  );
  // Only allow to send all e-mails if Mime Mail is not configured the same
  // (mimemail_alter is the counterpart to smtp_on).
  if (module_exists('mimemail') && variable_get('mimemail_alter', 0)) {
    $form['smtp_on']['#disabled'] = TRUE;
    $form['smtp_on']['#default_value'] = 0;
    $form['smtp_on']['#description'] = t('MimeMail has been detected. To enable PHPMailer for mail transport, go to the <a href="@url">MimeMail settings page</a> and select PHPMailer from the available e-mail engines.', array('@url' => url('admin/config/system/mimemail')));
  }
  elseif (!variable_get('smtp_on', 0) && empty($form_state['input'])) {
    drupal_set_message(t('PHPMailer is currently disabled.'), 'warning');
  }

  $form['server']['smtp_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Primary SMTP server'),
    '#default_value' => variable_get('smtp_host', 'localhost'),
    '#description' => t('The host name or IP address of your primary SMTP server.  Use !gmail-smtp for Google Mail.', array('!gmail-smtp' => '<code>smtp.gmail.com</code>')),
    '#required' => TRUE,
  );
  $form['server']['smtp_hostbackup'] = array(
    '#type' => 'textfield',
    '#title' => t('Backup SMTP server'),
    '#default_value' => variable_get('smtp_hostbackup', ''),
    '#description' => t('Optional host name or IP address of a backup server, if the primary server fails.  You may override the default port below by appending it to the host name separated by a colon.  Example: !hostname', array('!hostname' => '<code>localhost:465</code>')),
  );
  $form['server']['smtp_port'] = array(
    '#type' => 'textfield',
    '#title' => t('SMTP port'),
    '#size' => 5,
    '#maxlength' => 5,
    '#default_value' => variable_get('smtp_port', '25'),
    '#description' => t('The standard SMTP port is 25, for Google Mail use 465.'),
    '#required' => TRUE,
  );
  $form['server']['smtp_protocol'] = array(
    '#type' => 'select',
    '#title' => t('Use secure protocol'),
    '#default_value' => variable_get('smtp_protocol', ''),
    '#options' => array('' => t('No'), 'ssl' => t('SSL'), 'tls' => t('TLS')),
    '#description' => t('Whether to use an encrypted connection to communicate with the SMTP server.  Google Mail requires SSL.'),
  );
  if (!function_exists('openssl_open')) {
    $form['server']['smtp_protocol']['#default_value'] = '';
    $form['server']['smtp_protocol']['#disabled'] = TRUE;
    $form['server']['smtp_protocol']['#description'] .= ' ' . t('Note: This option has been disabled since your PHP installation does not seem to have support for OpenSSL.');
    variable_set('smtp_protocol', '');
  }

  $form['auth'] = array(
    '#type' => 'fieldset',
    '#title' => t('SMTP authentication'),
    '#description' => t('Leave blank if your SMTP server does not require authentication.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['auth']['smtp_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#default_value' => variable_get('smtp_username', ''),
    '#description' => t('For Google Mail, enter your username including "@gmail.com".'),
  );
  if (!variable_get('smtp_hide_password', 0)) {
    $form['auth']['smtp_password'] = array(
      '#type' => 'textfield',
      '#title' => t('Password'),
      '#default_value' => variable_get('smtp_password', ''),
    );
    $form['auth']['smtp_hide_password'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide password'),
      '#default_value' => 0,
      '#description' => t("Check this option to permanently hide the plaintext password from peeking eyes. You may still change the password afterwards, but it won't be displayed anymore."),
    );
  }
  else {
    $have_password = (variable_get('smtp_password', '') != '');
    $form['auth']['smtp_password'] = array(
      '#type' => 'password',
      '#title' => $have_password ? t('Change password') : t('Password'),
      '#description' => $have_password ? t('Leave empty if you do not intend to change the current password.') : '',
    );
  }

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced SMTP settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['advanced']['smtp_fromname'] = array(
    '#type' => 'textfield',
    '#title' => t('"From" name'),
    '#default_value' => variable_get('smtp_fromname', ''),
    '#description' => t('Enter a name that should appear as the sender for all messages.  If left blank the site name will be used instead: %sitename.', array('%sitename' => variable_get('site_name', 'Drupal'))),
  );
  $form['advanced']['smtp_always_replyto'] = array(
    '#type' => 'checkbox',
    '#title' => t('Always set "Reply-To" address'),
    '#default_value' => variable_get('smtp_always_replyto', 0),
    '#description' => t('Enables setting the "Reply-To" address to the original sender of the message, if unset.  This is required when using Google Mail, which would otherwise overwrite the original sender.'),
  );
  $form['advanced']['smtp_keepalive'] = array(
    '#type' => 'checkbox',
    '#title' => t('Keep connection alive'),
    '#default_value' => variable_get('smtp_keepalive', 0),
    '#description' => t('Whether to reuse an existing connection during a request.  Improves performance when sending a lot of e-mails at once.'),
  );
  $form['advanced']['smtp_debug'] = array(
    '#type' => 'select',
    '#title' => t('Debug level'),
    '#default_value' => variable_get('smtp_debug', 0),
    '#options' => array(0 => t('Disabled'), 1 => t('Errors only'), 2 => t('Server responses'), 4 => t('Full communication')),
    '#description' => t("Debug the communication with the SMTP server.  You normally shouldn't enable this unless you're trying to debug e-mail sending problems."),
  );

  // Send a test email message if an address has been entered.
  if ($test_address = variable_get('phpmailer_test', '')) {
    // Delete first to avoid unintended resending in case of an error.
    variable_del('phpmailer_test');
    // If PHPMailer is enabled, send via regular drupal_mail().
    if (phpmailer_enabled()) {
      drupal_mail('phpmailer', 'test', $test_address, NULL);
    }
    // Otherwise, prepare and send the test mail manually.
    else {
      // Prepare the message without sending.
      $message = drupal_mail('phpmailer', 'test', $test_address, NULL, array(), NULL, FALSE);
      // Send the message. drupal_mail_wrapper() is only defined when PHPMailer
      // is enabled, so drupal_mail_send() cannot be used.
      // @see drupal_mail_send()
      module_load_include('inc', 'phpmailer', 'includes/phpmailer.drupal');
      phpmailer_send($message);
    }
    drupal_set_message(t('A test e-mail has been sent to %email. <a href="@watchdog-url">Check the logs</a> for any error messages.', array(
      '%email' => $test_address,
      '@watchdog-url' => url('admin/reports/dblog'),
    )));
  }

  $form['test'] = array(
    '#type' => 'fieldset',
    '#title' => t('Test configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['test']['phpmailer_test'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient'),
    '#default_value' => '',
    '#description' => t('Type in an address to have a test e-mail sent there.'),
  );

  $form['#submit'] = array('btranslator_mail_config_form_submit');

  return system_settings_form($form);
}

/**
 * Form validation function.
 */
function btranslator_mail_config_form_validate($form, &$form_state) {
  if ($form_state['values']['smtp_on']) {
    if (intval($form_state['values']['smtp_port']) == 0) {
      form_set_error('smtp_port', t('You must enter a valid SMTP port number.'));
    }
  }
}

/**
 * Form submit function.
 */
function btranslator_mail_config_form_submit($form, &$form_state) {
  // Enable/disable mail sending subsystem.
  if ($form_state['values']['smtp_on']) {
    if (!phpmailer_enabled()) {
      $mail_system = variable_get('mail_system', array('default-system' => 'DefaultMailSystem'));
      $mail_system['default-system'] = 'DrupalPHPMailer';
      variable_set('mail_system', $mail_system);

      drupal_set_message(t('PHPMailer will be used to deliver all site e-mails.'));
      watchdog('phpmailer', 'PHPMailer has been enabled.');
    }
  }
  elseif (phpmailer_enabled()) {
    // Remove PHPMailer from all mail keys it is configured for.
    $mail_system = variable_get('mail_system', array('default-system' => 'DefaultMailSystem'));
    foreach ($mail_system as $key => $class) {
      if ($class == 'DrupalPHPMailer') {
        if ($key != 'default-system') {
          unset($mail_system[$key]);
        }
        else {
          $mail_system[$key] = 'DefaultMailSystem';
        }
      }
    }
    variable_set('mail_system', $mail_system);

    drupal_set_message(t('PHPMailer has been disabled.'));
    watchdog('phpmailer', 'PHPMailer has been disabled.');
  }

  // Log configuration changes.
  $settings = array('host', 'port', 'protocol', 'username');
  // Ignore empty passwords if hide password is active.
  if (variable_get('smtp_hide_password', 0) && $form_state['values']['smtp_password'] == '') {
    unset($form_state['values']['smtp_password']);
  }
  else {
    $settings[] = 'password';
  }
  foreach ($settings as $setting) {
    if ($form_state['values']['smtp_'. $setting] != variable_get('smtp_'. $setting, '')) {
      watchdog('phpmailer', 'SMTP configuration changed.');
      break;
    }
  }
}
