<?php
/**
 * @file
 * Functions called by cron.
 */

module_load_include('inc', 'btrCore', 'includes/mail_notifications');

/*
 * Implements hook_cron_queue_info().
 */
function btrCore_cron_queue_info() {

  $queues['notifications'] = array(
    'worker callback' => 'btrCore_send_notification_by_email',
    'time' => 240,
  );
  $queues['export_project'] = array(
    'worker callback' => 'btrCore_export_project',
    'time' => 2000,
  );
  $queues['import_project'] = array(
    'worker callback' => 'btrCore_import_project',
    'time' => 2000,
  );
  $queues['import_translations'] = array(
    'worker callback' => 'btrCore_import_translations',
    'time' => 2000,
  );
  $queues['delete_fake_users'] = array(
    'worker callback' => 'btrCore_delete_fake_user',
    'time' => 30,
  );
  return $queues;
}

/*
 * Implements hook_cron().
 */
function btrCore_cron() {
  btrCore_cron_nightly();
}

/**
 * Make sure that cron functions runs only once per night,
 * no matter how often cron is called.
 */
function btrCore_cron_nightly() {
  // check whether the crontime has been reached yet
  $crontime = variable_get('btrCore_crontime', '0');
  if (time() < $crontime)  return;

  // set the crontime after the next midnight (after 03:00 AM)
  $crontime = strtotime(date('Y-m-d 02:55')) + 24*60*60;
  variable_set('btrCore_crontime', $crontime);

  // Call cron functions.
  btrCore_delete_old_export_files();
  btrCore_cleanup_fake_users();
  btrCore_send_strings_for_review();
  btrCore_update_mysql_materialized_views();
}

/**
 * Delete export files that are older than 2 days
 */
function btrCore_delete_old_export_files() {
  $export_path = variable_get('btr_export_path', '/var/www/exports');
  exec("find $export_path/* -mtime +2 -delete");
}

/**
 * Cleanup the users that were registered a week ago,
 * but have never accessed the site since then
 * (most probably they are created by spamming robots).
 * Reference:
 * http://drupal.stackexchange.com/questions/54006/how-can-i-prevent-users-from-entering-invalid-e-mail-addresses-at-registration?newsletter=1&nlcode=43535%7c8b76
 */
function btrCore_cleanup_fake_users() {
  $query = new EntityFieldQuery();

  $query->entityCondition('entity_type', 'user')
    ->entityCondition('entity_id', 1, '>')
    ->propertyCondition('access', 0)
    ->propertyCondition('created', REQUEST_TIME - 7*24*60*60, '<')
    ->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT');

  $result = $query->execute();

  if (isset($result['user'])) {
    $queue = DrupalQueue::get('delete_fake_users');
    foreach (array_keys($result['user']) as $uid) {
      $queue->createItem($uid);
    }
  }
}

/**
 * This function is a callback from the cron-queue,
 * which is used to delete the user with the given $uid.
 */
function btrCore_delete_fake_user($uid) {
  // Delete from the drupal table 'users'
  user_delete($uid);

  // Delete from the table 'btr_users'
  btr_delete('btr_users')->condition('uid', $uid)->execute();
}


/**
 * Send by email a string for review to all the active users.
 */
function btrCore_send_strings_for_review() {

  // return true if we should NOT send a string by email to the given account
  function _btrCore_dont_send_email($account) {
    // skip admin, disabled accounts, and users that have never logged in
    if ($account->uid < 2 or $account->status != 1 or $account->login == 0) {
      return TRUE;
    }

    // skip users that have unchecked email on feedback_channels
    $field_arr = $account->field_feedback_channels['und'];
    $feedback_channels = array();
    if (is_array($field_arr)) {
      foreach ($field_arr as $item) {
        $feedback_channels[] = $item['value'];
      }
    }
    if ( ! in_array('email', $feedback_channels) )  {
      return TRUE;
    }

    // otherwise send email
    return FALSE;
  }

  $queue = DrupalQueue::get('notifications');
  $queue->createQueue();  // There is no harm in trying to recreate existing.

  $accounts = entity_load('user');
  foreach ($accounts as $account) {
    if (_btrCore_dont_send_email($account))  continue;

    // Get a random project from user preferences.
    if (empty($account->preferred_projects))  continue;
    $idx = rand(0, sizeof($account->preferred_projects) - 1);
    $project = $account->preferred_projects[$idx];

    // get a sguid according to the user preferencies
    module_load_include('inc', 'btrCore', 'includes/get_sguid');
    $sguid = _btr_sguid_get_random($account->uid, array($project));
    if (!$sguid)  continue;

    $message_params = array(
      'type' => 'string-to-be-reviewed',
      'uid' => $account->uid,
      'sguid' => $sguid,
      'project' => $project,
      'username' => $account->name,
      'recipient' => $account->name .' <' . $account->mail . '>',
    );
    $queue->createItem((object)$message_params);
  }
}

