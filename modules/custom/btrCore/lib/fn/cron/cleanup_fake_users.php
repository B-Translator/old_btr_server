<?php
/**
 * @file
 * Function: cron_cleanup_fake_users()
 */

namespace BTranslator;
use \EntityFieldQuery;
use \DrupalQueue;

/**
 * Cleanup the users that were registered a week ago,
 * but have never accessed the site since then
 * (most probably they are created by spamming robots).
 * Reference:
 * http://drupal.stackexchange.com/questions/54006/how-can-i-prevent-users-from-entering-invalid-e-mail-addresses-at-registration?newsletter=1&nlcode=43535%7c8b76
 */
function cron_cleanup_fake_users() {
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
