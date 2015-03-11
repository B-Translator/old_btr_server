<?php
/**
 * @file
 * Definition of function string_add().
 */

namespace BTranslator;
use \btr;
use \DrupalQueue;

/**
 * Add a new string to a project (useful for vocabularies).
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - origin
 *       Origin (category) of the project.
 *   - project
 *       Name of the project.
 *   - tplname (optional)
 *       Name of the template (POT) file.
 *   - string
 *       String to be added.
 *   - context (optional)
 *       The context of the string.
 *   - notify (optional)
 *       It TRUE, notify translators about the new string.
 *
 * @return
 *   The sguid of the new string, or NULL if such a string already exists.
 */
function string_add($origin, $project, $tplname = NULL, $string, $context = NULL, $notify = FALSE) {
  if ($context === NULL)  $context = '';
  $sguid = sha1($string . $context);

  // Check whether this string already exists or not.
  $field = btr_query(
    'SELECT sguid FROM {btr_strings} WHERE sguid = :sguid',
    array(':sguid' => $sguid)
  )->fetchField();
  if (empty($field)) {
    // Insert a new string.
    btr_insert('btr_strings')
      ->fields(array(
          'string' => $string,
          'context' => $context,
          'sguid' => $sguid,
          'uid' => $GLOBALS['user']->uid,
          'time' => date('Y-m-d H:i:s', REQUEST_TIME),
          'count' => 1,
        ))
      ->execute();
  }

  // Get the template id.
  if (empty($tplname))  $tplname = $project;
  $potid = btr_query(
    'SELECT potid FROM {btr_templates}
     WHERE pguid = :pguid AND tplname = :tplname',
    array(
      ':pguid' => sha1($origin . $project),
      ':tplname' => $tplname,
    ))
    ->fetchField();

  // Check that the location does not already exist.
  $lid = btr_query(
    'SELECT lid FROM {btr_locations}
     WHERE sguid = :sguid AND potid = :potid',
    array(
      ':sguid' => $sguid,
      ':potid' => $potid,
    ))
    ->fetchField();
  if (!empty($lid)) {
    return NULL;
  }

  // Insert a new location.
  btr_insert('btr_locations')
    ->fields(array(
        'sguid' => $sguid,
        'potid' => $potid,
      ))
    ->execute();

  // Insert the string to the materialized view.
  if ($origin=='vocabulary') {
    $table = 'btr_mv_' . strtolower($project);
    btr_insert($table)
      ->fields(array('string' => $string))
      ->execute();
  }

  // Notify users about the new string.
  if ($notify) {
    _btr_new_string_notification($project, $string, $sguid);
  }

  return $sguid;
}


/**
 * Notify users about the new string that was added.
 */
function _btr_new_string_notification($project, $string, $sguid) {
  // Get all the users interested on this project.
  $uids = db_query(
    "SELECT DISTINCT p.entity_id
     FROM {field_data_field_preferred_projects} p
     INNER JOIN {field_data_field_feedback_channels} f
             ON (p.entity_id = f.entity_id)
     WHERE field_preferred_projects_value = :project
       AND field_feedback_channels_value = 'email'",
    array(
      ':project' => "vocabulary/$project",
    ))
    ->fetchCol();
  $users = user_load_multiple($uids);

  // Notify the users about the new term.
  $queue = DrupalQueue::get('notifications');
  $queue->createQueue();  // There is no harm in trying to recreate existing.
  foreach ($users as $key => $user) {
    $notification_params = array(
      'type' => 'notify-on-new-vocabulary-term',
      'uid' => $user->uid,
      'username' => $user->name,
      'recipient' => $user->name . ' <' . $user->mail . '>',
      'project' => $project,
      'string' => $string,
      'sguid' => $sguid,
      'author' => $GLOBALS['user']->name,
    );
    $queue->createItem((object)$notification_params);
  }
}
