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
    '#default_value' => variable_get('btrClient_server', $GLOBALS['base_url']),
    '#description' => t('The URL of the B-Translator server.'),
  );

  return system_settings_form($form);
}
