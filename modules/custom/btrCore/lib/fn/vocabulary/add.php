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
 * @param $uid
 *   ID of the user that is creating the vocabulary.
 */
function vocabulary_add($name, $lng, $uid = 1) {
  $origin = 'vocabulary';
  $project = $name . '_' . $lng;
  $path = drupal_get_path('module', 'btrCore');
  $pot_file = '/tmp/' . $project . '.pot';
  touch($pot_file);
  btr::project_add($origin, $project, $pot_file, $uid);
  unlink($pot_file);

  // Create a custom contact form.
  \db_delete('contact')->condition('category', $project)->execute();
  \db_insert('contact')->fields([
      'category' => $project,
      'recipients' => variable_get('site_mail'),
      'reply' => '',
    ])->execute();

  // Update mv tables.
  shell_exec($path . '/data/db/update-mv-tables.sh');

  // Add user as admin of the project.
  $user = user_load($uid);
  btr::project_add_admin($origin, $project, $lng, $user->init);

  // Subscribe user to this project.
  btr::project_subscribe($origin, $project, $uid);
}
