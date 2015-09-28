<?php
/**
 * @file
 * Hybridauth hooks and form customizations.
 */

/**
 * Implements hook_hybridauth_registration_form().
 */
function btrUser_hybridauth_registration_form($data) {
  if (isset($data['translation_lng']))  return FALSE;

  $destination = drupal_parse_url($_GET['destination']);
  if (isset($destination['query']['lng']))  return FALSE;

  return TRUE;
}

/**
 * Implements hook_form_FORM_ID_alter() for hybridauth_additional_info_form.
 */
function btrUser_form_hybridauth_additional_info_form_alter(&$form, &$form_state, $form_id) {
  if (isset($_GET['lng']))  return;
  if (isset($_GET['destination'])) {
    $destination = drupal_parse_url($_GET['destination']);
    if (isset($destination['query']['lng']))  return;
  }

  // Field translation_lng.
  $form['fset']['translation_lng'] = array(
    '#type' => 'select',
    '#title' => t('Translation Language'),
    '#description' => t('The language of translations. You will help with the translations of this language (review existing translations or submit new ones).'),
    '#options' => btr::languages_get_list(),
  );

  // $form['#validate'][] = '_btrUser_form_hybridauth_additional_info_form_validate';
  array_unshift($form['#submit'], '_btrUser_form_hybridauth_additional_info_form_submit');
}

/*function _btrUser_form_hybridauth_additional_info_form_validate($form, &$form_state) {
}*/

function _btrUser_form_hybridauth_additional_info_form_submit($form, &$form_state) {
  if (isset($form_state['values']['translation_lng'])) {
    $form_state['values']['data']['translation_lng'] = $form_state['values']['translation_lng'];
  }
}

/**
 * Implements hook_hybridauth_userinfo_alter().
 */
function btrUser_hybridauth_userinfo_alter(&$userinfo, $data) {
  $destination = drupal_parse_url($_GET['destination']);

  // Fix a bug of hybridauth.
  $userinfo['init'] = $userinfo['mail'];

  // Set the translation_lng on the user profile.
  if (isset($destination['query']['lng'])) {
    $userinfo['translation_lng'] = $destination['query']['lng'];
  }
  elseif (isset($data['translation_lng'])) {
    $userinfo['translation_lng'] = $data['translation_lng'];
  }

  // Set the projects on the user profile.
  if (isset($destination['query']['proj'])) {
    $arr_projects = explode(',', $destination['query']['proj']);
    $userinfo['subscribed_projects'] = $arr_projects;
  }
}
