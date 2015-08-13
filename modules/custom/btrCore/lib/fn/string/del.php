<?php
/**
 * @file
 * Definition of function string_del().
 */

namespace BTranslator;
use \btr;

/**
 * Delete the string with the given id from the given project.
 * Return FALSE if permissions are not sufficient, otherwise return TRUE.
 */
function string_del($sguid, $project, $origin = 'vocabulary') {
  // Only a project admin can delete strings.
  if (!btr::user_is_project_admin($origin, $project))  return FALSE;

  // Remove the string from the 'materialized view' table of the project.
  if ($origin=='vocabulary') {
    // Get the string.
    $q = 'SELECT string FROM {btr_strings} WHERE sguid = :sguid';
    $string = btr::db_query($q, array(':sguid' => $sguid))->fetchField();

    // Remove it from the corresponding "mv" table.
    $table = 'btr_mv_' . strtolower($project);
    btr::db_delete($table)->condition('string', $string)->execute();
  }

  // Get the template of the project.
  $pguid = sha1($origin . $project);
  $q = 'SELECT potid FROM {btr_templates} WHERE pguid = :pguid';
  $potid = btr::db_query($q, array(':pguid' => $pguid))->fetchField();

  // Remove the string from the template of the project project.
  btr::db_delete('btr_locations')
    ->condition('potid', $potid)
    ->condition('sguid', $sguid)
    ->execute();

  // Decrement the count of the string (which keeps the number of projects).
  btr::db_update('btr_strings')
    ->expression('count', 'count - 1')
    ->condition('sguid', $sguid)
    ->execute();

  // If the count is 0, remove the string and any translations.
  $q = 'SELECT count FROM {btr_strings} WHERE sguid = :sguid';
  $count = btr::db_query($q, array(':sguid' => $sguid))->fetchField();
  if (!$count) {
    // Get any translations related to the string.
    $q = 'SELECT tguid FROM {btr_translations} WHERE sguid = :sguid';
    $tguid_list = btr::db_query($q, array(':sguid' => $sguid))->fetchCol();

    // Delete the string itself.
    btr::db_delete('btr_strings')->condition('sguid', $sguid)->execute();

    // Delete any translations (without notification).
    foreach ($tguid_list as $tguid) {
      btr::translation_del($tguid, FALSE);
    }
  }

  return TRUE;
}
