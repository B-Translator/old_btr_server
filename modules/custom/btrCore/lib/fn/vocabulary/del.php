<?php
/**
 * @file
 * Definition of function vocabulary_del() which is used for deleting vocabularies.
 */

namespace BTranslator;
use \btr;

/**
 * Delete the given vocabulary.
 *
 * @param $name
 *   The name of the vocabulary.
 *
 * @param $lng
 *   The language of the vocabulary.
 */
function vocabulary_del($name, $lng) {
  $origin = 'vocabulary';
  $project = $name . '_' . $lng;
  btr::project_del($origin, $project);

  // Delete the contact form.
  \db_delete('contact')->condition('category', $project)->execute();

  // Delete the mv table.
  $table = 'btr_mv_' . strtolower($project);
  btr::db_query("DROP TABLE IF EXISTS {$table}");
}
