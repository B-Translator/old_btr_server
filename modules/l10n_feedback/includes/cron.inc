<?php
/**
 * @file
 * Functions called by cron.
 */

/*
 * Implements hook_cron_queue_info().
 */
function l10n_feedback_cron_queue_info() {
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
      continue; // skip admin, disabled accounts, and users that have never loggen in
    }

    $message_params = array(
      'type' => 'string-to-be-reviewed',
      'uid' => $account->uid,
      'username' => $account->name,
      'recipient' => $account->name .' <' . $account->mail . '>',
    );
    $queue->createItem((object)$message_params);
  }
}