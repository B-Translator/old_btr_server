<?php
/**
 * Description of the command 'btr-vocabulary-add'.
 */
function _btr_vocabulary_add_drush_command() {
  return array(
    'description' => "Create a new vocabulary.",
    'arguments' => array(
      'name' => 'The name of the vocabulary.',
      'lng' => 'The language of the vocabulary.',
      'pot_file' => 'The POT file with the initial terms (optional).',
    ),
    'options' => array(),
    'examples' => array(
      "drush btrv-add ICT sq" => '',
    ),
    'aliases' => array('btrv-add'),
  );
}

/**
 * Help text for the command 'btr-vocabulary-add'.
 */
function _btr_vocabulary_add_drush_help() {
  return dt("Create  a new vocabulary.");
}

/**
 * Callback function for the command 'btr-vocabulary-add'.
 */
function drush_btranslator_btr_vocabulary_add($name, $lng, $pot_file = NULL) {
  btr::vocabulary_add($name, $lng, $pot_file);
}
