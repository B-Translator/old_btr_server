<?php
/**
 * @file
 * Functions called by cron.
 */


/*
 * Implements hook_cron_queue_info().
 */
function l10n_feedback_cron_queue_info() {

  $queues['export_project'] = array(
    'worker callback' => 'l10n_feedback_export_project',
    'time' => 120,
  );
  $queues['notifications'] = array(
    'worker callback' => 'l10n_feedback_send_notification_by_email',
    'time' => 120,
  );
  return $queues;
}

/*
 * Implements hook_cron().
 */
function l10n_feedback_cron() {
  l10n_feedback_send_strings_for_review();
}

/**
 * Send by email a string for review to all the active users.
 * Make sure that strings for review are sent
 * only once per day, no matter how often cron is called
 */
function l10n_feedback_send_strings_for_review() {

  // check whether the send_review_time has been reached yet
  $send_review_time = variable_get('l10n_feedback_cron_send_review_time', '0');
  if (time() < $send_review_time)  return;

  // set the send_review_time after the next midnight (after 03:00 AM)
  $send_review_time = strtotime(date('Y-m-d 02:55')) + 24*60*60;
  variable_set('l10n_feedback_cron_send_review_time', $send_review_time);

  $queue = DrupalQueue::get('notifications');
  $queue->createQueue();  // There is no harm in trying to recreate existing.

  $accounts = entity_load('user');
  foreach ($accounts as $account) {
    if ($account->uid < 2 or $account->status != 1 or $account->login == 0) {
      continue; // skip admin, disabled accounts, and users that have never logged in
    }

    // get a sguid according to the user preferencies
    require_once(dirname(__FILE__) . '/translations/vote.inc');
    $sguid = l10n_feedback_get_sguid($account->uid);

    $message_params = array(
      'type' => 'string-to-be-reviewed',
      'uid' => $account->uid,
      'sguid' => $sguid,
      'username' => $account->name,
      'recipient' => $account->name .' <' . $account->mail . '>',
    );
    $queue->createItem((object)$message_params);
  }
}

/**
 * The callback function called from cron_queue.
 */
function l10n_feedback_export_project($export_data) {
  $account = user_load($export_data->uid);
  $origin = $export_data->origin;
  $project = $export_data->project;
  $algorithm = $export_data->algorithm;

  set_time_limit(0);

  // Export files in a tgz archive.
  $lng = variable_get('l10n_feedback_translation_lng', 'fr');
  $path = drupal_get_path('module', 'l10n_feedback') . '/data/export';
  $output_dir = '/var/www/downloads/';
  $tgz_file = exec("nice $path/export_tgz.sh $origin $project $lng $output_dir");
  $filename = basename($tgz_file);
  global $base_url;
  $export_url = $base_url . '/downloads/' . $filename;

  // Notify the user that the export is ready for download.
  $queue = DrupalQueue::get('notifications');
  $queue->createQueue();  // There is no harm in trying to recreate existing.
  $notification_params = array(
    'type' => 'notify-that-export-is-done',
    'uid' => $account->uid,
    'project' => $origin . '/' . $project,
    'username' => $account->name,
    'recipient' => $account->name .' <' . $account->mail . '>',
    'export_url' => $export_url,
  );
  $queue->createItem((object)$notification_params);
}
