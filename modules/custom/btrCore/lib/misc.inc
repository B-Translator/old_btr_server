<?php

/**
 * Output the given parameter to a log file (useful for debugging).
 */
function btr_log($var, $comment ='') {
  $file = '/tmp/btr.log';
  $content = "\n==> $comment: " . print_r($var, true);
  file_put_contents($file, $content, FILE_APPEND);
}

/**
 * Output the call stack up to the point where this function is called.
 */
function btr_trace($comment ='') {
  $e = new Exception();
  $trace = $e->getTraceAsString();
  $trace = preg_replace('/^#0 .*/', '', $trace);
  $trace = str_replace(DRUPAL_ROOT.'/', '', $trace);
  btr_log($trace, $comment);
}

/**
 * Unpacks a string as retrieved from the database.
 *
 * Creates an array out of the string. If it was a single string, the array
 * will have one item. If the string was a plural string, the array will have
 * as many items as the language requires (two for source strings).
 *
 * @param $string
 *   The string with optional separation markers (NULL bytes)
 * @return
 *   An array of strings with one element for each plural form in case of
 *   a plural string, or one element in case of a regular string. This
 *  is called a $textarray elsewhere.
 */
function btr_unpack_string($string) {
  return explode("\0", $string);
}

/**
 * Packs a string for storage in the database.
 *
 * @param $string
 *   An array of strings.
 * @return
 *   A packed string with NULL bytes separating each string.
 */
function btr_pack_string($strings) {
  if (is_array($strings)) {
    return implode("\0", $strings);
  }
  else {
    return $strings;
  }
}

/**
 * Queue actions for batch execution.
 * @param $queue_name
 *   Name of the queue.
 * @param $items
 *   Array of items to be queued. Each item is an associative array
 *   that provides data for the batch process.
 */
function btr_queue($queue_name, $items) {
  $queue = DrupalQueue::get($queue_name);
  $queue->createQueue();  // There is no harm in trying to recreate existing.
  foreach ($items as $item) {
    $queue->createItem((object)$item);
  }
}

/**
 * Queue notifications for sending by email.
 *
 * @param $notifications
 *   Array of notification items. Each item is an associative array
 *   containing at least 'type' and 'recipient' (email), and optionally
 *   other parameters that can be used on the notification template
 *   (depending on the type of the notification).
 */
function btr_queue_notifications($notifications) {
  $queue = DrupalQueue::get('notifications');
  $queue->createQueue();  // There is no harm in trying to recreate existing.
  foreach ($notifications as $item) {
    $queue->createItem((object)$item);
  }
}
