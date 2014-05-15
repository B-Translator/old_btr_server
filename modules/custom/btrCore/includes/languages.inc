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
  module_load_include('inc', 'btrCore', 'languages');
  return $arr_langs;
}
