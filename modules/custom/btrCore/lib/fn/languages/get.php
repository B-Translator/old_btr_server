<?php
/**
 * @file
 * Get the languages that are supported by the application.
 */

namespace BTranslator;
use \btr;

/**
 * Get a list of supported languages.
 *
 * @return
 *   Array of language codes.
 */
function languages_get() {
  $langs = array();

  $btr_langs = variable_get('btr_languages', '');
  foreach (explode(' ', $btr_langs) as $lng) {
    if ($lng == '')  continue;
    $langs[] = $lng;
  }

  if (empty($langs)) {
    $langs = array('fr');
  }

  return $langs;
}

/**
 * Get a list of supported languages to be used in selection options.
 *
 * @return
 *   Associated array with language codes as keys and language names as
 *   values.
 */
function languages_get_list() {
  $list = array();
  $all_langs = \db_query('SELECT * FROM btr_languages')->fetchAllAssoc('code');
  $langs = btr::languages_get();
  foreach ($langs as $lng) {
    $list[$lng] = isset($all_langs[$lng]) ? $all_langs[$lng]->name : $lng;
  }

  return $list;
}

/**
 * Get an array of the supported languages and their details.
 *
 * @return
 *   Associated array with language codes as keys and language details as
 *   values.
 */
function languages_get_details() {
  $lng_details = array();
  $all_langs = \db_query('SELECT * FROM btr_languages')->fetchAllAssoc('code');
  $langs = btr::languages_get();
  foreach ($langs as $lng) {
    if (isset($all_langs[$lng])) {
      $lng_details[$lng] = array(
        'code' => $lng,
        'name' => $all_langs[$lng]->name,
        'direction' => $all_langs[$lng]->direction,
        'plurals' => $all_langs[$lng]->plurals,
      );
    }
    else {
      $lng_details[$lng] = array(
        'code' => $lng,
        'name' => "Unknown ($lng)",
        'direction' => LANGUAGE_LTR,
        'plurals' => 2,
      );
    }
  }

  return $lng_details;
}
