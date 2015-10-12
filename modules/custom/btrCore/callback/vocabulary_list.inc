<?php
/**
 * @file
 * Callback function for vocabulary/list.
 */

/**
 * Callback function for the menu vocabulary/list.
 * Return a list of vocabularies in JSON format.
 *
 * @param $lng
 *   Language of the vocabulary.
 *
 * @param $name
 *   Name of the vocabulary.
 *
 * Parameters can contain '*', which is replaced by '%' (for LIKE matches).
 */
function btrCore_vocabulary_list($lng = '*', $name = '*') {
  // Get and sanitize the parameters.
  $lng = check_plain($lng);
  $lng = str_replace('*', '%', $lng);
  $name = check_plain($name);
  $name = str_replace('*', '%', $name);

  // Get the vocabulary list.
  $vocabulary_list = btr::vocabulary_ls($lng, $name);

  // Output the result.
  drupal_json_output($vocabulary_list);
  drupal_exit();
}
