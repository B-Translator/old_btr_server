<?php
/**
 * @file
 * AJAX callback functions.
 */

/**
 * Retrieve a JSON list of autocomplete suggestions for projects.
 */
function btrCore_project_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $query = "SELECT DISTINCT project
              FROM {btr_projects}
              WHERE project LIKE :str ORDER BY project";
    $args = array(':str' => $string . '%');
    $result = btr::db_query_range($query, 0, 10, $args);
    foreach ($result as $project) {
      $matches[$project->project] = check_plain($project->project);
    }
  }
  print drupal_json_encode($matches);
  exit();
}

/**
 * Retrieve a JSON list of autocomplete suggestions for origins of projects.
 */
function btrCore_origin_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $query = "SELECT DISTINCT origin
              FROM {btr_projects}
              WHERE origin LIKE :str ORDER BY origin";
    $args = array(':str' => $string . '%');
    $result = btr::db_query_range($query, 0, 10, $args);
    foreach ($result as $project) {
      $matches[$project->origin] = check_plain($project->origin);
    }
  }
  print drupal_json_encode($matches);
  exit();
}

/**
 * Retrieve a JSON list of autocomplete suggestions for users.
 */
function btrCore_user_autocomplete($lng, $string = '') {
  $matches = array();
  if ($string) {
    $query = "SELECT name FROM {btr_users}
              WHERE name LIKE :str AND ulng = :ulng
              ORDER BY name";
    $args = array(
      ':str' => $string . '%',
      ':ulng' => $lng,
    );
    $result = btr::db_query_range($query, 0, 10, $args);
    foreach ($result as $user) {
      $matches[$user->name] = check_plain($user->name);
    }
  }
  print drupal_json_encode($matches);
  exit();
}

/**
 * Retrieve a JSON list of autocomplete suggestions for strings.
 */
function btrCore_string_autocomplete($origin = '*', $project = '*', $string = '') {
  $string = trim($string);
  if (empty($string)) {
    print drupal_json_encode(array());
    exit();
  }

  $origin = empty($origin) ? '*' : $origin;
  $project = empty($project) ? '*' : $project;

  // Get the query.
  if ($origin == 'vocabulary') {
    $table = 'btr_mv_' . strtolower(check_plain($project));
    $query = "SELECT string FROM {$table}
              WHERE string LIKE :string
              ORDER BY string ASC";
    $query_args = array(':string' => '%' . $string . '%');
  }
  else {
    // Get the query arguments and the condition for joining with project.
    $query_args = array(':string' => $string . '%');
    $project_join_condition = 'p.pguid = t.pguid';
    if ($project != '*') {
      $query_args[':project'] = $project;
      $project_join_condition .= ' AND p.project = :project';
    }
    if ($origin != '*') {
      $query_args[':origin'] = $origin;
      $project_join_condition .= ' AND p.origin = :origin';
    }

    // Build the query.
    $query = "SELECT DISTINCT s.string FROM {btr_strings} s ";
    if ($origin != '*' or $project != '*') {
      $query .= "JOIN {btr_locations} l ON (l.sguid = s.sguid)
               JOIN {btr_templates} t ON (t.potid = l.potid)
               JOIN {btr_projects}  p ON ($project_join_condition) ";
    }
    $query .= "WHERE s.string LIKE :string
             ORDER BY s.string ASC";
  }

  // Run the query and get the results.
  $result = btr::db_query_range($query, 0, 10, $query_args);
  $matches = array();
  foreach ($result as $str) {
    $matches[$str->string] = check_plain($str->string);
  }

  // Return the matches.
  print drupal_json_encode($matches);
  exit();
}
