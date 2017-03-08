<?php
/**
 * @file
 * Definition of function vocabulary_string_add().
 */

namespace BTranslator;
use \btr;

/**
 * Add a new string to a vocabulary.
 *
 * @param $name
 *   The name of the vocabulary.
 *
 * @param $lng
 *   The language of the vocabulary.
 *
 * @param $string
 *   String to be added.
 *
 * @param $uid
 *   Id of the user that is adding the string.
 *
 * @param $notify (optional)
 *   It TRUE, notify translators about the new string.
 *
 * @return
 *   The $sguid of the new string.
 */
function vocabulary_string_add($name, $lng, $string, $uid, $notify = FALSE) {
  // Set some variables.
  $origin = 'vocabulary';
  $project = $name . '_' . $lng;
  $tplname = $project;
  $context = $project;
  $sguid = sha1($string . $context);

  // Insert a new string.
  $q = 'SELECT sguid FROM {btr_strings} WHERE sguid = :sguid';
  $field_sguid = btr::db_query($q, [':sguid' => $sguid])->fetchField();
  if (!empty($field_sguid)) {
    $notify = FALSE;
  }
  else {
    btr::db_insert('btr_strings')
      ->fields([
          'string' => $string,
          'context' => $context,
          'sguid' => $sguid,
          'uid' => $uid,
          'time' => date('Y-m-d H:i:s', REQUEST_TIME),
          'count' => 0,
        ])
      ->execute();
  }

  // Get the template id.
  $query = 'SELECT potid FROM {btr_templates} WHERE pguid = :pguid AND tplname = :tplname';
  $args = [':pguid' => sha1($origin . $project), ':tplname' => $tplname];
  $potid = btr::db_query($query, $args)->fetchField();

  // Insert a new location.
  $query = 'SELECT lid FROM {btr_locations} WHERE sguid = :sguid AND potid = :potid';
  $args = [':sguid' => $sguid, ':potid' => $potid];
  $lid = btr::db_query($query, $args)->fetchField();
  if (!empty($lid)) {
    $notify = FALSE;
  }
  else {
    btr::db_insert('btr_locations')
      ->fields(['sguid' => $sguid, 'potid' => $potid])
      ->execute();
  }

  // Insert the string to the materialized view.
  $table = 'btr_mv_' . strtolower($project);
  btr::db_delete($table)->condition('string', $string)->execute();
  btr::db_insert($table)->fields(['string' => $string])->execute();

  // Notify users about the new string.
  if ($notify) {
    _btr_new_string_notification($project, $string, $sguid, $uid);
  }

  return $sguid;
}


/**
 * Notify users about the new string that was added.
 */
function _btr_new_string_notification($project, $string, $sguid, $uid) {
  $importer = user_load($uid);

  // Get all the users interested on this project.
  $uids = \db_query(
    "SELECT DISTINCT entity_id
     FROM {field_data_field_projects}
     WHERE field_projects_value = :project",
    [ ':project' => "vocabulary/$project" ]
  )->fetchCol();
  $users = user_load_multiple($uids);

  // Notify the users about the new term.
  $notifications = array();
  foreach ($users as $key => $user) {
    if ($user->status == 0) continue;
    $params = array(
      'type' => 'notify-on-new-vocabulary-term',
      'uid' => $user->uid,
      'username' => $user->name,
      'recipient' => $user->name . ' <' . $user->mail . '>',
      'project' => $project,
      'string' => $string,
      'sguid' => $sguid,
      'author' => $importer->name,
    );
    $notifications[] = $params;
  }
  btr::queue('notifications', $notifications);
}
