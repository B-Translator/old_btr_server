<?php
/**
 * @file
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
function btranslator_data_project_list($origin =NULL, $project =NULL, $format =NULL) {

  //print "$origin/$project/$format\n";  //debug

  $query = $GLOBALS['btr_db']->select('btr_projects', 'p')
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
  elseif (strtoupper($format) == 'TXT') {
    print "<xmp>" . implode("\n", $lines) . "</xmp>";
  }
  else {  //TEXT
    print implode("\n", $lines);
  }

  exit();
}

/**
 * Return as plain-text the PO file for a given origin/project/lng.
 */
function btranslator_data_project_export($origin =NULL, $project =NULL, $lng =NULL) {

  print "For performance reasons, export is currently disabled.";
  exit(0);

  $origin = check_plain($origin);
  $project = check_plain($project);
  $lng = check_plain($lng);

  set_time_limit(0);

  $path = drupal_get_path('module', 'btranslator_data') . '/data/export';
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
function btranslator_data_project_export_tgz($origin ='LibreOffice', $project ='all', $lng ='fr') {

  print "For performance reasons, export_tgz is currently disabled.";
  exit(0);

  $origin = check_plain($origin);
  $project = check_plain($project);
  $lng = check_plain($lng);

  set_time_limit(0);

  // Export files in a tgz archive.
  $path = drupal_get_path('module', 'btranslator_data') . '/data/export';
  $tgz_file = exec("$path/export_tgz.sh $origin $project $lng");

  // Send the headers.
  header('Content-Type: application/octet-stream');
  header('Content-Disposition: attachment; filename="' . basename($tgz_file) . '"');
  header('Content-Transfer-Encoding: binary');
  header("Content-Length: " . filesize($tgz_file));

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
function btranslator_data_project_diff($origin, $project, $lng, $nr =NULL, $format =NULL) {
  $origin = check_plain($origin);
  $project = check_plain($project);
  $lng = check_plain($lng);
  $nr = check_plain($nr);
  $format = check_plain($format);

  $fmt = ($format == 'ediff' ? 'ediff' : 'diff');

  set_time_limit(0);

  $path = drupal_get_path('module', 'btranslator_data') . '/data/export';
  if (empty($nr)) {
    $output = shell_exec("$path/db_diff.php list $origin $project $lng");
  }
  elseif ($nr == '-') {
    shell_exec("$path/export/make_diff.sh $origin $project $lng");
    $fname = "$path/export/$origin-$project-$lng";
    $output = file_get_contents($fname . ".$fmt");
    shell_exec("rm $fname.tgz $fname.diff $fname.ediff");
  }
  else {
    $output = shell_exec("$path/db_diff.php get $origin $project $lng $nr $fmt");
  }
  print $output;

  exit();
}


/**
 * The callback function for the menu 'translations/exports'.
 * The URL is of the form 'translations/exports/filename.tgz'
 * where the filename is passed as a parameter to the function.
 */
function btranslator_data_get_exported_file($filename =NULL) {

  $filename = check_plain($filename);
  if (empty($filename)) {
    drupal_set_message(t("Export file '!filename' does not exist!",
			 array('!filename' => $filename)), 'error');
    drupal_goto("translations");
    return;
  }

  // Get the full path of the export file.
  $export_path = variable_get('btr_export_path', '/var/www/exports');
  $export_file = $export_path . '/' . $filename;
  if (!file_exists($export_file)) {
    drupal_set_message(t("Export file '!filename' does not exist!",
			 array('!filename' => $filename)), 'error');
    drupal_goto("translations");
    return;
  }

  // Send the headers.
  header('Content-Type: application/octet-stream');
  header('Content-Disposition: attachment; filename="' . $filename . '"');
  header('Content-Transfer-Encoding: binary');
  header("Content-Length: " . filesize($export_file));

  // Open the file in a binary mode and dump it to the browser.
  $fp = fopen($export_file, 'rb');
  fpassthru($fp);

  // Stop execution.
  exit(0);
}

