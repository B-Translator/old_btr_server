<?php
/**
 * @file
 * Function vocabulary_ls().
 */

namespace BTranslator;
use \btr;

/**
 * Return a list of vocabularies.
 *
 * @param $lng
 *   Language of the vocabularies (can contain '%' for LIKE matches).
 *
 * @param $name
 *   Name of the vocabularies (can contain '%' for LIKE matches).
 */
function vocabulary_ls($lng = '%', $name = '%') {
  // Get the list of projects.
  $origin = 'vocabulary';
  $project = $name . '\\_' . $lng;
  $project_list = btr::project_ls($origin, $project);

  // Convert it into a suitable array of vocabularies.
  $vocabulary_list = [];
  foreach ($project_list as $project) {
    $project = str_replace('vocabulary/', '', $project);
    $lng = preg_replace('/^.*_/', '', $project);
    $name = preg_replace('/_[^_]*$/', '', $project);
    $vocabulary_list[$lng][] = $name;
  }

  // Return the list.
  return $vocabulary_list;
}
