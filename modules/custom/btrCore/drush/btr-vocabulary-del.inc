<?php
/**
 * Description of the command 'btr-vocabulary-del'.
 */
function _btr_vocabulary_del_drush_command() {
  return array(
    'description' => "Delete a vocabulary.",
    'arguments' => array(
      'name' => 'The name of the vocabulary.',
      'lng' => 'The language of the vocabulary.',
    ),
    'options' => array(),
    'examples' => array(
      "drush btrv-del ICT sq" => '',
    ),
    'aliases' => array('btrv-del'),
  );
}

/**
 * Help text for the command 'btr-vocabulary-del'.
 */
function _btr_vocabulary_del_drush_help() {
  return dt("Delete a vocabulary.");
}

/**
 * Callback function for the command 'btr-vocabulary-del'.
 */
function drush_btranslator_btr_vocabulary_del($name, $lng) {
  $origin = 'vocabulary';
  $project = $name . '_' . $lng;
  _btranslator_drush_check_params($origin, $project, $lng);

  btr::vocabulary_del($name, $lng);
}
