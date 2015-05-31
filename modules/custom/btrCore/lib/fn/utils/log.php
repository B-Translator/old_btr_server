<?php
/**
 * @file
 * Function: utils_log()
 */

namespace BTranslator;

/**
 * Output the given parameter to a log file (useful for debugging).
 */
function utils_log($var, $comment ='') {
  $file = '/tmp/btr.log';
  $content = "\n==> $comment: " . print_r($var, true);
  file_put_contents($file, $content, FILE_APPEND);
}
