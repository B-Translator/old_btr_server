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

  // The command 'btr-project-import-templates'
  $items['btr-project-import-templates'] = array(
    'description' => "Import the POT files of a project into the B-Translator DB.",
    'arguments' => array(
      'origin' => 'The origin of the project (ubuntu, GNOME, KDE, etc.)',
      'project' => 'The name of the project that is being imported.',
      'path' => 'The directory of the POT files of the project (absolute path or relative to DRUPAL_ROOT).',
    ),
    'options' => array(
    ),
    'examples' => array(
      "drush btr-impot KDE kturtle \\      \n      \$(pwd)/kturtle/" => 'Import kturtle into the DB.',
    ),
    'aliases' => array('btr-impot'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  // The command 'btr-project-import-translations'
  $items['btr-project-import-translations'] = array(
    'description' => "Import the translation (PO) files of a project/language into the DB.",
    'arguments' => array(
      'origin'  => 'The origin of the project (ubuntu, GNOME, KDE, etc.)',
      'project' => 'The name of the project.',
      'lng'     => 'The language of translation (de, fr, sq, en_GB, etc.)',
      'path' => 'The directory of the POT files of the project (absolute path or relative to DRUPAL_ROOT).',
    ),
    'options' => array(
    ),
    'examples' => array(
      "drush btr-impo \\\n   KDE kturtle fr \$(pwd)/kturtle_fr/" => 'Import the French translation of kturtle into the DB.',
    ),
    'aliases' => array('btr-impo'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  // The 'po-export' command
  $items['po-export'] = array(
    'description' => "Export the PO file of a translation from the DB.",
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
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  // These will appear in the list of topics when `drush topic` is executed.
  // To view this topic, run `drush --include=/full/path/to/examples topic`
  $items['btranslator-exposition'] = array(
    'description' => dt('Importing and exporting PO files from B-Translator.'),
    'hidden' => TRUE,
    'topic' => TRUE,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
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
    case 'drush:btr-project-import-templates':
      return dt("Import the POT files of a project into the B-Translator DB.");
    case 'drush:btr-project-import-translations':
      return dt("Import the PO files of a project/language into the DB.");
    case 'drush:po-export':
      return dt("This command will export a PO file from the DB.");
    case 'meta:btranslator:title':
      return dt("B-Translator Commands");
    case 'meta:btranslator:summary':
      return dt("Handle the import/export of PO/POT files for B-Translator.");
  }
}

/**
 * Implementation of drush_hook_COMMAND_validate().
 *
 * The validate command should exit with
 * `return drush_set_error(...)` to stop execution of
 * the command.  In practice, calling drush_set_error
 * OR returning FALSE is sufficient.  See drush.api.php
 * for more details.
 */
/*
  function drush_make_me_a_sandwitch_validate() {
  $name = posix_getpwuid(posix_geteuid());
  if ($name['name'] !== 'root') {
  return drush_set_error('MAKE_IT_YOUSELF', dt('What? Make your own sandwitch.'));
  }
  }
*/

/**
 * Command callback for btr-project-import-templates.
 */
function drush_btranslator_btr_project_import_templates($origin, $project, $path) {
  module_load_include('inc', 'btrCore', 'data/lib/project/import_pot');
  BTranslator\Data\Project\import($origin, $project, $path);
}

/**
 * Command callback for btr-project-import-translations.
 */
function drush_btranslator_btr_project_import_translations($origin, $project, $lng, $path) {
  module_load_include('inc', 'btrCore', 'data/lib/import_po');
  BTranslator\Data\Project\import_po_files($origin, $project, $lng, $path);
}

/**
 * Command callback for po-export.
 */
function drush_btranslator_po_export($origin, $project, $lng, $file =NULL) {
  $path = drupal_get_path('module', 'btrCore') . '/data/export';
  $output = shell_exec("$path/po_export.php $origin $project $lng $file");
  print $output;
}
