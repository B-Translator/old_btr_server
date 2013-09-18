<?php
/**
 * @file
 * Administrative pages for the btr_ui module.
 */

/**
 * General configuration settings for the module btr_ui.
 *
 * @return
 *   An array containing form items to place on the module settings page.
 */
function btr_ui_config() {

  $form['config'] = array(
    '#type'  => 'fieldset',
    '#title' => t('B-Translator UI configuration options'),
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

  $form['export'] = array(
    '#type'  => 'fieldset',
    '#title' => t('B-Translator UI export configuration'),
  );

  $form['export']['btr_export_notify_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Notify admin'),
    '#description' => t('Send a notification email to admin on each export request.'),
    '#default_value' => variable_get('btr_export_notify_admin', TRUE),
  );


  return system_settings_form($form);
}  //  End of btr_config().
