<?php

/**
 * Menu callback for translations/languages.
 * Returns a json list of languages and their details.
 */
function btrCore_languages() {
  $languages = btr_get_languages();
  print drupal_json_encode($languages);
  exit(0);
}

/**
 * Returns an array of languages and their details.
 */
function btr_get_languages() {

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
