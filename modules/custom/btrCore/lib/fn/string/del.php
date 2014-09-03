<?php
/**
 * @file
 * Definition of function string_del().
 */

namespace BTranslator;

/**
 * Delete the string with the given id.
 */
function string_del($sguid) {
  btr_delete('btr_strings')->condition('sguid', $sguid)->execute();
  btr_delete('btr_locations')->condition('sguid', $sguid)->execute();
  btr_delete('btr_translations')->condition('sguid', $sguid)->execute();
}
