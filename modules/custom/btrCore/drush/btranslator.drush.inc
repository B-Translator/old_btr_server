<?php
/**
 * @file
 * Drush commands for importing/exporting *.po files.
 */

require_once(dirname(__FILE__) . '/btr-project-list.inc');
require_once(dirname(__FILE__) . '/btr-project-add.inc');
require_once(dirname(__FILE__) . '/btr-project-import.inc');
require_once(dirname(__FILE__) . '/btr-project-delete.inc');
require_once(dirname(__FILE__) . '/btr-project-export.inc');
require_once(dirname(__FILE__) . '/btr-project-diff.inc');
require_once(dirname(__FILE__) . '/btr-project-diff-ls.inc');
require_once(dirname(__FILE__) . '/btr-project-diff-get.inc');
require_once(dirname(__FILE__) . '/btr-project-snapshot.inc');
require_once(dirname(__FILE__) . '/btr-vote-import.inc');
require_once(dirname(__FILE__) . '/btr-vocabulary-add.inc');
require_once(dirname(__FILE__) . '/btr-vocabulary-del.inc');
require_once(dirname(__FILE__) . '/btr-vocabulary-list.inc');
require_once(dirname(__FILE__) . '/btr-vocabulary-get.inc');
require_once(dirname(__FILE__) . '/btr-vocabulary-import.inc');

/**
 * Implementation of hook_drush_command().
 *
 * @return
 *   An associative array describing commands.
 */
function btranslator_drush_command() {
  $items = array(
    'btr-project-list' => _btr_project_list_drush_command(),
    'btr-project-add' => _btr_project_add_drush_command(),
    'btr-project-import' => _btr_project_import_drush_command(),
    'btr-project-delete' => _btr_project_delete_drush_command(),
    'btr-project-export' => _btr_project_export_drush_command(),
    'btr-project-diff' => _btr_project_diff_drush_command(),
    'btr-project-diff-ls' => _btr_project_diff_ls_drush_command(),
    'btr-project-diff-get' => _btr_project_diff_get_drush_command(),
    'btr-project-snapshot' => _btr_project_snapshot_drush_command(),
    'btr-vote-import' => _btr_vote_import_drush_command(),
    'btr-vocabulary-add' => _btr_vocabulary_add_drush_command(),
    'btr-vocabulary-del' => _btr_vocabulary_del_drush_command(),
    'btr-vocabulary-list' => _btr_vocabulary_list_drush_command(),
    'btr-vocabulary-get' => _btr_vocabulary_get_drush_command(),
    'btr-vocabulary-import' => _btr_vocabulary_import_drush_command(),
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
      return _btr_project_list_drush_help();
    case 'drush:btr-project-add':
      return _btr_project_add_drush_help();
    case 'drush:btr-project-import':
      return _btr_project_import_drush_help();
    case 'drush:btr-project-export':
      return _btr_project_export_drush_help();
    case 'drush:btr-project-delete':
      return _btr_project_delete_drush_help();
    case 'drush:btr-project-diff':
      return _btr_project_diff_drush_help();
    case 'drush:btr-project-diff-ls':
      return _btr_project_diff_ls_drush_help();
    case 'drush:btr-project-diff-get':
      return _btr_project_diff_get_drush_help();
    case 'drush:btr-project-snapshot':
      return _btr_project_snapshot_drush_help();
    case 'drush:btr-vote-import':
      return _btr_vote_import_drush_help();
    case 'drush:btr-vocabulary-add':
      return _btr_vocabulary_add_drush_help();
    case 'drush:btr-vocabulary-del':
      return _btr_vocabulary_del_drush_help();
    case 'drush:btr-vocabulary-list':
      return _btr_vocabulary_list_drush_help();
    case 'drush:btr-vocabulary-get':
      return _btr_vocabulary_get_drush_help();
    case 'drush:btr-vocabulary-import':
      return _btr_vocabulary_import_drush_help();

    case 'meta:btranslator:title':
      return dt("B-Translator Commands");
    case 'meta:btranslator:summary':
      return dt("Handle the import/export of PO/POT files for B-Translator.");
  }
}

/**
 * Check that the parameters $origin, $project and $lng exist (are valid).
 */
function _btranslator_drush_check_params($origin, $project = NULL, $lng = NULL) {
  // Make sure that the given origin and project do exist.
  if ($project !== NULL and !btr::project_exists($origin, $project)) {
    drush_log(t("The project '!project' does not exist.",
        array('!project' => "$origin/$project")), 'error');
    drupal_exit();
  }

  // Make sure that the given language exists.
  if ($lng !== NULL and !in_array($lng, btr::languages_get())) {
    drush_log(t("The language '!lng' does not exist.", ['!lng' => "$lng"]), 'error');
    drupal_exit();
  }
}
