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

  return system_settings_form($form);
}  //  End of btr_config().
