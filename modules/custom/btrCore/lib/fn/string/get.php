<?php
/**
 * @file
 * Function: string_get()
 */

namespace BTranslator;
use \btr;

/**
 * Get a string from its ID.
 */
function string_get($sguid) {
  $string = btr::db_query(
    'SELECT string FROM {btr_strings} WHERE sguid = :sguid',
    array(':sguid' => $sguid)
  )->fetchField();
  return $string;
}
