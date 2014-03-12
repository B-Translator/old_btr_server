<?php

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
function btrClient_unpack_string($string) {
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
function btrClient_pack_string($strings) {
  if (is_array($strings)) {
    return implode("\0", $strings);
  }
  else {
    return $strings;
  }
}

/**
 * Check whether the btr_user has the given permission.
 *
 * @param $permission
 *   The name of the permission (like btranslator-*).
 * @return
 *   TRUE or FALSE
 */
function btr_user_access($permission) {
  if (!isset($_SESSION['btrClient']['btr_profile']['permissions'])) {
    return FALSE;
  }
  $btr_permissions = &$_SESSION['btrClient']['btr_profile']['permissions'];
  return in_array($permission, $btr_permissions);
}

/**
 * Display any messages, warnings and errors.
 *
 * @param $messages
 *   Array of messages, usually returned from btr rest services.
 *   Each item is an array that contains a string message and a type,
 *   where type can be one of: status, warning, error.
 */
function btrClient_display_messages($messages) {
  foreach ($messages as $message) {
    list($msg, $type) = $message;
    if (!in_array($type, array('status', 'warning', 'error'))) {
      $type = 'status';
    }
    drupal_set_message($msg, $type);
  }
}