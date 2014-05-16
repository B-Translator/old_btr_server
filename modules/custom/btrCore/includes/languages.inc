<?php

/**
 * Menu callback for translations/languages.
 * Returns a json list of languages and their details.
 */
function btrCore_languages() {
  $languages = btr_get_languages();
  drupal_json_output($languages);
  drupal_exit();
}

/**
 * Returns an array of languages and their details.
 */
function btr_get_languages() {

  // Translation languages supported by the B-Translator Server.
  // Do not remove 'fr', because sometimes French translations
  // are used instead of template files (when they are missing).
  $arr_langs = array(
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
