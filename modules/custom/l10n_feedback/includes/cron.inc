<?php
/**
 * @file
 * Functions called by cron.
 */


/*
 * Implements hook_cron_queue_info().
 */
function l10n_feedback_cron_queue_info() {
  $queues['l10n_feedback_delete_fake_users'] = array(
    'worker callback' => 'l10n_feedback_delete_fake_user',
    'time' => 30,
  );
  return $queues;
}

/*
 * Implements hook_cron().
 */
function l10n_feedback_cron() {
  l10n_feedback_cron_nightly();
}

/**
 * Make sure that cron functions runs only once per night,
 * no matter how often cron is called.
 */
function l10n_feedback_cron_nightly() {
  // check whether the crontime has been reached yet
  $crontime = variable_get('btr_ui_crontime', '0');
  if (time() < $crontime)  return;

  // set the crontime after the next midnight (after 03:00 AM)
  $crontime = strtotime(date('Y-m-d 02:55')) + 24*60*60;
  variable_set('btr_ui_crontime', $crontime);

  // Call cron functions.
  l10n_feedback_cleanup_fake_users();
}


/**
 * Cleanup the users that were registered a week ago,
 * but have never accessed the site since then
 * (most probably they are created by spamming robots).
 * Reference:
 * http://drupal.stackexchange.com/questions/54006/how-can-i-prevent-users-from-entering-invalid-e-mail-addresses-at-registration?newsletter=1&nlcode=43535%7c8b76
 */
function l10n_feedback_cleanup_fake_users() {
  $query = new EntityFieldQuery();

  $query->entityCondition('entity_type', 'user')
    ->entityCondition('entity_id', 1, '>')
    ->propertyCondition('access', 0)
    ->propertyCondition('created', REQUEST_TIME - 7*24*60*60, '<')
    ->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT');

  $result = $query->execute();

  if (isset($result['user'])) {
    $queue = DrupalQueue::get('l10n_feedback_delete_fake_users');
    foreach (array_keys($result['user']) as $uid) {
      $queue->createItem($uid);
    }
  }
}

/**
 * This function is a callback from the cron-queue,
 * which is used to delete the user with the given $uid.
 */
function l10n_feedback_delete_fake_user($uid) {
  // Delete from the drupal table 'users'
  user_delete($uid);

  // Delete from the table 'btr_users'
  $lng = variable_get('btr_translation_lng', 'fr');
  btr_user_delete($lng, $uid);
}
