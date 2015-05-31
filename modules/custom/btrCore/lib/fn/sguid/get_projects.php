<?php
/**
 * @file
 * Get a random sguid.
 */

namespace BTranslator;

/**
 * Return an array of the projects that contain the given string.
 *
 * Each item of the array is of the form 'origin/project'.
 */
function sguid_get_projects($sguid) {
  if (empty($sguid))  return NULL;

  $args = array(':sguid' => $sguid);
  $get_projects = "
      SELECT p.origin, p.project
      FROM {btr_locations} l
      LEFT JOIN {btr_templates} tpl ON (tpl.potid = l.potid)
      LEFT JOIN {btr_projects} p ON (p.pguid = tpl.pguid)
      WHERE l.sguid = :sguid
  ";
  $result = btr::db_query($get_projects, $args)->fetchAll();
  $projects = array();
  foreach ($result as $proj) {
    $projects[] = $proj->origin . '/' . $proj->project;
  }
  if (empty($projects))  $projects = NULL;

  return $projects;
}
