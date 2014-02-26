<?php
/**
 * @file
 * Functions specific to the menu path: translations/vote .
 */

/**
 * Include utility and theme functions.
 */
require_once(dirname(__FILE__) . '/list/list.inc');
require_once(dirname(__FILE__) . '/utils.inc');

/**
 * Menu callback: translations/vote
 * Vote the best translation for a string, or suggest a better translation.
 */
function btrClient_vote($lng =NULL, $sguid =NULL, $one_time_login =NULL) {

  if ($one_time_login != NULL) {
    btrClient_login_one_time($one_time_login);
    drupal_goto("translations/$lng/$sguid");
    return;
  }

  if ($lng == NULL) {
    $lng = variable_get('btrClient_translation_lng', 'fr');
  }

  if ($sguid==NULL)  {
    $sguid = 'next';
  }

  if (in_array($sguid, array('next', 'translated', 'untranslated'))) {
    $result = $GLOBALS['btr']->get_random_sguid(
      array('target' => $sguid, 'lng' => $lng)
    );
    $sguid = $result['sguid'];
    drupal_goto("translations/$lng/$sguid");
    return;
  }
  // last_sguid is used in search, to get similar results
  $_SESSION['btrClient']['last_sguid'] = $sguid;

  // If there is a $_SESSION['btr']['translate_form']['state'],
  // then this is a redirect after login. Call the submit function again.
  if (isset($_SESSION['btr']['translate_form']['state'])) {
    $form_state = $_SESSION['btr']['translate_form']['state'];
    unset($_SESSION['btr']['translate_form']['state']);
    //drupal_form_submit('btrClient_translate_form', $form_state);
    btrClient_translate_form_submit(NULL, $form_state);
  }

  // Get the string and its translations.
  $strings = $GLOBALS['btr']->get_translations($sguid, $lng);
  if (empty($strings)) {
    drupal_set_message(t('No string found! Please check preferred projects and other settings!'), 'warning');
    drupal_goto("/");
    return;
  }

  // Set the title.
  drupal_set_title(t('Vote Translations'));

  // Add the CSS and JS files.
  drupal_add_css(drupal_get_path('module', 'btrClient') . '/editor/editor.css');
  drupal_add_js(drupal_get_path('module', 'btrClient') . '/editor/jquery.worddiff.js');
  drupal_add_js(drupal_get_path('module', 'btrClient') . '/editor/editor.js');

  // Add RTL style if the current language's direction is RTL
  $languages = btr_get_languages();
  if ($languages[$lng]['direction'] == LANGUAGE_RTL) {
    drupal_add_css(drupal_get_path('module', 'btrClient') . '/editor-rtl.css');
  }

  // Output the string and its translations.
  $output = drupal_get_form('btrClient_translate_form', $strings, $lng);

  return $output;
}

function btrClient_login_one_time($one_time_login =NULL) {

  if ($one_time_login == NULL)  return FALSE;

  // Check if the user is already logged in.
  global $user;
  if ($user->uid)  return FALSE;

  // Get $timestamp, $uid, and $hashed_pass
  $parts = preg_split('/\./', $one_time_login, 3);
  $timestamp = isset($parts[0]) ? $parts[0] : '';
  $uid = isset($parts[1]) ? $parts[1] : '';
  $hashed_pass = isset($parts[2]) ? $parts[2] : '';
  if ($timestamp == '' or $uid == '' or $hashed_pass == '')  return FALSE;

  // Get the user details.
  $account = user_load($uid);
  if (!isset($account) || $account->status == 0)  return FALSE;

  // Check the timestamp.
  $timeout = 86400;  // 24 hours
  $current = REQUEST_TIME;
  if ($current - $timestamp > $timeout) {
    drupal_set_message(t('Login link has expired.'));
    return FALSE;
  }

  // Check the hashed password.
  if ($hashed_pass != user_pass_rehash($account->pass, $timestamp, $account->login)) {
    drupal_set_message(t('Could not validate login link.'));
    return FALSE;
  }

  // Login the new user.
  $user = $account;
  user_login_finalize();
  return TRUE;
}
