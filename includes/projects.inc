<?php
/**
 * Simple REST API for listing and exporting projects.
 */

/**
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
function l10n_suggestions_project_list($origin =NULL, $project =NULL, $format =NULL) {

  //print "$origin/$project/$format\n";  //debug

  $query = db_select('l10n_suggestions_projects', 'p')
    ->fields('p', array('origin'))->orderBy('origin');

  if ($project == '-') {
    $query->distinct();
  }
  else {
    $query->fields('p', array('project'))->orderBy('project');
  }

  if (!empty($origin)) {
    $origin = str_replace('*', '%', $origin);
    $origin = check_plain($origin);
    $query->condition('origin', $origin, 'LIKE');
  }

  if ($project != '-' && !empty($project)) {
    $project = str_replace('*', '%', $project);
    $project = check_plain($project);
    $query->condition('project', $project, 'LIKE');
  }

  $results = $query->execute()->fetchAll();

  $lines = array();
  foreach ($results as $record) {
    $line = $record->origin;
    if ($project != '-') {
      $line .= '/' . $record->project;
    }
    $lines[] = $line;
  }

  // Output the results.
  if (strtoupper($format) == 'JSON') {
    print drupal_json_encode($lines);
  }
  else {  //TEXT
    print implode("\n", $lines);
  }

  exit();
}

/**
 * Return as plain-text the PO file for a given origin/project/lng.
 */
function l10n_suggestions_project_export($origin =NULL, $project =NULL, $lng =NULL) {
  $origin = check_plain($origin);
  $project = check_plain($project);
  $lng = check_plain($lng);

  set_time_limit(0);

  $path = drupal_get_path('module', 'l10n_suggestions') . '/import';
  $tplname = $project;
  $output = shell_exec("$path/po_export.php $origin $project $tplname $lng");
  print $output;

  exit();
}

/**
 * Return an archive of PO files for a given origin/project/lng
 * (usefull for projects that have many POT files.)
 */
function l10n_suggestions_project_export_tgz($origin =NULL, $project =NULL, $lng =NULL) {
  $origin = check_plain($origin);
  $project = check_plain($project);
  $lng = check_plain($lng);

  set_time_limit(0);
  /*
  $path = drupal_get_path('module', 'l10n_suggestions') . '/import';
  $output = shell_exec("$path/po_export.php $origin $project $lng");
  print $output;
  */
  exit();
}

/**
 * Return as plain-text the PO file for a given origin/project/lng.
 */

/**
 * Return a plain-text diff/ediff of the PO files for a given origin/project/lng,
 * which contains the new suggestions since the last version that was imported.
 * It gets the parameters: origin/project/lng[/ediff] (where project can also be '*').
 */
function l10n_suggestions_project_diff($origin =NULL, $project =NULL, $lng =NULL, $format =NULL) {
  $origin = check_plain($origin);
  $project = check_plain($project);
  $lng = check_plain($lng);
  $format = check_plain($format);

  set_time_limit(0);

  /*
  $path = drupal_get_path('module', 'l10n_suggestions') . '/import';
  $tplname = $project;
  $output = shell_exec("$path/po_export.php $origin $project $tplname $lng");
  print $output;
  */

  exit();
}
?>