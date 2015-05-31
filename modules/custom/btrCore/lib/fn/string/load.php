<?php
/**
 * @file
 * Function: string_load()
 */

namespace BTranslator;
use \btr;

/**
 * Get details for a list of strings.
 *
 * @param $arr_sguid
 *   List of string IDs to be loaded.
 *
 * @param $lng
 *   Language of translations.
 *
 * @return
 *   An array of strings, translations and votes, where each string
 *   is an associative array, with translations and votes as nested
 *   associative arrays.
 */
function string_load($arr_sguid, $lng) {
  $query = btr::db_select('btr_strings', 's')
    ->fields('s', array('sguid'))
    ->condition('s.sguid', $arr_sguid, 'IN');

  // Get alternative langs from the preferences of the user.
  $alternative_langs = array();
  global $user;
  $user = user_load($user->uid);
  if (isset($user->auxiliary_languages) and is_array($user->auxiliary_languages)) {
    $alternative_langs = $user->auxiliary_languages;
  }

  return btr::string_details($query, $lng, $alternative_langs);
}
