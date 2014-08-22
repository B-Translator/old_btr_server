<?php
/**
 * @file
 * Drush commands for importing/exporting *.po files.
 */

/**
 * Implementation of hook_drush_command().
 *
 * @return
 *   An associative array describing commands.
 */
function btranslator_drush_command() {
  $items = array();

  // The command 'btr-project-list'
  $items['btr-project-list'] = array(
    'description' => "List imported projects, filtered by origin/project.

Options origin and project can contain '%' (for LIKE matches).
If --project='-' then only a list of 'origin' is outputed.
",
    'arguments' => array(
    ),
    'options' => array(
      'origin' => 'The pattern for matching the origin.',
      'project' => 'The pattern for matching the project.',
    ),
    'examples' => array(
      "drush btrp-ls --origin=KDE --project=k%" => 'List KDE projects that start with k.',
      "drush btrp-ls --project=-" => 'Get a list of all origins.'
    ),
    'aliases' => array('btrp-ls'),
    //'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

  // The command 'btr-project-import-templates'
  $items['btr-project-import-templates'] = array(
    'description' => "Import the POT files of a project into the B-Translator DB.
",
    'arguments' => array(
      'origin' => 'The origin of the project (ubuntu, GNOME, KDE, etc.)',
      'project' => 'The name of the project that is being imported.',
      'path' => 'The directory of the POT files of the project (absolute path or relative to DRUPAL_ROOT).',
    ),
    'options' => array(
    ),
    'examples' => array(
      "drush btrp-impot KDE kturtle \\      \n      \$(pwd)/kturtle/" => 'Import kturtle into the DB.',
    ),
    'aliases' => array('btrp-impot'),
    //'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

  // The command 'btr-project-import-translations'
  $items['btr-project-import-translations'] = array(
    'description' => "Import the translation (PO) files of a project/language into the DB.
",
    'arguments' => array(
      'origin'  => 'The origin of the project (ubuntu, GNOME, KDE, etc.)',
      'project' => 'The name of the project.',
      'lng'     => 'The language of translation (de, fr, sq, en_GB, etc.)',
      'path' => 'The directory of the PO files of the project (absolute path or relative to DRUPAL_ROOT).',
    ),
    'options' => array(
    ),
    'examples' => array(
      "drush btrp-impo \\\n   KDE kturtle fr \$(pwd)/kturtle_fr/" => 'Import the French translation of kturtle into the DB.',
    ),
    'aliases' => array('btrp-impo'),
  );

  // The command 'btr-project-erase'
  $items['btr-project-erase'] = array(
    'description' => "Delete everything related to the given origin and project
(but not the strings, translations, etc.)

If no project is given, then all the projects of the given origin
will be deleted. If the origin is NULL, then all the projects
of the given name (from any origin) will be deleted.
",
    'arguments' => array(
    ),
    'options' => array(
      'origin' => 'The origin of the project to be deleted.',
      'project' => 'The name of the project to be deleted.',
      'purge' => 'If true, then snapshots and diffs are deleted as well.',
    ),
    'examples' => array(
      "drush btrp-erase --origin=KDE --project=kturtle" => 'Erase KDE/kturtle from the DB.',
    ),
    'aliases' => array('btrp-erase'),
    //'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

  // The 'po-export' command
  $items['po-export'] = array(
    'description' => "Export the PO file of a translation from the DB.
",
    'arguments' => array(
      'origin'  => 'The origin of the project (ubuntu, GNOME, KDE, etc.)',
      'project' => 'The name of the project that is being exported.',
      'lng'     => 'The language of translation (de, fr, sq, en_GB, etc.)',
      'file.po' => 'File to save the exported translation (absolute path or relative to DRUPAL_ROOT). If missing, write to stdout.',
    ),
    'options' => array(
    ),
    'examples' => array(
      "drush -l l10n-sq.org expo \\\n  KDE kturtle sq ../kturtle_sq.po" => 'Export KDE/kturtle Albanian into kturtle_sq.po.',
    ),
    'aliases' => array('expo'),
  );

  // These will appear in the list of topics when `drush topic` is executed.
  // To view this topic, run `drush --include=/full/path/to/examples topic`
  $items['btranslator-exposition'] = array(
    'description' => dt('Importing and exporting PO files from B-Translator.'),
    'hidden' => TRUE,
    'topic' => TRUE,
    'callback' => 'drush_print_file',
    'callback arguments' => array(dirname(__FILE__) . '/btranslator-topic.txt'),
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function btranslator_drush_help($section) {
  switch ($section) {
    case 'drush:btr-project-list':
      return dt("List imported projects, filtered by origin/project.");
    case 'drush:btr-project-import-templates':
      return dt("Import the POT files of a project into the B-Translator DB.");
    case 'drush:btr-project-import-translations':
      return dt("Import the PO files of a project/language into the DB.");
    case 'drush:btr-project-erase':
      return dt("Erase a project from the DB.");
    case 'drush:po-export':
      return dt("This command will export a PO file from the DB.");
    case 'meta:btranslator:title':
      return dt("B-Translator Commands");
    case 'meta:btranslator:summary':
      return dt("Handle the import/export of PO/POT files for B-Translator.");
  }
}

/**
 * Command callback for btr-project-list.
 */
function drush_btranslator_btr_project_list() {
  $origin = drush_get_option('origin');
  $project = drush_get_option('project');

  module_load_include('inc', 'btrCore', 'data/lib/project/list');
  $project_list = BTranslator\Data\Project\project_list($origin, $project);

  foreach ($project_list as $project) {
    drush_print($project);
  }
}

/**
 * Command callback for btr-project-import-templates.
 */
function drush_btranslator_btr_project_import_templates($origin, $project, $path) {
  global $user;
  module_load_include('inc', 'btrCore', 'data/lib/project/import_pot');
  BTranslator\Data\Project\import($origin, $project, $path, $user->uid);
}

/**
 * Command callback for btr-project-import-translations.
 */
function drush_btranslator_btr_project_import_translations($origin, $project, $lng, $path) {
  module_load_include('inc', 'btrCore', 'data/lib/project/import_po');
  try {
    $errors = BTranslator\Data\Project\import_po_files($origin, $project, $lng, $path, $GLOBALS['user']->uid);
    foreach ($errors as $error)  drush_log($error, 'error');
  }
  catch (Exception $e) {
    $trace = $e->getTraceAsString();
    $trace = preg_replace('/^#0 .*/', '', $trace);
    $trace = str_replace(DRUPAL_ROOT.'/', '', $trace);
    drush_log($trace, 'error');
  }
}

/**
 * Command callback for btr-project-erase.
 */
function drush_btranslator_btr_project_erase() {
  $origin = drush_get_option('origin');
  $project = drush_get_option('project');
  $purge = drush_get_option('purge');
  $purge = ($purge == 'false' ? FALSE : TRUE);

  module_load_include('inc', 'btrCore', 'data/lib/project/erase');
  BTranslator\Data\Project\erase($origin, $project, $purge);
}

/**
 * Command callback for po-export.
 */
function drush_btranslator_po_export($origin, $project, $lng, $file =NULL) {
  $path = drupal_get_path('module', 'btrCore') . '/data/export';
  $output = shell_exec("$path/po_export.php $origin $project $lng $file");
  print $output;
}
