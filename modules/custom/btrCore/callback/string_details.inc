<?php
/**
 * @file
 * Callback for string_details.
 */

/**
 * Return string context, a list of related projects (where the string appears), etc.
 *
 * @param $sguid
 *   Id of the string.
 */
function btrCore_string_details($sguid) {

  $details = [
    'context' => '',
    'projects' => [],
  ];

  // Get the context of this string.
  $query = "SELECT context FROM {btr_strings} WHERE sguid = :sguid";
  $args = array(':sguid' => $sguid);
  $context = btr::db_query($query, $args)->fetchField();
  $details['context'] = $context;

  // Get the projects where this string is used.
  $sql = "
    SELECT DISTINCT p.origin, p.project
    FROM {btr_strings} s
    RIGHT JOIN {btr_locations} l ON (l.sguid = s.sguid)
    RIGHT JOIN {btr_templates} t ON (t.potid = l.potid)
    RIGHT JOIN {btr_projects} p ON (p.pguid = t.pguid)
    WHERE s.sguid = :sguid
    ORDER BY p.origin, p.project
  ";
  $args = array(':sguid' => $sguid);
  $result = btr::db_query($sql, $args)->fetchAll();
  foreach ($result as $row) {
    $project = $row->origin . '/' . $row->project;
    $details['projects'][] = $project;
  }

  // Return the string details.
  print drupal_json_encode($details);
  exit();
}
