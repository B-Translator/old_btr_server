<?php
/**
 * @file
 * Configuration of Sharethis (custom/private settings).
 */

/**
 * Implements hook_menu().
 */
function btr_sharethis_menu() {
  $items = array();
  $items['admin/config/btr/sharethis'] = array(
    'title'            => 'Sharethis',
    'description'      => 'Custom Sharethis settings.',
    'page callback'    => 'drupal_get_form',
    'page arguments'   => array('btr_sharethis_config'),
    'access arguments' => array('btranslator-admin'),
  );

  return $items;
}


/**
 * Custom settings for Sharethis.
 *
 * @return
 *   An array containing form items to place on the module settings page.
 */
function btr_sharethis_config() {
  $form = array();

  $current_options_array = sharethis_get_options_array();
  $publisher = $current_options_array['publisherID'];
  $form['sharethis_publisherID'] = array(
    '#title' => t("Insert a publisher key (optional)."),
    '#description' => t("When you install the module, we create a random publisher key.  You can register the key with ShareThis by contacting customer support.  Otherwise, you can go to <a href='http://www.sharethis.com/account'>ShareThis</a> and create an account.<br />Your official publisher key can be found under 'My Account'.<br />It allows you to get detailed analytics about sharing done on your site."),
    '#type' => 'textfield',
    '#default_value' => $publisher,
  );

  $form['sharethis_twitter_suffix'] = array(
    '#title' => t("Twitter Suffix"),
    '#description' => t("Optionally append a Twitter handle, or text, so that you get pinged when someone shares an article. Example: <em>via @YourNameHere</em>"),
    '#type' => 'textfield',
    '#default_value' => variable_get('sharethis_twitter_suffix', ''),
  );

  $form['sharethis_twitter_handle'] = array(
    '#title' => t('Twitter Handle'),
    '#description' => t('Twitter handle to use when sharing.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('sharethis_twitter_handle', ''),
  );

  return system_settings_form($form);
}

function btr_sharethis_config_validate($form, &$form_state) {
  // Sanitize the publisher ID option.  Since it's a text field, remove anything that resembles code
  $form_state['values']['sharethis_publisherID'] = filter_xss($form_state['values']['sharethis_publisherID'], array());

  // Ensure default value for twitter suffix
  $form_state['values']['sharethis_twitter_suffix'] = (isset($form_state['values']['sharethis_twitter_suffix'])) ? $form_state['values']['sharethis_twitter_suffix'] : '';

  // Ensure default value for twitter handle
  $form_state['values']['sharethis_twitter_handle'] = (isset($form_state['values']['sharethis_twitter_handle'])) ? $form_state['values']['sharethis_twitter_handle'] : '';
}