/**
 * The callback function called from cron_queue export_project.
 */
function btrCore_export_project($export_params) {

  // Make sure that exports do not run in parallel,
  // so that the server is not loaded.
  if (!lock_acquire('export_project', 3000)) {
    // If we cannot get the lock, just stop the execution, do not return,
    // because after the callback function returns, the cron_queue will
    // remove the item from the queue, no matter whether it is processed or not.
    exit();
  }

  // Allow the export script to run until completion.
  set_time_limit(0);

  // Get the parameters of export.
  $lng = $export_params->lng;
  $origin = $export_params->origin;
  $project = $export_params->project;
  $export_mode = $export_params->export_mode;
  $preferred_voters = $export_params->preferred_voters;
  $account = user_load($export_params->uid);

  // Get the full path of the export files.
  $export_dir = variable_get('btr_export_path', '/var/www/exports');
  $username = strtr(strtolower($account->name), ' ', '_');
  $filename = "$username.$origin-$project-$lng";
  $file_diff = "$export_dir/$filename.diff";
  $file_ediff = "$export_dir/$filename.ediff";
  $file_tgz = "$export_dir/$filename.tgz";

  // Get the latest translations and diffs with the last snapshot.
  exec("rm -f $file_diff $file_ediff $file_tgz");
  btr::project_diff($origin, $project, $lng,
    $file_diff, $file_ediff, $file_tgz,
    $export_mode, $preferred_voters);

  // Notify the user that the export is done.
  $queue = DrupalQueue::get('notifications');
  $queue->createQueue();  // There is no harm in trying to recreate existing.
  $exports_url = url('translations/exports', array('absolute' => TRUE));
  $params = array(
    'type' => 'notify-that-export-is-done',
    'uid' => $account->uid,
    'project' => $origin . '/' . $project,
    'username' => $account->name,
    'recipient' => $account->name .' <' . $account->mail . '>',
    'export_url_tgz' => "$exports_url/$filename.tgz",
    'export_url_diff' => "$exports_url/$filename.diff",
    'export_url_ediff' => "$exports_url/$filename.ediff",
  );
  $queue->createItem((object)$params);

  // This export is done, allow any other exports to run.
  lock_release('export_project');
}

/**
 * The callback function called from cron_queue import_project.
 */
function btrCore_import_project($params) {

  // Make sure that imports do not run in parallel,
  // so that the server is not overloaded.
  if (!lock_acquire('import_project', 3000)) {
    // If we cannot get the lock, just stop the execution, do not return,
    // because after the callback function returns, the cron_queue will
    // remove the item from the queue, no matter whether it is processed or not.
    exit();
  }

  // Allow the import script to run until completion.
  set_time_limit(0);

  // Get the parameters.
  $account = user_load($params->uid);
  $file = file_load($params->fid);
  $origin = $params->origin;
  $project = $params->project;
  $lng = $account->translation_lng;

  // Create a temporary directory.
  $tmpdir = '/tmp/' . sha1_file($file->uri);
  mkdir($tmpdir, 0700);

  // Copy the file there and extract it (if it is an archive).
  file_unmanaged_copy($file->uri, $tmpdir);
  exec("cd $tmpdir ; dtrx -q -n $file->filename 2>/dev/null");

  // Create the project.
  btr::project_add($origin, $project, $tmpdir, $account->uid);

  // If there are any PO files, import translations from them.
  btr::project_import($origin, $project, $lng, $tmpdir, $account->uid);

  // Get the base_url of the site.
  module_load_include('inc', 'btrCore', 'includes/sites');
  $base_url = btr_get_base_url($lng);

  // Notify the user that the project import is done.
  $queue = DrupalQueue::get('notifications');
  $queue->createQueue();  // There is no harm in trying to recreate existing.

  $params = array(
    'type' => 'notify-that-project-import-is-done',
    'uid' => $account->uid,
    'username' => $account->name,
    'recipient' => $account->name .' <' . $account->mail . '>',
    'project' => $origin . '/' . $project,
    'search_url' => $base_url . url('translations/search', array(
                    'query' => array(
                      'lng' => $lng,
                      'origin' => $origin,
                      'project' => $project,
                      'limit' => 50,
                    )
                  )),
  );
  $queue->createItem((object)$params);

  // Cleanup, remove the temp dir and delete the file.
  exec("rm -rf $tmpdir/");
  file_delete($file, TRUE);

  // This import is done, allow any other imports to run.
  lock_release('import_project');
}

