<?php
/**
 * @file
 * Function: utils_get_emails()
 */

namespace BTranslator;

/**
 * Converts a comma separated list of usernames into an array of user emails.
 *
 * May be used before calling project_export(). It checks each
 * username and appends its email to the list of emails, or adds an
 * error message if the username is not valid.
 *
 * @param $preferred_voters
 *   Comma separated list of usernames. White spaces are tolerated as well.
 *
 * @return
 *   array($arr_of_user_emails, $arr_of_error_messages)
 *   Each error message is in the format: array($error_message, 'error').
 */
function utils_get_emails($preferred_voters) {
  $arr_emails = array();
  $error_messages = array();

  $arr_names = preg_split('/\s*,\s*/', trim($preferred_voters));
  foreach ($arr_names as $username) {
    $account = user_load_by_name($username);
    if ($account) {
      $arr_emails[] = $account->init;
    }
    else {
      $msg = t("The user '!username' does not exist.",
               array('!username' => $username));
      $error_messages[] = array($msg, 'error');
    }
  }
  if (empty($arr_emails)) {
    $arr_emails = NULL;
  }

  return array($arr_emails, $error_messages);
}
