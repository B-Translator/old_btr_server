<?php
/**
 * @file
 * Definition of function string_del().
 */

namespace BTranslator;

/**
 * Delete the string with the given id.
 * Return FALSE if permissions are not sufficient,
 * otherwise return TRUE.
 */
function string_del($sguid) {
  if (!btr::utils_user_has_project_role('admin', $sguid) and !user_access('btranslator-admin')) {
    return FALSE;
  }

  btr_delete('btr_strings')->condition('sguid', $sguid)->execute();
  btr_delete('btr_locations')->condition('sguid', $sguid)->execute();
  btr_delete('btr_translations')->condition('sguid', $sguid)->execute();

  return TRUE;
}
