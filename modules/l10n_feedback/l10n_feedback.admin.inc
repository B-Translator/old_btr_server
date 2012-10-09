<?php
/**
 * @file
 * Administrative pages for the l10n_feedback module.
 */

/**
 * General configuration settings for the module l10n_feedback.
 *
 * @return
 *   An array containing form items to place on the module settings page.
 */
function l10n_feedback_config() {

  $form['config'] = array(
    '#type'  => 'fieldset',
    '#title' => t('B-Translator configuration options'),
  );

  // get a list of available languages
  $languages = l10n_feedback_get_languages();
  foreach ($languages as $code => $lang)  $lang_options[$code] = $lang['name'];
  unset($lang_options['en']);

  // l10n_feedback_translation_lng
  $form['config']['l10n_feedback_translation_lng'] = array(
    '#type' => 'select',
    '#title' => t('Translation Language'),
    '#description' => t('The language of translations. This site is about collecting feedback for the translations of this language.'),
    '#options' => $lang_options,
    '#default_value' => variable_get('l10n_feedback_translation_lng', 'fr'),
  );

  // l10n_feedback_voting_mode
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

  $form['defaults'] = array(
    '#type'  => 'fieldset',
    '#title' => t('B-Translator default settings'),
  );

  // l10n_feedback_preferred_projects
  $preferred_projects_description = t("
       Select the projects that will be used for review and translations.
       Only strings from these projects will be presented to the users. <br/>
       You can enter projects in the form <em>origin/project</em>, for example:
       <em>KDE/kdeedu</em>, <em>Mozilla/browser</em>, etc.
       Or you can include all the projects from a certain origin,
       like this: <em>KDE</em>, <em>LibreOffice</em>, etc. <br/>
       Enter each project on a separate line.
       See a list of the imported projects <a href='/translations/project/list/*/*/txt' target='_blank'>here</a>.<br/>
       <strong>Note</strong>: The user can override the preferred projects on his profile/settings.
       If the user does not select any preferred projects on his profile, then the projects listed here
       will be used. If this list is empty, then all the imported projects will be used.
  ");
  $form['defaults']['l10n_feedback_preferred_projects'] = array(
    '#type' => 'textarea',
    '#title' => t('The List of Projects that Will be Used for Voting and Translation'),
    '#description' => $preferred_projects_description,
    '#default_value' => variable_get('l10n_feedback_preferred_projects', ''),
  );

  return system_settings_form($form);
}  //  End of l10n_feedback_config().
