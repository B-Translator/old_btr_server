<?php
/**
 * Description of the command 'btr-project-import'.
 */
function _btr_project_import_drush_command() {
  return array(
    'description' => "Import the translation (PO) files of a project/language into the DB.
",
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
  return dt("Import the PO files of a project/language into the DB.");
}

/**
 * Callback function for the command 'btr-project-import'.
 */
function drush_btranslator_btr_project_import($origin, $project, $lng, $path) {
  try {
    $errors = btr::project_import($origin, $project, $lng, $path, $GLOBALS['user']->uid);
    foreach ($errors as $error)  drush_log($error, 'error');
  }
  catch (Exception $e) {
    $trace = $e->getTraceAsString();
    $trace = preg_replace('/^#0 .*/', '', $trace);
    $trace = str_replace(DRUPAL_ROOT.'/', '', $trace);
    drush_log($trace, 'error');
  }
}
