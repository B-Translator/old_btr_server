<?php
/**
 * @file
 * Callback function for project/diff
 */

/**
 * Callback function for the menu 'project/diff'
 *
 * Return the diff/ediff of the PO files for a given
 * origin/project/lng/nr.  It gets the parameters:
 * origin/project/lng[/nr[/ediff]].  If the parameter 'nr' is missing,
 * it returns a list of the saved diffs instead.
 *
 * Examples:
 *   curl https://btranslator.org/project/diff/LibreOffice/sw/sq
 *   curl https://btranslator.org/project/diff/LibreOffice/sw/sq/2 > 2.diff
 *   curl https://btranslator.org/project/diff/LibreOffice/sw/sq/2/ediff > 2.ediff
 *   curl https://btranslator.org/project/diff/LibreOffice/sw/sq/4 > 4.diff
 *   curl https://btranslator.org/project/diff/LibreOffice/sw/sq/4/ediff > 4.ediff
 */
function btrCore_project_diff($origin, $project, $lng, $nr =NULL, $format =NULL) {
  $origin = check_plain($origin);
  $project = check_plain($project);
  $lng = check_plain($lng);
  $nr = check_plain($nr);
  $format = check_plain($format);

  if (empty($nr)) {
    $arr_diffs = array();
    $diff_list = btr::project_diff_list($origin, $project, $lng);
    foreach ($diff_list as $diff) {
      // Separate fields by TAB.
      $arr_diffs[] = implode("\t", array($diff->nr, $diff->time, $diff->comment));
    }
    $output = implode("\n", $arr_diffs) . "\n";
  }
  else {
    $fmt = ($format == 'ediff' ? 'ediff' : 'diff');
    $output = btr::project_diff_get($origin, $project, $lng, $nr, $fmt);
  }
  print $output;

  drupal_exit();
}

/**
 * Callback function for the menu 'project/diff-dl'
 *
 * Similar to project_diff, but return a file for download (not plain text).
 *
 * Examples:
 *   curl https://btranslator.org/project/diff-dl/LibreOffice/sw/sq/2
 *   curl https://btranslator.org/project/diff-dl/LibreOffice/sw/sq/2/ediff
 *   curl https://btranslator.org/project/diff-dl/LibreOffice/sw/sq/4/diff
 *   curl https://btranslator.org/project/diff-dl/LibreOffice/sw/sq/4/ediff
 */
function btrCore_project_diff_download($origin, $project, $lng, $nr =NULL, $format =NULL) {
  $origin = check_plain($origin);
  $project = check_plain($project);
  $lng = check_plain($lng);
  $nr = check_plain($nr);
  $format = check_plain($format);

  $fmt = ($format == 'ediff' ? 'ediff' : 'diff');
  $output = btr::project_diff_get($origin, $project, $lng, $nr, $fmt);

  // Send the output.
  $filename = "$origin-$project-$lng.$nr.$fmt";
  header('Content-Type: text/plain; charset=utf-8');
  header('Content-Disposition: attachment; filename="' . $filename . '"');
  header('Content-Transfer-Encoding: binary');
  header("Content-Length: " . sizeof($output));
  print $output;

  drupal_exit();
}
