<?php
/**
 * @file
 * Functions called by cron.
 */

/**
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

/**
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
  btr::cron_delete_old_export_files();
  btr::cron_cleanup_fake_users();
  btr::cron_send_strings_for_review();
  btr::cron_update_mysql_materialized_views();
}

/**
 * The callback function called from cron_queue 'notifications'.
 */
function btrCore_send_notification_by_email($params) {
  btr::email_send($params);
}

/**
 * The callback function called from cron_queue 'export_project'.
 */
function btrCore_export_project($export_params) {
  btr::cron_export_project($export_params);
}

/**
 * The callback function called from cron_queue 'import_project'.
 */
function btrCore_import_project($params) {
  btr::cron_import_project($params);
}

/**
 * The callback function called from cron_queue 'import_translations'.
 */
function btrCore_import_translations($params) {
  btr::cron_import_translations($params);
}

/**
 * The callback function called from cron_queue 'delete_fake_users'.
 */
function btrCore_delete_fake_user($uid) {
  // Delete from the drupal table 'users'
  user_delete($uid);

  // Delete from the table 'btr_users'
  btr::db_delete('btr_users')->condition('uid', $uid)->execute();
}
