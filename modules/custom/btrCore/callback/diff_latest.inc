<?php
/**
 * @file
 * Callback function for project/diff-latest
 */

/**
 * Callback function for the menu 'project/diff-latest'
 *
 * Export the latest most voted translations and make the diffs with the last
 * snapshot.
 *
 * Examples:
 *   curl 'https://btranslator.org/project/diff-latest/LibreOffice/sw/sq?format=diff&export_mode=preferred_by_me&friends='
 */
function btrCore_project_diff_latest($origin, $project, $lng) {
  // For performance reasons, this is restricted only to the project admins.
  if (!btr::user_is_project_admin($origin, $project, $lng)) {
    print t('Only project admins can get the latest diffs.');
    return;
  }

  // Get parameters.
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

  // Make the diffs.
  $export_file = tempnam('/tmp', 'export_file_');
  $file_diff = tempnam('/tmp', 'file_diff_');
  $file_ediff = tempnam('/tmp', 'file_ediff_');
  btr::project_diff($origin, $project, $lng,
    $file_diff, $file_ediff, $export_file,
    $export_mode, $arr_emails);

  // Send the diff file.
  $fmt = check_plain($_GET['format']);
  $file = ($fmt=='ediff' ? $file_ediff : $file_diff);
  $filename = "$origin-$project-$lng.$fmt";
  header('Content-Type: text/plain; charset=utf-8');
  header('Content-Disposition: attachment; filename="' . $filename . '"');
  header('Content-Transfer-Encoding: binary');
  header("Content-Length: " . filesize($file));
  $fp = fopen($file, 'rb');
  fpassthru($fp);
  fclose($fp);

  // Cleanup.
  unlink($export_file);
  unlink($file_diff);
  unlink($file_ediff);

  drupal_exit();
}
