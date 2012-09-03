<?php
/**
 * Functions that are common for all the pages.
 */

/**
 * Returns an array of languages and their details.
 */
function l10n_feedback_get_languages() {

  $arr_langs = array(
    'en' => array(
      'code' => 'en',
      'name' => 'English',
      'encoding' => 'latin1',
      'direction' => LANGUAGE_LTR,
      'plurals' => 2,
    ),
    'fr' => array(
      'code' => 'fr',
      'name' => 'French',
      'encoding' => 'latin1',
      'direction' => LANGUAGE_LTR,
      'plurals' => 2,
    ),
    'sq' => array(
      'code' => 'sq',
      'name' => 'Albanian',
      'encoding' => 'latin1',
      'direction' => LANGUAGE_LTR,
      'plurals' => 2,
    ),
  );

  return $arr_langs;
}

/**
 * Get and return the translation lng from the settings (profile)
 * of the current user. If not specified, return the default
 * translation language of the site.
 */
function l10n_feedback_get_translation_lng() {

  global $user;
  $account = user_load($user->uid);
  $field_translation_language = field_get_items('user', $account, 'field_translation_language');

  if (isset($field_translation_language[0]['value'])) {
    $lng = $field_translation_language[0]['value'];
  } else {
    $lng = variable_get('l10n_feedback_default_lng', 'fr');
  }

  return $lng;
}
?>