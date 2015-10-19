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
    ),
    'options' => array(
      'user'  => 'The username of the user that is importing the vocabulary.',
    ),
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
function drush_btranslator_btr_vocabulary_add($name, $lng) {
  // Check the language.
  _btranslator_drush_check_params(NULL, NULL, $lng);

  // Add the vocabulary.
  btr::vocabulary_add($name, $lng);
  foreach(btr::messages() as $msg)  drush_log($msg[0], $msg[1]);
}
