<?php
/**
 * @file
 * AJAX callback functions.
 */

/**
 * Retrieve a JSON list of autocomplete suggestions for projects.
 */
function btr_data_project_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $db = $GLOBALS['btr_db'];
    $query = "SELECT DISTINCT project
              FROM {btr_projects}
              WHERE project LIKE :str ORDER BY project";
    $args = array(':str' => $string . '%');
    $result = $db->queryRange($query, 0, 10, $args);
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
function btr_data_origin_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $db = $GLOBALS['btr_db'];
    $query = "SELECT DISTINCT origin
              FROM {btr_projects}
              WHERE origin LIKE :str ORDER BY origin";
    $args = array(':str' => $string . '%');
    $result = $db->queryRange($query, 0, 10, $args);
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
function btr_data_user_autocomplete($lng, $string = '') {
  $matches = array();
  if ($string) {
    $db = $GLOBALS['btr_db'];
    $query = "SELECT name FROM {btr_users}
              WHERE name LIKE :str AND ulng = :ulng
              ORDER BY name";
    $args = array(
      ':str' => $string . '%',
      ':ulng' => $lng,
    );
    $result = $db->queryRange($query, 0, 10, $args);
    foreach ($result as $user) {
      $matches[$user->name] = check_plain($user->name);
    }
  }
  print drupal_json_encode($matches);
  exit();
}


/**
 * Return string context, a list of related projects (where the string appears), etc.
 * This callback is invoked from JavaScript and is used as an AJAX provider.
 *
 * @param $sguid
 *   Id of the string.
 */
function btr_data_string_details($sguid) {

  $output = '';

  // Get the context of this string.
  $db = $GLOBALS['btr_db'];
  $query = "SELECT context FROM {btr_strings} WHERE sguid = :sguid";
  $args = array(':sguid' => $sguid);
  $context = $db->query($query, $args)->fetchField();
  if (!empty($context)) {
    $output .= '<h3>' . t('Used with context: %context', array('%context' => $context)) . '</h3>';
  }

  // List projects where this string is used.
  $output .= '<h3>' . t('Used on these projects:') . '</h3>';
  $sql = "
    SELECT CONCAT(p.origin, ' / ', p.project) AS proj
    FROM {btr_strings} s
    RIGHT JOIN {btr_locations} l ON (l.sguid = s.sguid)
    RIGHT JOIN {btr_templates} t ON (t.potid = l.potid)
    RIGHT JOIN {btr_projects} p ON (p.pguid = t.pguid)
    WHERE s.sguid = :sguid
    ORDER BY p.origin, p.project
  ";
  $args = array(':sguid' => $sguid);
  $project_list = $db->query($sql, $args)->fetchCol();
  $output .= theme('item_list', array('items' => $project_list));

  print $output;
  exit(0);
}
