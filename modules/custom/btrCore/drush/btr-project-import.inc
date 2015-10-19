<?php
/**
 * Description of the command 'btr-project-import'.
 */
function _btr_project_import_drush_command() {
  return array(
    'description' => "Import the PO files of an origin/project/lng into the DB.",
    'arguments' => array(
      'origin'  => 'The origin of the project (ubuntu, GNOME, KDE, etc.)',
      'project' => 'The name of the project.',
      'lng'     => 'The language of translation (de, fr, sq, en_GB, etc.)',
      'path' => 'The directory of the PO files of the project (absolute path or relative to DRUPAL_ROOT).',
    ),
    'options' => array(
      'user'  => 'The username of the user that is importing translations.',
    ),
    'examples' => array(
      "drush btrp-import \\\n   KDE kturtle fr \$(pwd)/kturtle_fr/" => 'Import the French translation of kturtle into the DB.',
    ),
    'aliases' => array('btrp-import'),
  );
}

/**
 * Help text for the command 'btr-project-import'.
 */
function _btr_project_import_drush_help() {
  return dt("Import the PO files of an origin/project/lng into the DB.

Templates of the project (POT files) must have been imported first.
If the corresponding template for a file does not exist, it will not
be imported.
");
}

/**
 * Callback function for the command 'btr-project-import'.
 */
function drush_btranslator_btr_project_import($origin, $project, $lng, $path) {
  // Check parameters $origin, $project, $lng.
  _btranslator_drush_check_params($origin, $project, $lng);

  // Import the project.
  btr::project_import($origin, $project, $lng, $path);
  foreach(btr::messages() as $msg)  drush_log($msg[0], $msg[1]);
}
