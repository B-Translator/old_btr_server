<?php
/**
 * @file
 * Function: string_get_translations()
 */

namespace BTranslator;
use \btr;

/**
 * Return a string and its translations.
 *
 * @param $sguid
 *   ID of the string.
 *
 * @param $lng
 *   Language of translations.
 *
 * @return
 *   array($string, $translations)
 */
function string_get_translations($sguid, $lng) {
  $query = btr::db_select('btr_strings', 's')
    ->fields('s', array('sguid'))
    ->where('s.sguid = :sguid', array(':sguid' => $sguid));
  $strings = btr::string_details($query, $lng);

  $string = $strings[0]->string;
  $translations = array();
  foreach ($strings[0]->translations as $obj_translation) {
    $translations[] = $obj_translation->translation;
  }

  return array($string, $translations);
}
