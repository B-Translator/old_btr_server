<?php
/**
 * Description of the command 'btr-project-add'.
 */
function _btr_project_add_drush_command() {
  return array(
    'description' => "Create a project and import its POT files into the DB.",
    'arguments' => array(
      'origin' => 'The origin of the project (ubuntu, GNOME, KDE, etc.)',
      'project' => 'The name of the project that is being imported.',
      'path' => 'The directory of the POT files of the project (absolute path or relative to DRUPAL_ROOT). It can also be a single POT/PO file.',
    ),
    'options' => array(
      'user'  => 'The username of the user that is importing templates.',
    ),
    'examples' => array(
      "drush btrp-add KDE kturtle \$(pwd)/kturtle/" => '',
    ),
    'aliases' => array('btrp-add'),
  );
}

/**
 * Help text for the command 'btr-project-add'.
 */
function _btr_project_add_drush_help() {
  return dt("Create a project and import its POT files into the DB.

If such a project already exists (the same origine and project)
it will be deleted first (related data will be erased as well).
");
}

/**
 * Callback function for the command 'btr-project-add'.
 */
function drush_btranslator_btr_project_add($origin, $project, $path) {
  btr::project_add($origin, $project, $path);
  foreach(btr::messages() as $msg)  drush_log($msg[0], $msg[1]);
}
