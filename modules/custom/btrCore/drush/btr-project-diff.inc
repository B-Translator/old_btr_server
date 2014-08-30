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
  $format = drush_get_option('format');

  // Get the names of the diff files.
  if ($format == 'ediff') {
    $file_diff = tempnam('/tmp', 'file_diff_') . '.diff';
    $file_ediff = $file;
  }
  else {
    $file_diff = $file;
    $file_ediff = tempnam('/tmp', 'file_ediff_') . '.ediff';
  }

  // Make the diff.
  btr::project_diff($origin, $project, $lng, $file_diff, $file_ediff);


  // Cleanup.
  if ($format == 'ediff') {
    exec("rm $file_diff");
  }
  else {
    exec("rm $file_ediff");
  }
}
