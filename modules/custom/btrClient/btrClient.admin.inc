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
  $languages = btr_get_languages();
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

  $form['server'] = array(
    '#type'  => 'fieldset',
    '#title' => t('B-Translator Server Settings'),
    '#description' => t('The settings for connecting to the web services of B-Translator.'),
 );

  $form['server']['btrClient_server_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Server URL'),
    '#default_value' => variable_get('btrClient_server_url', 'https://l10n.org.xx'),
    '#description' => t('The URL of the B-Translator server.'),
  );

  $form['server']['btrClient_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#default_value' => variable_get('btrClient_client_id'),
    '#description' => t('The Client ID that is registered on the B-Translator server.'),
  );

  $form['server']['btrClient_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Client secret'),
    '#default_value' => variable_get('btrClient_client_secret'),
    '#description' => t('The Client secret that is registered on the B-Translator server.'),
  );

  $form['server']['btrClient_skip_ssl_check'] = array(
    '#type' => 'checkbox',
    '#title' => t('Skip SSL'),
    '#description' => t('Skip checking the SSL certificate (for development and testing).'),
    '#default_value' => variable_get('btrClient_skip_ssl_check', FALSE),
  );

  return system_settings_form($form);
}  //  End of btr_config().
