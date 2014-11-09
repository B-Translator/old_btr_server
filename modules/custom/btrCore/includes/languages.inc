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
    'sq' => array(
      'code' => 'sq',
      'name' => 'Albanian',
      'encoding' => 'latin1',
      'direction' => LANGUAGE_LTR,
      'plurals' => 2,
    ),
    'bg' => array(
      'code' => 'bg',
      'name' => 'Bulgarian',
      'encoding' => 'ISO-8859-5',
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
    'de' => array(
      'code' => 'de',
      'name' => 'German',
      'encoding' => 'latin1',
      'direction' => LANGUAGE_LTR,
      'plurals' => 2,
    ),
    'it' => array(
      'code' => 'it',
      'name' => 'Italian',
      'encoding' => 'latin1',
      'direction' => LANGUAGE_LTR,
      'plurals' => 2,
    ),
    'es' => array(
      'code' => 'es',
      'name' => 'Spanish',
      'encoding' => 'latin1',
      'direction' => LANGUAGE_LTR,
      'plurals' => 2,
    ),
  );

  return $arr_langs;
}
