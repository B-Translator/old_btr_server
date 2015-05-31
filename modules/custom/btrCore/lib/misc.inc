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
