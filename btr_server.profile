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
  // Add our custom CSS file for the installation process
  //drupal_add_css(drupal_get_path('profile', 'btranslator') . '/btranslator.css');

  require_once(drupal_get_path('module', 'phpmailer') . '/phpmailer.admin.inc');

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
      'function' => 'phpmailer_settings_form',
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
  $languages = btr_get_languages();
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
}  //  End of btranslator_config().
