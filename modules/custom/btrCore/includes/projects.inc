<?php
/**
 * @file
 * Functions for listing and exporting projects.
 */

/**
 * Return a list of all the imported projects, filtered by
 * origin/project.
 *
 * Variables $origin and $project can contain '*', which
 * is replaced by '%' (for LIKE matches).
 *
 * If $project=='-' then only a list of 'origin' is outputed,
 * otherwise a list of 'origin/project'.
 */
function btr_project_list($origin =NULL, $project =NULL) {

  // Get and sanitize the parameters.
  if (!empty($origin)) {
    $origin = str_replace('*', '%', $origin);
    $origin = check_plain($origin);
  }
  if (!empty($project) && $project != '-') {
    $project = str_replace('*', '%', $project);
    $project = check_plain($project);
  }

  // Start building the query.
  $query = $GLOBALS['btr_db']->select('btr_projects', 'p')
    ->fields('p', array('origin'))
    ->orderBy('origin');

  if ($project == '-') {
    $query->distinct();
  }
  else {
    $query->fields('p', array('project'))
      ->orderBy('project');
  }

  // Build the condition of the query.
  if (!empty($origin)) {
    $query->condition('origin', $origin, 'LIKE');
  }
  if (!empty($project) && $project != '-') {
    $query->condition('project', $project, 'LIKE');
  }

  // Execute the query and get the results.
  $results = $query->execute()->fetchAll();

  // Build the list of projects as an array.
  $list = array();
  foreach ($results as $record) {
    $item = $record->origin;
    if ($project != '-') {
      $item .= '/' . $record->project;
    }
    $list[] = $item;
  }

  return $list;
}

/**
 * Schedule a project for export. When the request
 * is completed, the user will be notified by email.
 *
 * @param $origin
 *   The origin of the project.
 *
 * @param $project
 *   The name of the project. If not given, then all the projects
 *   of the 'origin' will be exported, however only those with
 *   export access rights (usually translators) can do this.
 *   Contributors can export only a single project at a time.
 *
 * @param $export_mode
 *   The export mode that should be used. It can be one of:
 *   (most_voted | preferred_by_me | preferred_by_my_friends).
 *   Normal users can use only the default mode: most_voted.
 *   However those with export access rights (usually translators)
 *   can choose another export mode.
 *    - When the mode most_voted is used, then the translations
 *      with the highest number of votes are exported.
 *    - When the mode preferred_by_me is used, then the translations
 *      voted by the user take precedence over the other translations
 *      despite the number of votes.
 *    - When the mode preferred_by_my_friends is used, then the
 *      translations voted by any friends of the user take precedence.
 *      Friends are the users that are listed on the parameter
 *      'friends' (see below).
 *
 * @param $friends
 *   Comma separated list of usernames. Used only when export_mode
 *   is preferred_by_my_friends.
 *
 * @return
 *   Array of notification messages; each notification message
 *   is an array of a message and a type, where type can be one of
 *   'status', 'warning', 'error'.
 */
function btr_project_export($origin, $project =NULL, $export_mode =NULL, $friends =NULL) {

  // Check the project.
  if (empty($project) and !user_access('btranslator-export')) {
    $msg = t("A project is required but is missing.");
    return array(array($msg, 'error'));
  }

  // Make sure that the given origin and project do exist.
  if (empty($project)) {
    $query = "SELECT DISTINCT origin FROM {btr_projects} WHERE BINARY origin = :origin";
    $params = array(':origin' => $origin);
  }
  else {
    $query = "SELECT project FROM {btr_projects} WHERE BINARY origin = :origin AND BINARY project = :project";
    $params = array(':origin' => $origin, ':project' => $project);
  }
  $result = btr_query($query, $params)->fetchField();
  if (!$result) {
    $msg = t("The project '!project' does not exist.",
           array('!project' => "$origin/$project"));
    return array(array($msg, 'error'));
  }

  // Check the export_mode.
  if (!in_array($export_mode,
      array('most_voted', 'preferred_by_me', 'preferred_by_my_friends')))
    {
      $msg = t("Unknown export mode '!export_mode'.",
             array('!export_mode' => $export_mode));
      return array(array($msg, 'error'));
    }
  if ($export_mode != 'most_voted' and !user_access('btranslator-export')) {
    $msg = t("You don't have access for advanced modes of export.");
    return array('messages' => array($msg, 'error'));
  }

  // Get and check the list of friends.
  if ($export_mode == 'preferred_by_my_friends') {
    $arr_friends = preg_split('/\s*,\s*/', trim($friends));
    $messages = array();
    foreach ($arr_friends as $username) {
      if (!user_load_by_name($username)) {
        $msg = t("The user '!username' does not exist.",
               array('!username' => $username));
        $messages[] = array($msg, 'error');
      }
      if (!empty($messages))  return $messages;
    }
  }

  // Get a list of preferred users (identified by their emails).
  $user = user_load($GLOBALS['user']->uid);
  $arr_voters[] = $user->init;
  foreach ($arr_friends as $username) {
    $account = user_load_by_name($username);
    $arr_voters[] = $account->init;
  }

  // Schedule the project export.
  $queue_params = array(
    'uid' => $user->uid,
    'lng' => $user->translation_lng,
    'origin' => $origin,
    'project' => empty($project) ? 'all' : $project,
    'export_mode' => $export_mode,
    'voters' => implode(',', $arr_voters),
  );
  btr_queue('export_project', array($queue_params));

  // Schedule a notification to the admin.
  // TODO: Send this notification to the project admin.
  $notify_admin = variable_get('btr_export_notify_admin', TRUE);
  if ($notify_admin) {
    $queue_params['type'] = 'notify-admin-on-export-request';
    $queue_params['recipient'] = user_load(1)->mail;
    btr_queue_notifications(array($params));
  }

  // Return a notification message.
  $msg = t("Export of '!project' is scheduled. You will be notified by email when it is done.",
         array('!project' => "$origin/$project"));
  return array(array($msg, 'status'));
}

/**
 * Return an archive of PO files for a given origin/project/lng
 * (usefull for projects that have many POT files.)
 * If project=='all', then all the projects of the given origin
 * will be exported (it usually takes a very long time).
 */
function btr_project_export_tgz($origin ='LibreOffice', $project ='all', $lng ='fr') {

  print "For performance reasons, export_tgz is currently disabled.";
  exit(0);

  $origin = check_plain($origin);
  $project = check_plain($project);
  $lng = check_plain($lng);

  set_time_limit(0);

  // Export files in a tgz archive.
  $path = drupal_get_path('module', 'btrCore') . '/data/export';
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
function btr_project_diff($origin, $project, $lng, $nr =NULL, $format =NULL) {
  $origin = check_plain($origin);
  $project = check_plain($project);
  $lng = check_plain($lng);
  $nr = check_plain($nr);
  $format = check_plain($format);

  $fmt = ($format == 'ediff' ? 'ediff' : 'diff');

  set_time_limit(0);

  $path = drupal_get_path('module', 'btrCore') . '/data/export';
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
