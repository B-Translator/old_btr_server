<?php
/**
 * Description of the command 'btr-project-diff'.
 */
function _btr_project_diff_drush_command() {
  return array(
    'description' => "Find differencies between the last snapshot and the current state of the project.",
    'arguments' => array(
      'origin' => 'The origin of the project.',
      'project' => 'The name of the project',
      'lng' => 'The language of translations.',
      'file' => 'The file (full path) where the diffs are outputed.',
    ),
    'options' => array(
      'format' => 'The diff format: \'diff\' or \'ediff\' (default \'diff\').',
      'prefer' => 'List of comma separated users whose opinion will be preferred.',
    ),
    'examples' => array(
      'drush btrp-diff KDE kdeedu sq $(pwd)/kdeadmin-sq.diff' => '',
      'drush btrp-diff KDE kdeedu sq /tmp/test.ediff --format=ediff' => '',
    ),
    'aliases' => array('btrp-diff'),
  );
}

/**
 * Help text for the command 'btr-project-diff'.
 */
function _btr_project_diff_drush_help() {
  return dt("Find differencies with the last snapshot.

The format 'diff' is generated with the normal diff utility.
The format 'ediff' is generated with 'pology/poediff'.
");
}

/**
 * Callback function for the command 'btr-project-diff'.
 */
function drush_btranslator_btr_project_diff($origin, $project, $lng, $file) {
  // Check parameters $origin, $project, $lng.
  _btranslator_drush_check_params($origin, $project, $lng);

  // Get the preferred users.
  $prefer = drush_get_option('prefer', NULL);
  $export_mode = ($prefer == NULL ? 'moste_voted' : 'preferred');
  list($preferred_voters, $error_messages) = btr::utils_get_emails($prefer);
  if (!empty($error_messages)) {
    foreach ($error_messages as $msg)  drush_log($msg[0], $msg[1]);
    drupal_exit();
  }

  // Get the names of the diff files.
  $format = drush_get_option('format');
  if ($format == 'ediff') {
    $file_diff = tempnam('/tmp', 'file_diff_');
    $file_ediff = $file;
  }
  else {
    $file_diff = $file;
    $file_ediff = tempnam('/tmp', 'file_ediff_');
  }

  // Make the diff.
  btr::project_diff($origin, $project, $lng, $file_diff, $file_ediff,
    $export_file=NULL, $export_mode, $preferred_voters);
  foreach(btr::messages() as $msg)  drush_log($msg[0], $msg[1]);

  // Cleanup.
  if ($format == 'ediff') {
    unlink($file_diff);
  }
  else {
    unlink($file_ediff);
  }
}
