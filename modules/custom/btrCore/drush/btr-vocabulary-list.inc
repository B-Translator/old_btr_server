<?php
/**
 * Description of the command 'btr-vocabulary-list'.
 */
function _btr_vocabulary_list_drush_command() {
  return array(
    'description' => "List vocabularies.",
    'arguments' => array(),
    'options' => array(
      'lng' => 'The code of the language.',
      'name' => 'The pattern for matching the vocabulary name.',
    ),
    'examples' => array(
      "drush btrv-ls --lng=sq" => 'List vocabularies of language sq.',
      "drush btrv-ls --name=ICT%" => 'List vocabularies that start with ICT.',
    ),
    'aliases' => array('btrv-ls'),
  );
}

/**
 * Help text for the command 'btr-vocabulary-list'.
 */
function _btr_vocabulary_list_drush_help() {
  return dt("List vocabularies.

The option 'lng' is the code of the language, for example 'sq', 'fr', 'de', etc.
The option 'name' can contain '%' (for LIKE matches).
");
}

/**
 * Callback function for the command 'btr-vocabulary-list'.
 */
function drush_btranslator_btr_vocabulary_list() {
  $name = drush_get_option('name', '%');
  $lng = drush_get_option('lng', '%');
  $project = $name . '_' . $lng;
  $origin = 'vocabulary';
  $project_list = btr::project_ls($origin, $project);

  foreach ($project_list as $project) {
    $project = str_replace('vocabulary/', '', $project);
    drush_print($project);
  }
}