/**
 * The callback function called from cron_queue import_translations.
 */
function btrCore_import_translations($params) {

  // Make sure that imports do not run in parallel,
  // so that the server is not overloaded.
  if (!lock_acquire('import_translations', 3000)) {
    // If we cannot get the lock, just stop the execution, do not return,
    // because after the callback function returns, the cron_queue will
    // remove the item from the queue, no matter whether it is processed or not.
    exit();
  }

  // Allow the import script to run until completion.
  set_time_limit(0);

  // Get the parameters.
  $lng = $params->lng;
  $account = user_load($params->uid);
  $file = file_load($params->fid);

  // Create a temporary directory.
  $tmpdir = '/tmp/' . sha1_file($file->uri);
  mkdir($tmpdir, 0700);

  // Copy the file there and extract it (if it is an archive).
  file_unmanaged_copy($file->uri, $tmpdir);
  exec("cd $tmpdir ; dtrx -q -n $file->filename 2>/dev/null");

  // Import the PO files.
  btr::vote_import($account->uid, $lng, $tmpdir);

  // Get the base_url of the site.
  module_load_include('inc', 'btrCore', 'includes/sites');
  $base_url = btr_get_base_url($lng);

  // Notify the user that the export is done.
  $queue = DrupalQueue::get('notifications');
  $queue->createQueue();  // There is no harm in trying to recreate existing.
  $params = array(
    'type' => 'notify-that-import-is-done',
    'uid' => $account->uid,
    'username' => $account->name,
    'recipient' => $account->name .' <' . $account->mail . '>',
    'filename' => $file->filename,
    'search_url' => $base_url . url('translations/search', array(
                    'query' => array(
                      'lng' => $lng,
                      'translated_by' => $account->name,
                      'voted_by' => $account->name,
                      'date_filter' => 'votes',
                      'from_date' => date('Y-m-d H:i:s', REQUEST_TIME - 1),
                      'to_date' => date('Y-m-d H:i:s', REQUEST_TIME + 1),
                      'limit' => 50,
                    )
                  )),
  );
  $queue->createItem((object)$params);

  // Cleanup, remove the temp dir and delete the file.
  exec("rm -rf $tmpdir/");
  file_delete($file, TRUE);

  // This import is done, allow any other imports to run.
  lock_release('import_translations');
}

/**
 * Update MySQL materialized views.
 */
function btrCore_update_mysql_materialized_views() {
  // Materialized views are used to speed-up
  // term autocompletion of vocabularies.
  // For each vocabulary project update the mv table.
  $project_list = btr::project_ls('vocabulary');
  foreach ($project_list as $project) {
    $project = str_replace('vocabulary/', '', $project);
    $table = 'btr_mv_' . strtolower($project);
    btr_query("TRUNCATE {$table}");
    btr_query("INSERT INTO {$table}
               SELECT DISTINCT s.string FROM {btr_strings} s
               JOIN {btr_locations} l ON (l.sguid = s.sguid)
               JOIN {btr_templates} t ON (t.potid = l.potid)
               JOIN {btr_projects}  p ON (p.pguid = t.pguid)
               WHERE p.project = :project
                 AND p.origin = 'vocabulary'
               ORDER BY s.string",
      array(':project' => $project)
    );
  }
}
