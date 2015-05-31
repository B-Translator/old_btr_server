<?php
/**
 * @file
 * Function: queue()
 */

namespace BTranslator;
use \DrupalQueue;

/**
 * Queue actions for batch execution.
 * @param $queue_name
 *   Name of the queue.
 * @param $items
 *   Array of items to be queued. Each item is an associative array
 *   that provides data for the batch process.
 */
function queue($queue_name, $items) {
  $queue = DrupalQueue::get($queue_name);
  $queue->createQueue();  // There is no harm in trying to recreate existing.
  foreach ($items as $item) {
    $queue->createItem((object)$item);
  }
}
