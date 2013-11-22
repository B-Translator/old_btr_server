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

  if ($sguid==NULL)  { $sguid = 'next'; }
  if (in_array($sguid, array('next', 'translated', 'untranslated'))) {
    switch ($sguid) {
      case 'next':
        $sguid = btr_sguid_get_next();
        break;
      case 'translated':
        $sguid = btr_sguid_get_translated($lng);
        break;
      case 'untranslated':
        $sguid = btr_sguid_get_untranslated($lng);
        break;
    }
    if (empty($sguid)) {
      drupal_set_message(t('No string found! Please check preferred projects and other settings!'), 'warning');
      drupal_goto("/");
      return;
    }
    $_SESSION['sguid'] = $sguid;
    drupal_goto("translations/$lng/$sguid");
    return;
  }

  // Add the CSS and JS files.
  drupal_add_css(drupal_get_path('module', 'btrClient') . '/editor/editor.css');
  drupal_add_js(drupal_get_path('module', 'btrClient') . '/editor/jquery.worddiff.js');
  drupal_add_js(drupal_get_path('module', 'btrClient') . '/editor/editor.js');

  // Get languages and language codes
  $languages = btr_get_languages();
  $lng_codes = array_keys($languages);

  // Add RTL style if the current language's direction is RTL
  if ($languages[$lng]['direction'] == LANGUAGE_RTL) {
    drupal_add_css(drupal_get_path('module', 'btrClient') . '/editor-rtl.css');
  }

  /*
  // Add missing breadcrumb.
  drupal_set_breadcrumb(
    array(
      l(t('Home'), NULL),
      l(t('Translations'), 'translations'),
    )
  );
  */

  // Set the title.
  drupal_set_title(t('Vote Translations'));

  // Get the string and its translations.
  //$strings = btr_get_strings(array($sguid), $lng);
  //$strings = json_decode(json_encode($strings), true);
  try {
    $strings = $GLOBALS['btr']->get_translations($sguid, 'sq');
  }
  catch (Exception $e) {
    drupal_set_message($e->getMessage(), 'error');
  }
  //if ($strings) dpm($strings);  //debug

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
