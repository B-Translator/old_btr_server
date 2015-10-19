<?php
/**
 * @file
 * Definition of function vocabulary_string_del().
 */

namespace BTranslator;
use \btr;

/**
 * Delete a string from a vocabulary.
 *
 * @param $name
 *   The name of the vocabulary.
 *
 * @param $lng
 *   The language of the vocabulary.
 *
 * @param $sguid
 *   ID of the string to be deleted.
 *
 * @return
 *   FALSE if permissions are not sufficient, otherwise TRUE
 */
function vocabulary_string_del($name, $lng, $sguid) {
  // Set project variables.
  $origin = 'vocabulary';
  $project = $name . '_' . $lng;

  // Only a project admin can delete strings.
  if (!btr::user_is_project_admin($origin, $project))  return FALSE;

  // Remove the string from the 'materialized view' table of the project.
  $q = 'SELECT string FROM {btr_strings} WHERE sguid = :sguid';
  $string = btr::db_query($q, [':sguid' => $sguid])->fetchField();
  $table = 'btr_mv_' . strtolower($project);
  btr::db_delete($table)->condition('string', $string)->execute();

  // Get the template of the project.
  $pguid = sha1($origin . $project);
  $q = 'SELECT potid FROM {btr_templates} WHERE pguid = :pguid';
  $potid = btr::db_query($q, [':pguid' => $pguid])->fetchField();

  // Remove the string from the template of the project.
  btr::db_delete('btr_locations')
    ->condition('potid', $potid)
    ->condition('sguid', $sguid)
    ->execute();

  // Delete any translations of the string.
  $q = 'SELECT tguid FROM {btr_translations} WHERE sguid = :sguid';
  $tguid_list = btr::db_query($q, [':sguid' => $sguid])->fetchCol();
  foreach ($tguid_list as $tguid) {
    btr::translation_del($tguid, $notify=FALSE);
  }

  // Delete the string itself.
  btr::db_delete('btr_strings')->condition('sguid', $sguid)->execute();

  return TRUE;
}
