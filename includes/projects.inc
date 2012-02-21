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
 * Return the diff/ediff of the PO files for a given origin/project/lng/nr.
 * It gets the parameters: origin/project/lng[/nr[/ediff]].
 * If the parameter 'nr' is '-', it returns the latest most-voted suggestions
 * since the last snapshot.
 * If the parameter 'nr' is missing, it returns a list of the saved diffs instead.
 */
function l10n_suggestions_project_diff($origin, $project, $lng, $nr =NULL, $format =NULL) {
  $origin = check_plain($origin);
  $project = check_plain($project);
  $lng = check_plain($lng);
  $nr = check_plain($nr);
  $format = check_plain($format);

  $fmt = ($format == 'ediff' ? 'ediff' : 'diff');

  set_time_limit(0);

  $path = drupal_get_path('module', 'l10n_suggestions') . '/import';
  if (empty($nr)) {
    $output = shell_exec("$path/po_diff.php list $origin $project $lng");
  }
  else if ($nr == '-') {
    shell_exec("$path/export-scripts/diff.sh $origin $project $lng");
    $fname = "$path/export-scripts/$origin-$project-$lng";
    $output = file_get_contents($fname.".$fmt");
    shell_exec("rm $fname.tgz $fname.diff $fname.ediff");
  }
  else {
    $output = shell_exec("$path/po_diff.php get $origin $project $lng $nr $fmt");
  }
  print $output;

  exit();
}
?>