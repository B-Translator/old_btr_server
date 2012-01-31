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

  // Send the content.
  print $output;

  // Stop execution.
  exit(0);
}

/**
 * Return an archive of PO files for a given origin/project/lng
 * (usefull for projects that have many POT files.)
 * If project=='all', then all the projects of the given origin
 * will be exported (it usually takes a very long time).
 */
function l10n_suggestions_project_export_tgz($origin ='LibreOffice', $project ='all', $lng ='fr') {
  $origin = check_plain($origin);
  $project = check_plain($project);
  $lng = check_plain($lng);

  set_time_limit(0);

  // Export files in a tgz archive.
  $path = drupal_get_path('module', 'l10n_suggestions') . '/import/export-scripts';
  $tgz_file = exec("$path/export_tgz.sh $origin $project $lng");

  // Send the headers.
  header('Content-Type: application/octet-stream');
  header('Content-Disposition: attachment; filename="'. basename($tgz_file) .'"');
  header('Content-Transfer-Encoding: binary');
  header("Content-Length: ".filesize($tgz_file));

  // Open the file in a binary mode and dump it to the browser.
  $fp = fopen($tgz_file, 'rb');
  fpassthru($fp);

  // Stop execution.
  exit(0);
}

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