<?php
/**
 * @file
 * Simple REST API for listing and exporting projects.
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
 * Callback function for the menu 'project/export'
 *
 * Return an archive of PO files for a given origin/project/lng.
 *
 * Does not allow concurrent exports because they may affect the performance
 * of the server.  Parameters are received from the request (either GET or
 * POST). They are:
 *
 *  - origin
 *      Origin of the project.
 *
 *  - project
 *      The name of the project.
 *
 *  - lng
 *      Translation to be exported.
 *
 *  - export_mode
 *      Mode of export: most_voted | preferred | original
 *
 *      Default is 'most_voted' which exports the most voted
 *      translations and suggestions.
 *
 *      The export mode 'original' exports the translations of the
 *      original file that was imported (useful for making diffs).
 *
 *      The export mode 'preferred' gives priority to translations
 *      that are voted by a certain user or a group of users. It
 *      requires an additional argument (preferred_voters) to specify
 *      the user (or a list of users) whose translations are
 *      preferred.
 *
 * - preferred_voters
 *      Comma separated list of usernames of the preferred voters.
 *
 * Examples:
 *   curl -k 'https://dev.btr.example.org/project/export?origin=test&project=kturtle&lng=sq' > test1.tgz
 *   curl -k https://dev.btranslator.org/project/export \
 *        -d 'origin=test&project=kturtle&lng=sq&export_mode=original' > test1.tgz
 *   curl -k https://dev.btranslator.org/project/export \
 *        -d origin=test -d project=kturtle -d lng=sq \
 *        -d export_mode=preferred \
 *        -d preferred_voters=user1,user2 > test1.tgz
 */
function btrCore_project_export() {

  // Try to avoid concurrent exports because they
  // may affect the performance of the server.
  if (!lock_acquire('export_project')) {
    print t("Error: Server is currently busy. Please try to export again later.");
    drupal_exit();
  }

  // Get the parameters.
  $origin = check_plain($_REQUEST['origin']);
  $project = check_plain($_REQUEST['project']);
  $lng = check_plain($_REQUEST['lng']);
  $export_mode = check_plain($_REQUEST['export_mode']);
  $preferred_voters = check_plain($_REQUEST['preferred_voters']);

  // Make sure that the given origin and project do exist.
  if (!btr::utils_project_exists($origin, $project)) {
    print t("The project '!project' does not exist.",
      array('!project' => "$origin/$project"));
    drupal_exit();
  }

  // Check the export_mode.
  if (empty($export_mode))  $export_mode = 'most_voted';
  if (!in_array($export_mode, array('most_voted', 'preferred', 'original'))) {
    print t("Unknown export mode '!export_mode'.",
      array('!export_mode' => $export_mode));
    drupal_exit();
  }

  // Get and check the list of preferred voters.
  if ($export_mode == 'preferred') {
    if (empty($preferred_voters)) {
      print t("For mode 'preferred' parameter 'preferred_voters' should not be empty.") . "\n";
      drupal_exit();
    }
    list($arr_emails, $error_messages) = btr::utils_get_emails($preferred_voters);
    if (!empty($error_messages)) {
      foreach ($error_messages as $msg) {
        print $msg[0] . "\n";
      }
      drupal_exit();
    }
  }

  // Export translations of the project.
  set_time_limit(0);
  $export_dir = exec('mktemp -d');
  btr::project_export($origin, $project, $lng, $export_dir,
    $GLOBALS['user']->uid, $quiet = TRUE,
    $export_mode, $arr_emails);
  $file_tgz = tempnam('/tmp', 'export_');
  exec("tar -cz -f $file_tgz -C $export_dir .");

  // Send the headers.
  $filename = "$origin-$project-$lng.tgz";
  header('Content-Type: application/x-compressed');
  header('Content-Disposition: attachment; filename="' . $filename . '"');
  header('Content-Transfer-Encoding: binary');
  header("Content-Length: " . filesize($file_tgz));

  // Open the file in a binary mode and dump it to the browser.
  $fp = fopen($file_tgz, 'rb');
  fpassthru($fp);

  // Cleanup temporary files.
  unlink($file_tgz);
  exec("rm -rf $export_dir");

  // Stop execution.
  lock_release('export_project');
  drupal_exit();
}

/**
 * Callback function for the menu 'project/diff'
 *
 * Return the diff/ediff of the PO files for a given
 * origin/project/lng/nr.  It gets the parameters:
 * origin/project/lng[/nr[/ediff]].  If the parameter 'nr' is missing,
 * it returns a list of the saved diffs instead.
 *
 * Examples:
 *   curl -k https://btranslator.org/project/diff/LibreOffice/sw/sq
 *   curl -k https://btranslator.org/project/diff/LibreOffice/sw/sq/2 > 2.diff
 *   curl -k https://btranslator.org/project/diff/LibreOffice/sw/sq/2/ediff > 2.ediff
 *   curl -k https://btranslator.org/project/diff/LibreOffice/sw/sq/4 > 4.diff
 *   curl -k https://btranslator.org/project/diff/LibreOffice/sw/sq/4/ediff > 4.ediff
 */
function btrCore_project_diff($origin, $project, $lng, $nr =NULL, $format =NULL) {
  $origin = check_plain($origin);
  $project = check_plain($project);
  $lng = check_plain($lng);
  $nr = check_plain($nr);
  $format = check_plain($format);

  $path = drupal_get_path('module', 'btrCore') . '/data/export';
  if (empty($nr)) {
    $arr_diffs = array();
    $diff_list = btr::project_diff_list($origin, $project, $lng);
    foreach ($diff_list as $diff) {
      // Separate fields by TAB.
      $arr_diffs[] = implode("\t", array($diff->nr, $diff->time, $diff->comment));
    }
    $output = implode("\n", $arr_diffs) . "\n";
  }
  else {
    $fmt = ($format == 'ediff' ? 'ediff' : 'diff');
    $output = btr::project_diff_get($origin, $project, $lng, $nr, $fmt);
  }
  print $output;

  drupal_exit();
}


/**
 * The callback function for the menu 'translations/exports'.
 * The URL is of the form 'translations/exports/filename.tgz'
 * where the filename is passed as a parameter to the function.
 */
function btrCore_get_exported_file($filename =NULL) {

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
  $content_type = ( substr($filename, -4) == '.tgz'
                  ? 'application/x-compressed'
                  : 'application/octet-stream' );
  header('Content-Type: ' . $content_type);
  header('Content-Disposition: attachment; filename="' . $filename . '"');
  header('Content-Transfer-Encoding: binary');
  header("Content-Length: " . filesize($export_file));

  // Open the file in a binary mode and dump it to the browser.
  $fp = fopen($export_file, 'rb');
  fpassthru($fp);

  // Stop execution.
  exit(0);
}
