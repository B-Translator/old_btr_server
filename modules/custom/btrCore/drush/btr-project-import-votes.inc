<?php
/**
 * Description of the command 'btr-project-import-votes'.
 */
function _btr_project_import_votes_drush_command() {
  return array(
    'description' => "Bulk import of translations and votes from PO files.
",
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
    'aliases' => array('btrp-vote'),
  );
}

/**
 * Help text for the command 'btr-project-import-votes'.
 */
function _btr_project_import_votes_drush_help() {
  return dt('Import votes from PO files.');
}

/**
 * Callback function for the command 'btr-project-import-votes'.
 */
function drush_btranslator_btr_project_import_votes($lng, $path) {
  btr::translations_import($GLOBALS['user']->uid, $lng, $path);
}
