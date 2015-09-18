<?php
/**
 * @file
 * Function: project_owner()
 */

namespace BTranslator;
use \btr;

/**
 * Get the uid of the project owner.
 *
 * @param $origin
 *   The origin of the project.
 *
 * @param $project
 *   The name of the project.
 *
 * @return
 *   The uid of the project owner.
 */
function project_owner($origin, $project) {
  $uid = btr::db_query(
    'SELECT uid FROM {btr_projects} WHERE origin = :origin AND project = :project',
    [
      ':origin' => $origin,
      ':project' => $project,
    ])
    ->fetchField();

  return $uid;
}
