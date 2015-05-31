<?php
/**
 * @file
 * Function: translation_get()
 */

namespace BTranslator;

/**
 * Return a translation from its ID.
 */
function translation_get($tguid) {
  $translation = btr::db_query(
    'SELECT translation FROM {btr_translations} WHERE tguid = :tguid',
    array(':tguid' => $tguid)
  )->fetchField();
  return $translation;
}
