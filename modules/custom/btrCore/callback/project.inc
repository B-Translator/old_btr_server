<?php
/**
 * @file
 * Callback functions for projects.
 */

/**
 * Callback function for the menu 'project/sync'
 *
 * Synchronize the translations of a given origin/project/lng with the upstream
 * project.
 *
 * Does not allow concurrent synchronizations because they may affect the
 * performance of the server.  Parameters are received from the request (either
 * GET or POST). They are:
 *  - origin : Origin of the project.
 *  - project : The name of the project.
 *  - lng : Translation to be exported.
 *
 * Examples:
 *   curl -k 'https://dev.btr.example.org/project/sync?origin=LibreOffice&project=cui&lng=sq'
 *   curl -k https://dev.btranslator.org/project/sync \
 *        -d origin=LibreOffice -d project=cui -d lng=sq
 */
function btrCore_project_sync() {
  // Get the parameters.
  $origin = check_plain($_REQUEST['origin']);
  $project = check_plain($_REQUEST['project']);
  $lng = check_plain($_REQUEST['lng']);

  btr::project_sync($origin, $project, $lng);
}

/**
 * Callback function for the menu project/list.
 *
 * Return a plain-text list of all the imported projects,
 * filtered by the given origin/project.
 *
 * Variables $origin and $project can contain '*', which
 * is replaced by '%' (for LIKE matches).
 *
 * If $project=='-' then only a list of 'origin' is outputed,
 * otherwise a list of 'origin/project'.
 *
 * The third variable can be JSON or TEXT (default).
 */
function btrCore_project_list($origin =NULL, $project =NULL, $format =NULL) {
  // Get and sanitize the parameters.
  if (!empty($origin)) {
    $origin = str_replace('*', '%', $origin);
    $origin = check_plain($origin);
  }
  if (!empty($project) && $project != '-') {
    $project = str_replace('*', '%', $project);
    $project = check_plain($project);
  }

  // Get the project list.
  $project_list = btr::project_ls($origin, $project);

  // Output the result.
  if (strtoupper($format) == 'JSON') {
    drupal_json_output($project_list);
  }
  elseif (strtoupper($format) == 'TXT') {
    print "<xmp>" . implode("\n", $project_list) . "</xmp>";
  }
  else {  //TEXT
    print implode("\n", $project_list);
  }

  drupal_exit();
}

/**
 * Return a full json list of all the imported projects and languages.
 */
function btrCore_project_list_all() {
  $project_list = btr::project_list_all();
  drupal_json_output($project_list);
  drupal_exit();
}

/**
 * Return a list of languages for the given origin/project.
 *
 * @param $origin
 *   The origin of the project.
 *
 * @param $project
 *   The name of the project.
 */
function btrCore_project_langs($origin, $project) {
  $project_langs = btr::project_langs($origin, $project);
  drupal_json_output($project_langs);
  drupal_exit();
}
