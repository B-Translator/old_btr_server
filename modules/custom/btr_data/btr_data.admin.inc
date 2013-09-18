<?php
/**
 * @file
 * Administrative pages for the btr_data module.
 */

/**
 * General configuration settings for the module btr_data.
 *
 * @return
 *   An array containing form items to place on the module settings page.
 */
function btr_data_config() {

  $form['config'] = array(
    '#type'  => 'fieldset',
    '#title' => t('B-Translator Back-End Configuration'),
  );

  // get a list of available languages
  $languages = btr_get_languages();
  foreach ($languages as $code => $lang)  $lang_options[$code] = $lang['name'];
  unset($lang_options['en']);

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

  $form['export'] = array(
    '#type'  => 'fieldset',
    '#title' => t('B-Translator Data export configuration'),
  );

  $form['export']['btr_export_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Export path'),
    '#default_value' => variable_get('btr_export_path', '/var/www/exports'),
    '#description' => t('The directory where the exported projects will be placed. Must be accessable by the web server (www-data).'),
  );

  return system_settings_form($form);
}  //  End of btr_data_config().
