<?php
/**
 * Description of the command 'btr-project-snapshot'.
 */
function _btr_project_snapshot_drush_command() {
  return array(
    'description' => "Make a snapshot of the project.",
    'arguments' => array(
      'origin' => 'The origin of the project.',
      'project' => 'The name of the project',
      'lng' => 'The language of translations.',
      'comment' => 'A comment about the snapshot.',
    ),
    'options' => array(
    ),
    'examples' => array(
      'drush btrp-snapshot KDE kdeedu sq "Merging upstream before the new release."' => '',
    ),
    'aliases' => array('btrp-snapshot'),
  );
}

/**
 * Help text for the command 'btr-project-snapshot'.
 */
function _btr_project_snapshot_drush_help() {
  return dt("Find differencies with the last snapshot.

The format 'diff' is generated with the normal diff utility.
The format 'ediff' is generated with 'pology/poediff'.
");
}

/**
 * Callback function for the command 'btr-project-snapshot'.
 */
function drush_btranslator_btr_project_snapshot($origin, $project, $lng, $comment) {
  btr::project_snapshot($origin, $project, $lng, $comment);
}
