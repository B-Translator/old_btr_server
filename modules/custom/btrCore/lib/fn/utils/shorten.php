<?php
/**
 * @file
 * Function: utils_shorten()
 */

namespace BTranslator;

/**
 * Shorten the given string.
 *
 * From the given (possibly long) string, returns a short string
 * of the given length that can be suitable for title, subject, etc.
 */
function utils_shorten($string, $length) {
  $str = strip_tags(str_replace("\n", ' ', $string));
  if (strlen($str) > $length) {
    $str = substr($str, 0, strrpos(substr($str, 0, $length - 3), ' '));
    $str .= '...';
  }
  return $str;
}
