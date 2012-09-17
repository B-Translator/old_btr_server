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

  $tasks = array(
    'btranslator_config' => array(
      'display_name' => st('B-Translator Settings'),
      'type' => 'form',
      'run' => INSTALL_TASK_RUN_IF_REACHED,
      'function' => 'btranslator_config',
    ),
    'btranslator_smtp' => array(
      'display_name' => st('SMTP Settings'),
      'type' => 'form',
      'run' => INSTALL_TASK_RUN_IF_REACHED,
      'function' => 'smtp_config',
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

  $voting_mode_options = array(
    'single'   => t('Single'),
    'multiple' => t('Multiple'),
  );
  $voting_mode_description = t('
      When voting mode is <em>Single</em>, only one translation
      can be voted as suitable for each string. When voting mode is
      <em>Multiple</em>, more than one translation can be selected
      as suitable for each string. <br/>
      <strong>Note:</strong> Switching back from <em>Multiple</em>
      to <em>Single</em> may have a bad impact on the existing votes.
  ');

  $form['config']['l10n_feedback_voting_mode'] = array(
    '#type'          => 'radios',
    '#title'         => t('Select Voting Mode'),
    '#default_value' => variable_get('l10n_feedback_voting_mode', 'single'),
    '#options'       => $voting_mode_options,
    '#description'   => $voting_mode_description,
  );

  $languages = l10n_feedback_get_languages();
  foreach ($languages as $code => $lang)  $lang_options[$code] = $lang['name'];
  $form['config']['l10n_feedback_default_lng'] = array(
    '#type' => 'select',
    '#title' => t('Default Translation Language'),
    '#description' => t('The default language of translations, which is used wherever the translations language in not specified (for example for the guest users).'),
    '#options' => $lang_options,
    '#default_value' => variable_get('l10n_feedback_default_lng', 'fr'),
  );

  return system_settings_form($form);
}  //  End of l10n_feedback_config().


/**
 * SMTP configuration settings.
 *
 * @return
 *   An array containing form items to place on the module settings page.
 */
function smtp_config() {
  // Override the smtp_library variable.
  if (module_exists('mimemail') &&
      strpos(variable_get('smtp_library', ''), 'mimemail')) {
    // don't touch smtp_library
  }
  else {
    if (variable_get('smtp_on', 0)) {
      $smtp_path = drupal_get_filename('module', 'smtp');
      if ($smtp_path) {
        variable_set('smtp_library', $smtp_path);
        drupal_set_message(t('SMTP.module is active.'));
      }
      // If drupal can't find the path to the module, display an error.
      else {
        drupal_set_message(t("SMTP.module error: Can't find file."), 'error');
      }
    }
    // If this module is turned off, delete the variable.
    else {
      variable_del('smtp_library');
      drupal_set_message(t('SMTP.module is INACTIVE.'));
    }
  }

  $form['onoff'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Install options'),
  );
  $form['onoff']['smtp_on'] = array(
    '#type'          => 'radios',
    '#title'         => t('Turn this module on or off'),
    '#default_value' => variable_get('smtp_on', 0),
    '#options'       => array(1 => t('On'), 0 => t('Off')),
    '#description'   => t('To uninstall this module you must turn it off here first.'),
  );

  $form['server'] = array(
    '#type'  => 'fieldset',
    '#title' => t('SMTP server settings'),
  );
  $form['server']['smtp_host'] = array(
    '#type'          => 'textfield',
    '#title'         => t('SMTP server'),
    '#default_value' => variable_get('smtp_host', ''),
    '#description'   => t('The address of your outgoing SMTP server.'),
  );
  $form['server']['smtp_hostbackup'] = array(
    '#type'          => 'textfield',
    '#title'         => t('SMTP backup server'),
    '#default_value' => variable_get('smtp_hostbackup', ''),
    '#description'   => t('The address of your outgoing SMTP backup server. If the primary server can\'t be found this one will be tried. This is optional.'),
  );
  $form['server']['smtp_port'] = array(
    '#type'          => 'textfield',
    '#title'         => t('SMTP port'),
    '#size'          => 6,
    '#maxlength'     => 6,
    '#default_value' => variable_get('smtp_port', '25'),
    '#description'   => t('The default SMTP port is 25, if that is being blocked try 80. Gmail uses 465. See !url for more information on configuring for use with Gmail.', array('!url' => l(t('this page'), 'http://gmail.google.com/support/bin/answer.py?answer=13287'))),
  );
  // Only display the option if openssl is installed.
  if (function_exists('openssl_open')) {
    $encryption_options = array(
      'standard' => t('No'),
      'ssl'      => t('Use SSL'),
      'tls'      => t('Use TLS'),
    );
    $encryption_description = t('This allows connection to an SMTP server that requires SSL encryption such as Gmail.');
  }
  // If openssl is not installed, use normal protocol.
  else {
    variable_set('smtp_protocol', 'standard');
    $encryption_options = array('standard' => t('No'));
    $encryption_description = t('Your PHP installation does not have SSL enabled. See the !url page on php.net for more information. Gmail requires SSL.', array('!url' => l(t('OpenSSL Functions'), 'http://php.net/openssl')));
  }
  $form['server']['smtp_protocol'] = array(
    '#type'          => 'select',
    '#title'         => t('Use encrypted protocol'),
    '#default_value' => variable_get('smtp_protocol', 'standard'),
    '#options'       => $encryption_options,
    '#description'   => $encryption_description,
  );

  $form['auth'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('SMTP Authentication'),
    '#description' => t('Leave blank if your SMTP server does not require authentication.'),
  );
  $form['auth']['smtp_username'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Username'),
    '#default_value' => variable_get('smtp_username', ''),
    '#description'   => t('SMTP Username.'),
  );
  $form['auth']['smtp_password'] = array(
    '#type'          => 'password',
    '#title'         => t('Password'),
    '#default_value' => variable_get('smtp_password', ''),
    '#description'   => t('SMTP password. Leave blank if you don\'t wish to change it.'),
  );

  $form['email_options'] = array(
    '#type'  => 'fieldset',
    '#title' => t('E-mail options'),
  );
  $form['email_options']['smtp_from'] = array(
    '#type'          => 'textfield',
    '#title'         => t('E-mail from address'),
    '#default_value' => variable_get('smtp_from', ''),
    '#description'   => t('The e-mail address that all e-mails will be from.'),
  );
  $form['email_options']['smtp_fromname'] = array(
    '#type'          => 'textfield',
    '#title'         => t('E-mail from name'),
    '#default_value' => variable_get('smtp_fromname', ''),
    '#description'   => t('The name that all e-mails will be from. If left blank will use the site name of:') . ' ' . variable_get('site_name', 'Drupal powered site'),
  );
  $form['email_options']['smtp_allowhtml'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Allow to send e-mails formated as Html'),
    '#default_value' => variable_get('smtp_allowhtml', 0),
    '#description'   => t('Cheking this box will allow Html formated e-mails to be sent with the SMTP protocol.'),
  );

  // If an address was given, send a test e-mail message.
  $test_address = variable_get('smtp_test_address', '');
  if ($test_address != '') {
    // Clear the variable so only one message is sent.
    variable_del('smtp_test_address');
    global $language;
    $params['subject'] = t('Drupal SMTP test e-mail');
    $params['body']    = array(t('If you receive this message it means your site is capable of using SMTP to send e-mail.'));
    drupal_mail('smtp', 'smtp-test', $test_address, $language, $params);
    drupal_set_message(t('A test e-mail has been sent to @email. You may want to !check for any error messages.', array('@email' => $test_address, '!check' => l(t('check the logs'), 'admin/reports/dblog'))));
  }
  $form['email_test'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Send test e-mail'),
  );
  $form['email_test']['smtp_test_address'] = array(
    '#type'          => 'textfield',
    '#title'         => t('E-mail address to send a test e-mail to'),
    '#default_value' => '',
    '#description'   => t('Type in an address to have a test e-mail sent there.'),
  );

  $form['smtp_debugging'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Enable debugging'),
    '#default_value' => variable_get('smtp_debugging', 0),
    '#description'   => t('Checking this box will print SMTP messages from the server for every e-mail that is sent.'),
  );

  return system_settings_form($form);
}  //  End of smtp_config().



/**
 * Validataion for the administrative settings form.
 *
 * @param form
 *   An associative array containing the structure of the form.
 * @param form_state
 *   A keyed array containing the current state of the form.
 */
function smtp_config_validate($form, &$form_state) {
  if ($form_state['values']['smtp_on'] == 1 && $form_state['values']['smtp_host'] == '') {
    form_set_error('smtp_host', t('You must enter an SMTP server address.'));
  }

  if ($form_state['values']['smtp_on'] == 1 && $form_state['values']['smtp_port'] == '') {
    form_set_error('smtp_port', t('You must enter an SMTP port number.'));
  }

  if ($form_state['values']['smtp_from'] && !valid_email_address($form_state['values']['smtp_from'])) {
    form_set_error('smtp_from', t('The provided from e-mail address is not valid.'));
  }
  // A little hack. When form is presentend, the password is not shown (Drupal way of doing).
  // So, if user submits the form without changing the password, we mus prevent it from being reset.
  if (empty($form_state['values']['smtp_password'])) {
    unset($form_state['values']['smtp_password']);
  }
}  //  End of smtp_config_validate().

