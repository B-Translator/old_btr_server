<?php
/**
 * @file
 * Callback function for project/snapshot
 */

/**
 * Callback function for the menu 'project/snapshot'
 *
 * Make a snapshot of the given origin/project/lng.
 *
 * Examples:
 *   curl 'https://btranslator.org/project/snapshot/LibreOffice/sw/sq?export_mode=preferred_by_me&friends='
 */
function btrCore_project_snapshot($origin, $project, $lng) {
  // For performance reasons, this is restricted only to the project admins.
  if (!btr::user_is_project_admin($origin, $project, $lng)) {
    print t('Only project admins can make a project snapshot.');
    return;
  }

  // Get parameters.
  $comment = check_plain($_GET['comment']);
  $preferred_voters = check_plain($_GET['friends']);
  $export_mode = check_plain($_GET['export_mode']);

  if (in_array($export_mode, ['preferred_by_me', 'preferred_by_my_friends'])) {
    $export_mode = 'preferred';
  }

  // Get and check the list of preferred voters.
  if ($export_mode == 'preferred') {
    if (empty($preferred_voters)) {
      $preferred_voters = $GLOBALS['user']->name;
    }
    list($arr_emails, $error_messages) = btr::utils_get_emails($preferred_voters);
    if (!empty($error_messages)) {
      header('Content-Type: text/plain; charset=utf-8');
      foreach ($error_messages as $msg) { print $msg[0] . "\n"; }
      return;
    }
  }

  // Make the snapshot.
  btr::project_snapshot($origin, $project, $lng, $comment, $export_mode, $arr_voters);
  foreach(btr::messages() as $msg)  drupal_set_message($msg[0], $msg[1]);

  // Redirect back to the calling page.
  if (isset($_GET['dest'])) {
    drupal_goto($_GET['dest']);
  }
}
