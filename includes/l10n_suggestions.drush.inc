<?php

/**
 * @file
 *   Drush commands for importing/exporting *.po files.
 */

/**
 * Implementation of hook_drush_command().
 *
 * @return
 *   An associative array describing commands.
 */
function l10n_suggestions_drush_command() {
  $items = array();

  // The 'po-import' command
  $items['po-import'] = array(
    'description' => "Import a .po file into the DB of l10n_suggestions.",
    'arguments' => array(
      'origin'  => 'the origin of the PO file (ubuntu, GNOME, KDE, etc.)',
      'project' => 'the name of the project that is being imported',
      'lng'     => 'the language of translation (de, fr, sq, en_GB, etc.)',
      'file.po' => 'the PO file to be imported (absolute path or relative to DRUPAL_ROOT)',
    ),
    'options' => array(
    ),
    'examples' => array(
      "drush -l l10n-sq.org impo \\\n   KDE kturtle sq ../kturtle.po" => 'Import kturtle.po Albanian into the DB.',
    ),
    'aliases' => array('impo'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  // The 'po-export' command
  $items['po-export'] = array(
    'description' => "Export a .po file from the DB of l10n_suggestions.",
    'arguments' => array(
      'origin'  => 'the origin of the PO file (ubuntu, GNOME, KDE, etc.)',
      'project' => 'the name of the project that is being exported',
      'lng'     => 'the language of translation (de, fr, sq, en_GB, etc.)',
      'file.po' => 'File to save the exported data (absolute path or relative to DRUPAL_ROOT). If missing, write to stdout.',
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
  $items['l10n_suggestions-exposition'] = array(
    'description' => dt('Importing and exporting PO files from the l10n_suggestions module.'),
    'hidden' => TRUE,
    'topic' => TRUE,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'callback' => 'drush_print_file',
    'callback arguments' => array(dirname(__FILE__) . '/l10n_suggestions-topic.txt'),
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
function l10n_suggestions_drush_help($section) {
  switch ($section) {
    case 'drush:po-import':
      return dt("This command will import into DB a PO file of a project.");
    case 'drush:po-export':
      return dt("This command will export a PO file from the DB.");
    case 'meta:l10n_suggestions:title':
      return dt("L10n_Suggestions Commands");
    case 'meta:l10n_suggestions:summary':
      return dt("Handle the import/export of PO files for the module l10n_suggestions.");
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
 * Command callback for po-import.
 */
function drush_l10n_suggestions_po_import($origin, $project, $lng, $file) {
  $path = drupal_get_path('module', 'l10n_suggestions') . '/import';
  $output = shell_exec("$path/po_import.php $origin $project $lng $file");
  print $output;
}

/**
 * Command callback for po-export.
 */
function drush_l10n_suggestions_po_export($origin, $project, $lng, $file =NULL) {
  $path = drupal_get_path('module', 'l10n_suggestions') . '/import';
  $output = shell_exec("$path/po_export.php $origin $project $lng $file");
  print $output;
}
?>