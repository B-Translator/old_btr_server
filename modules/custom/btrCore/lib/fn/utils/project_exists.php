<?php
/**
 * @file
 * Function: utils_project_exists()
 */

namespace BTranslator;


/**
 * Check weather the given origin/project exists.
 *
 * @param $origin
 *   The origin of the project.
 *
 * @param $project
 *   The name of the project.
 *
 * @return
 *   TRUE if such a project exists, otherwise FALSE.
 */
function utils_project_exists($origin, $project) {
  $project = btr::db_query(
    'SELECT project FROM {btr_projects}
     WHERE BINARY origin = :origin AND BINARY project = :project',
    array(
      ':origin' => $origin,
      ':project' => $project,
    ))
    ->fetchField();

  return ($project ? TRUE : FALSE);
}
