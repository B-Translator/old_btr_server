<?php
/**
 * @file
 * Creating a vocabulary.
 */

namespace BTranslator;
use \btr;

/**
 * Create a new vocabulary.
 *
 * @param $name
 *   The name of the vocabulary.
 *
 * @param $lng
 *   The language of the vocabulary.
 *
 * @param $pot_file (optional)
 *   The POT file with the initial terms.
 */
function vocabulary_add($name, $lng, $pot_file = NULL) {
  $path = drupal_get_path('module', 'btrCore');
  if ($pot_file === NULL) {
    $pot_file = $path . '/data/import/vocabulary/empty.po';
  }
  $origin = 'vocabulary';
  $project = $name . '_' . $lng;
  btr::project_add($origin, $project, $pot_file);

  // Create a custom contact form.
  \db_delete('contact')->condition('category', $project)->execute();
  \db_insert('contact')->fields(array(
      'category' => $project,
      'recipients' => variable_get('site_mail'),
      'reply' => '',
    ))->execute();

  // Update mv tables.
  shell_exec($path . '/data/db/update-mv-tables.sh');
}
