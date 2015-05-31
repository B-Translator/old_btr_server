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
