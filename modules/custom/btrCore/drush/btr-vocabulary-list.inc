<?php
/**
 * Description of the command 'btr-vocabulary-list'.
 */
function _btr_vocabulary_list_drush_command() {
  return array(
    'description' => "List vocabularies.",
    'arguments' => array(),
    'options' => array(
      'name' => 'The pattern for matching the vocabulary name.',
    ),
    'examples' => array(
      "drush btrv-ls --name=%_sq" => 'List vocabularies of language sq.',
    ),
    'aliases' => array('btrv-ls'),
  );
}

/**
 * Help text for the command 'btr-vocabulary-list'.
 */
function _btr_vocabulary_list_drush_help() {
  return dt("List vocabularies.

The option 'name' can contain '%' (for LIKE matches).
");
}

/**
 * Callback function for the command 'btr-vocabulary-list'.
 */
function drush_btranslator_btr_vocabulary_list() {
  $project = drush_get_option('name');
  $origin = 'vocabulary';
  $project_list = btr::project_ls($origin, $project);

  foreach ($project_list as $project) {
    $project = str_replace('vocabulary/', '', $project);
    drush_print($project);
  }
}
