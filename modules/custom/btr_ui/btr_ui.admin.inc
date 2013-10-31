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

  // btr_ui_translation_lng
  $form['defaults']['btr_ui_translation_lng'] = array(
    '#type' => 'select',
    '#title' => t('Default Translation Language'),
    '#description' => t('The default language of translations (for anonymous users).'),
    '#options' => $lang_options,
    '#default_value' => variable_get('btr_ui_translation_lng', 'fr'),
  );

  return system_settings_form($form);
}  //  End of btr_config().
