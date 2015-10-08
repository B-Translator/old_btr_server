<?php
/**
 * @file
 * Get the list of terms in a vocabulary and all the suggested translations.
 */

namespace BTranslator;
use \btr;

/**
 * Get the list of terms in a vocabulary and all the suggested translations.
 *
 * @param $vocab
 *   The name of the vocabulary.
 *
 * @param $lng
 *   The language of the vocabulary.
 *
 * @return
 *   Array of the terms and translations.
 */
function vocabulary_get($vocab, $lng, $format = NULL) {
  $vocabulary = $vocab . '_' . $lng;

  // Get the template id (potid) of this vocabulary.
  $query = "SELECT potid FROM {btr_templates} WHERE pguid = :pguid";
  $origin = 'vocabulary';
  $project = $vocabulary;
  $params = array(':pguid' => sha1($origin . $project));
  $potid = btr::db_query($query, $params)->fetchField();

  // Build the query for getting all the strings of this vocabulary.
  $query = btr::db_select('btr_locations', 'l')
    ->fields('l', array('sguid'))
    ->condition('l.potid', $potid);
  $query->leftJoin('btr_strings', 's', 's.sguid = l.sguid');
  $query->orderBy('s.string');

  // Get the strings and their translations.
  $strings = btr::string_details($query, $lng);

  // Simplify the structure of the result.
  $result = array();
  foreach ($strings as $str) {
    $translations = array();
    foreach ($str->translations as $trans) {
      $translations[] = $trans->translation;
    }
    $result[$str->string] = $translations;
  }

  return $result;
}
