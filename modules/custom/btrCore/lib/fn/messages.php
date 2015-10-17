<?php
/**
 * @file
 * Function for collecting output messages.
 */

namespace BTranslator;

/**
 * Collect output messages from functions.
 *
 * If called without arguments (or with 'get') will return and reset the message
 * array.  Anything else will be appended to the message array.  The type of the
 * message can be: 'status', 'warning', 'error'.  If the given $msg parameter is
 * an array of messages itself, then it will be appended to the messages.
 */
function messages($msg = 'get', $type = 'status') {
  static $messages = [];
  if ($msg == 'get') {
    // Return the list of messages and empty it.
    $msgs = $messages;
    $messages = [];
    return $msgs;
  }
  elseif (is_string($msg)) {
    // Append a new message to the list.
    $messages[] = [$msg, $type];
  }
  elseif (is_array($msg)) {
    // Append the given list of messages.
    $messages = array_merge($messages, $msg);
  }
  else {
  }
}

/**
 * Concat messages into a text format.
 */
function messages_cat($arr_messages) {
  $txt_messages = '';
  foreach ($arr_messages as $msg) {
    $txt_messages .= "\n - " . $msg[1] . ': ' . $msg[0] . "\n";
  }
  return $txt_messages;
}
