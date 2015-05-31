<?php
/**
 * @file
 * Definition of function project_ls() which returns a list of projects.
 */

namespace BTranslator;
use \btr;

/**
 * Return a list of all the imported projects, filtered by origin/project.
 *
 * Variables $origin and $project can contain '%' (for LIKE matches).
 * If $project=='-' then only a list of 'origin' is outputed,
 * otherwise a list of 'origin/project'.
 *
 * @param $origin
 *   The pattern for matching the origin.
 *
 * @param $project
 *   The pattern for matching the project.
 */
function project_ls($origin =NULL, $project =NULL) {
  // Start building the query.
  $query = btr::db_select('btr_projects', 'p')
    ->fields('p', array('origin'))
    ->orderBy('origin');

  if ($project == '-') {
    $query->distinct();
  }
  else {
    $query->fields('p', array('project'))
      ->orderBy('project');
  }

  // Build the condition of the query.
  if (!empty($origin)) {
    $query->condition('origin', $origin, 'LIKE');
  }
  if (!empty($project) && $project != '-') {
    $query->condition('project', $project, 'LIKE');
  }

  // Execute the query and get the results.
  $results = $query->execute()->fetchAll();

  // Build the list of projects as an array.
  $project_list = array();
  foreach ($results as $record) {
    $item = $record->origin;
    if ($project != '-') {
      $item .= '/' . $record->project;
    }
    $project_list[] = $item;
  }

  return $project_list;
}
