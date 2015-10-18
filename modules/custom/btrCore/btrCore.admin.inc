<?php
/**
 * @file
 * Administrative pages for the btrCore module.
 */

/**
 * General configuration settings for the module btrCore.
 *
 * @return
 *   An array containing form items to place on the module settings page.
 */
function btrCore_config() {

  $form['config'] = array(
    '#type'  => 'fieldset',
    '#title' => t('B-Translator Configuration'),
  );

  // btr_languages
  $form['config']['btr_languages'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Translation Languages'),
    '#default_value' => variable_get('btr_languages', 'fr'),
    '#description'   => t('The list of translation languages supported by the server. Enter a space separated list of language codes.'),
  );

  // btr_client
  $form['config']['btr_client'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Client URL'),
    '#default_value' => variable_get('btr_client', 'https://l10n.example.org'),
    '#description'   => t('URL of the default client.'),
  );

  // btr_voting_mode
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
    '#title' => t('B-Translator Defaults'),
  );

  // btr_preferred_projects
  $projects_description = t("Select the projects that will be used for review and translations. Only strings from these projects will be presented to the users. <br/> You can enter projects in the form <em>origin/project</em>, for example: <em>KDE/kdeedu</em>, <em>Mozilla/browser</em>, etc. Or you can include all the projects from a certain origin, like this: <em>KDE</em>, <em>LibreOffice</em>, etc. <br/> Enter each project on a separate line. See a list of the imported projects <a href='@project-list' target='_blank'>here</a>.<br/> <strong>Note</strong>: The user can override the projects on his profile/settings. If the user does not subscribe to any projects, then the projects listed here will be used. If this list is empty, then all the imported projects will be used.",
                                    array('@project-list' => '/project/list/*/*/txt'));
  $form['defaults']['btr_preferred_projects'] = array(
    '#type' => 'textarea',
    '#title' => t('The List of Projects that Will be Used for Voting and Translation'),
    '#description' => $projects_description,
    '#default_value' => variable_get('btr_preferred_projects', ''),
  );

  $form['export'] = array(
    '#type'  => 'fieldset',
    '#title' => t('B-Translator Export/Import'),
  );

  $form['export']['btr_export_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Export path'),
    '#default_value' => variable_get('btr_export_path', '/var/www/exports'),
    '#description' => t('The directory where the exported projects will be placed. Must be accessable by the web server (www-data).'),
  );

  $form['export']['btr_export_notify_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Notify admin'),
    '#description' => t('Send a notification email to admin on each export request.'),
    '#default_value' => variable_get('btr_export_notify_admin', TRUE),
  );

  $form = system_settings_form($form);
  $form['#submit'][] = 'btrCore_config_set_languages';
  return $form;
}

/**
 * Update cached values of languages.
 */
function btrCore_config_set_languages() {
  // Update 'allowed_values' of 'field_translation_lng'.
  $info = field_info_field('field_translation_lng');
  $info['settings']['allowed_values'] = btr::languages_get_list();
  field_update_field($info);

  // Update 'allowed_values' of 'field_auxiliary_languages'.
  $info = field_info_field('field_auxiliary_languages');
  $info['settings']['allowed_values'] = btr::languages_get_list();
  field_update_field($info);
}
