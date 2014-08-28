<?php
/**
 * Description of the command 'btr-vote-import'.
 */
function _btr_vote_import_drush_command() {
  return array(
    'description' => "Bulk import of translations and votes from PO files.",
    'arguments' => array(
      'lng'     => 'The language of translation (de, fr, sq, en_GB, etc.)',
      'path' => 'The directory of the PO files (absolute path or relative to DRUPAL_ROOT).',
    ),
    'options' => array(
      'user'  => 'The username of the user who has made the translations.',
    ),
    'examples' => array(
      "drush btrp-vote --user=user1 fr \$(pwd)/kturtle_fr/" => 'Vote as user1 all the given French translations.',
    ),
    'aliases' => array('btr-vote'),
  );
}

/**
 * Help text for the command 'btr-vote-import'.
 */
function _btr_vote_import_drush_help() {
  return dt('Bulk import of translations and votes from PO files.');
}

/**
 * Callback function for the command 'btr-vote-import'.
 */
function drush_btranslator_btr_vote_import($lng, $path) {
  btr::vote_import($GLOBALS['user']->uid, $lng, $path);
}
