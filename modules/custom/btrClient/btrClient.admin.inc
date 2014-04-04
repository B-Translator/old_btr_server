<?php
/**
 * @file
 * Administrative pages for the btrClient module.
 */

/**
 * General configuration settings for the module btrClient.
 *
 * @return
 *   An array containing form items to place on the module settings page.
 */
function btrClient_config() {

  $form['defaults'] = array(
    '#type'  => 'fieldset',
    '#title' => t('B-Translator Client Default Settings'),
  );

  // get a list of available languages
  $languages = btrClient_get_languages();
  foreach ($languages as $code => $lang)  $lang_options[$code] = $lang['name'];
  unset($lang_options['en']);

  // btrClient_translation_lng
  $form['defaults']['btrClient_translation_lng'] = array(
    '#type' => 'select',
    '#title' => t('Default Translation Language'),
    '#description' => t('The default language of translations (for anonymous users).'),
    '#options' => $lang_options,
    '#default_value' => variable_get('btrClient_translation_lng', 'fr'),
  );

  // btrClient_server
  $form['defaults']['btrClient_server'] = array(
    '#type' => 'textfield',
    '#title' => t('Server URL'),
    '#default_value' => variable_get('btrClient_server', ''),
    '#description' => t('The URL of the B-Translator server.'),
  );

  // btrClient_voting_mode
  $form['defaults']['btrClient_voting_mode'] = array(
    '#title'         => t('Select Voting Mode'),
    '#description'   => t('When voting mode is <em>Single</em>, only one translation can be voted as suitable for each string. When voting mode is <em>Multiple</em>, more than one translation can be selected as suitable for each string. <br/> <strong>Note:</strong> This setting must have the same value as the one on the server.'),
    '#type'          => 'radios',
    '#options'       => array(
      'single'   => t('Single'),
      'multiple' => t('Multiple'),
    ),
    '#default_value' => variable_get('btrClient_voting_mode', 'single'),
  );

  $form = system_settings_form($form);
  $form['#submit'][] = 'btrClient_config_get_languages';
  return $form;
}

function btrClient_config_get_languages() {
  // Update the cached value of languages.
  cache_clear_all('btrClient_languages', 'cache_btrClient');
  $languages = btrClient_get_languages();
}