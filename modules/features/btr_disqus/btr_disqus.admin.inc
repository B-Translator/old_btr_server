<?php
/**
 * @file
 * Configuration of Disqus (custom/private settings).
 */

/**
 * Implements hook_menu().
 */
function btr_disqus_menu() {
  $items = array();
  $items['admin/config/btr/disqus'] = array(
    'title'            => 'Disqus',
    'description'      => 'Private Disqus settings.',
    'page callback'    => 'drupal_get_form',
    'page arguments'   => array('btr_disqus_config'),
    'access arguments' => array('btranslator-admin'),
  );

  return $items;
}


/**
 * Custom settings for Disqus.
 *
 * @return
 *   An array containing form items to place on the module settings page.
 */
function btr_disqus_config() {
  $form = array();

  $form['disqus_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Shortname'),
    '#description' => t('The website shortname that you registered Disqus with. If you registered https://example.disqus.com, you would enter "example" here.'),
    '#default_value' => variable_get('disqus_domain', ''),
  );

  $form['disqus_userapikey'] = array(
    '#type' => 'textfield',
    '#title' => t('User API Key'),
    '#description' => t('The API key of the administrator account on Disqus. You can get yours <a href="@key">here</a>.', array('@key' => 'https://disqus.com/api/get_my_key/')),
    '#default_value' => variable_get('disqus_userapikey', ''),
  );

  $form['disqus_publickey'] = array(
    '#type' => 'textfield',
    '#title' => t('Public Key'),
    '#default_value' => variable_get('disqus_publickey', ''),
  );

  $form['disqus_secretkey'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret Key'),
    '#default_value' => variable_get('disqus_secretkey', ''),
  );

  $form['disqus_developer'] = array(
    '#type' => 'checkbox',
    '#title' => t('Testing'),
    '#description' => t('When enabled, uses the <a href="https://docs.disqus.com/help/2/">disqus_developer</a> flag to tell Disqus that you are in a testing environment. Threads will not display on the public community page with this set.'),
    '#default_value' => variable_get('disqus_developer', FALSE),
  );

  return system_settings_form($form);
}
