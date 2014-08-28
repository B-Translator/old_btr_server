<?php
/**
 * Description of the command 'btr-project-add'.
 */
function _btr_project_add_drush_command() {
  return array(
    'description' => "Import the POT files of a project into the B-Translator DB.",
    'arguments' => array(
      'origin' => 'The origin of the project (ubuntu, GNOME, KDE, etc.)',
      'project' => 'The name of the project that is being imported.',
      'path' => 'The directory of the POT files of the project (absolute path or relative to DRUPAL_ROOT).',
    ),
    'options' => array(
      'user'  => 'The username of the user that is importing templates.',
    ),
    'examples' => array(
      "drush btrp-add KDE kturtle \\      \n      \$(pwd)/kturtle/" => 'Import kturtle into the DB.',
    ),
    'aliases' => array('btrp-add'),
  );
}

/**
 * Help text for the command 'btr-project-add'.
 */
function _btr_project_add_drush_help() {
  return dt("Import the POT files of a project into the B-Translator DB.");
}

/**
 * Callback function for the command 'btr-project-add'.
 */
function drush_btranslator_btr_project_add($origin, $project, $path) {
  btr::project_add($origin, $project, $path, $GLOBALS['user']->uid);
}
