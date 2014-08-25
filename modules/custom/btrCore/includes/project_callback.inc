<?php
/**
 * @file
 * Simple REST API for listing and exporting projects.
 */

module_load_include('inc', 'btrCore', 'includes/projects');

/**
 * Callback function for the menu translations/project/list.
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
 * Callback function for the menu translations/project/templates.
 *
 * Return a list of the templates (names of POT files) for a project.
 * Many projects have just one template, however big projects are
 * composed of many templates. The third parameter can be JSON or TEXT
 * (default).
 *
 * Examples:
 *   curl -k https://dev.l10n.org.al/translations/project/templates/test/kturtle
 *   curl -k https://dev.l10n.org.al/translations/project/templates/test/kturtle/json
 *   curl -k https://dev.l10n.org.al/translations/project/templates/KDE/kdeedu
 */
function btrCore_project_templates($origin, $project, $format =NULL) {
  $origin = check_plain($origin);
  $project = check_plain($project);
  $format = check_plain($format);

  $query = "SELECT t.tplname FROM {btr_projects} p
      LEFT JOIN {btr_templates} t ON (t.pguid = p.pguid)
      WHERE p.origin = :origin and p.project = :project";
  $params = array(':origin' => $origin, ':project' => $project);
  $result = btr_query($query, $params)->fetchCol();

  // Output the result.
  if (strtoupper($format) == 'JSON') {
    drupal_json_output($result);
  }
  elseif (strtoupper($format) == 'TXT') {
    print "<xmp>" . implode("\n", $result) . "</xmp>";
  }
  else {  //TEXT
    print implode("\n", $result);
  }

  drupal_exit();
}

/**
 * Callback function for the menu 'translations/project/export'
 *
 * Return a PO file as plain-text. Does not allow concurrent exports
 * because they may affect the performance of the server.  Parameters
 * are received from the request (either GET or POST). They are:
 *
 *  - origin
 *      Origin of the project (ubuntu, GNOME, KDE, etc.)
 *
 *  - project
 *      The name of the project to be exported.
 *
 *  - tplname
 *      The name of the PO template.
 *
 *  - lng
 *      Translation to be exported (de, fr, sq, en_GB, etc.)
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
 *      Comma separated list of email addresses of preferred voters.
 *
 * Examples:
 *   curl -k 'https://dev.l10n.org.al/translations/project/export?origin=test&project=kturtle&lng=sq' > test.po
 *   curl -k https://dev.l10n.org.al/translations/project/export \
 *        -d 'origin=test&project=kturtle&lng=sq&export_mode=original' > test.po
 *   curl -k https://dev.l10n.org.al/translations/project/export \
 *        -d origin=test -d project=kturtle -d lng=sq \
 *        -d preferred_voters=email1@example.com,email2@example.com \
 *        -d export_mode=preferred > test.po
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
  $tplname = check_plain($_REQUEST['tplname']);
  $lng = check_plain($_REQUEST['lng']);
  $export_mode = check_plain($_REQUEST['export_mode']);
  $preferred_voters = check_plain($_REQUEST['preferred_voters']);
  if (empty($tplname))  $tplname = $project;

  // Run the export script.
  set_time_limit(100);
  $path = drupal_get_path('module', 'btrCore') . '/data/export';
  $output = shell_exec("$path/po_export.php $origin $project $tplname $lng stdout $export_mode $preferred_voters");

  // Send the content.
  print $output;

  // Stop execution.
  lock_release('export_project');
  drupal_exit();
}


/**
 * Callback function for the menu 'translations/project/export_tgz'
 *
 * Return an archive of PO files for a given origin/project/lng
 * (usefull for projects that have many POT files).  Does not allow
 * concurrent exports because they may affect the performance of the
 * server.  Parameters are received from the request (either GET or
 * POST). They are:
 *
 *  - origin
 *      Origin of the project (ubuntu, GNOME, KDE, etc.)
 *
 *  - project
 *      The name of the project to be exported.
 *
 *  - lng
 *      Translation to be exported (de, fr, sq, en_GB, etc.)
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
 *      Comma separated list of email addresses of preferred voters.
 *
 * Examples:
 *   curl -k 'https://dev.btr.example.org/translations/project/export_tgz?origin=test&project=kturtle&lng=sq' > test1.tgz
 *   curl -k https://dev.l10n.org.al/translations/project/export_tgz \
 *        -d 'origin=test&project=kturtle&lng=sq&export_mode=original' > test1.tgz
 *   curl -k https://dev.l10n.org.al/translations/project/export_tgz \
 *        -d origin=test -d project=kturtle -d lng=sq \
 *        -d preferred_voters=email1@example.com,email2@example.com \
 *        -d export_mode=preferred > test1.tgz
 */
function btrCore_project_export_tgz() {

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
  if ($project == 'all') {
    print t("Error: Exporting all the projects is not allowed. Please specify a project.");
    drupal_exit();
  }

  // Export files in a tgz archive.
  set_time_limit(120);
  $path = drupal_get_path('module', 'btrCore') . '/data/export';
  $export_cmd = "$path/export_tgz.sh $origin $project $lng";
  if ($export_mode == 'preferred_by_me'
      or $export_mode == 'preferred_by_my_friends') {
    $export_cmd = "export PO_EXPORT_MODE='preferred' ; export PO_EXPORT_VOTERS='$voters' ; $export_cmd";
  }
  $tgz_file = exec($export_cmd);

  // Send the headers.
  header('Content-Type: application/octet-stream');
  header('Content-Disposition: attachment; filename="' . basename($tgz_file) . '"');
  header('Content-Transfer-Encoding: binary');
  header("Content-Length: " . filesize($tgz_file));

  // Open the file in a binary mode and dump it to the browser.
  $fp = fopen($tgz_file, 'rb');
  fpassthru($fp);

  // Stop execution.
  lock_release('export_project');
  drupal_exit();
}

/**
 * Callback function for the menu 'translations/project/diff'
 *
 * Return the diff/ediff of the PO files for a given
 * origin/project/lng/nr.  It gets the parameters:
 * origin/project/lng[/nr[/ediff]].  If the parameter 'nr' is missing,
 * it returns a list of the saved diffs instead.
 *
 * Examples:
 *   curl -k https://l10n.org.al/translations/project/diff/LibreOffice/sw/sq
 *   curl -k https://l10n.org.al/translations/project/diff/LibreOffice/sw/sq/2 > 2.diff
 *   curl -k https://l10n.org.al/translations/project/diff/LibreOffice/sw/sq/2/ediff > 2.ediff
 *   curl -k https://l10n.org.al/translations/project/diff/LibreOffice/sw/sq/4 > 4.diff
 *   curl -k https://l10n.org.al/translations/project/diff/LibreOffice/sw/sq/4/ediff > 4.ediff
 */
function btrCore_project_diff($origin, $project, $lng, $nr =NULL, $format =NULL) {
  $origin = check_plain($origin);
  $project = check_plain($project);
  $lng = check_plain($lng);
  $nr = check_plain($nr);
  $format = check_plain($format);

  $path = drupal_get_path('module', 'btrCore') . '/data/export';
  if (empty($nr)) {
    $output = shell_exec("$path/db_diff.php list $origin $project $lng");
  }
  else {
    $fmt = ($format == 'ediff' ? 'ediff' : 'diff');
    $output = shell_exec("$path/db_diff.php get $origin $project $lng $nr $fmt");
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

