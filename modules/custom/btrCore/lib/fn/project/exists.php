<?php
/**
 * @file
 * Function: project_exists()
 */

namespace BTranslator;
use \btr;

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
function project_exists($origin, $project) {
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
