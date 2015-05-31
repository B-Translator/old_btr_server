<?php
/**
 * @file
 * Definition of function string_add().
 */

namespace BTranslator;
use \btr;

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
 *   array($sguid, $messages)
 *   - $sguid is the ID of the new string,
 *               or NULL if no string was added
 *   - $messages is an array of notification messages; each notification
 *               message is an array of a message and a type, where
 *               type can be one of 'status', 'warning', 'error'
 */
function string_add($origin, $project, $tplname = NULL, $string, $context = NULL, $notify = FALSE) {
  // Check access permissions.
  if (!user_access('btranslator-suggest')) {
    $msg = t('You do not have enough rights for making suggestions!');
    return array(NULL, array(array($msg, 'error')));
  }

  // Check that the string is being added to a vocabulary project.
  if ($origin != 'vocabulary') {
    $msg = t('Strings can be added only to a vocabulary project.');
    return array(NULL, array(array($msg, 'error')));
  }

  // Check that the language of the project matches
  // the translation language of the user.
  $arr = explode('_', $project);
  $lng = $arr[sizeof($arr) - 1];
  $user = user_load($GLOBALS['user']->uid);
  if ($lng != $user->translation_lng) {
    $msg = t('You cannot add terms to this vocabulary.');
    return array(NULL, array(array($msg, 'error')));
  }

  if ($context === NULL)  $context = $project;
  $sguid = sha1($string . $context);

  // Check whether this string already exists or not.
  $field = btr::db_query(
    'SELECT sguid FROM {btr_strings} WHERE sguid = :sguid',
    array(':sguid' => $sguid)
  )->fetchField();
  if (!empty($field)) {
    $msg = t('This string already exists.');
    return array(NULL, array(array($msg, 'error')));
  }

  // Insert a new string.
  btr::db_insert('btr_strings')
    ->fields(array(
        'string' => $string,
        'context' => $context,
        'sguid' => $sguid,
        'uid' => $GLOBALS['user']->uid,
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
        'count' => 1,
      ))
    ->execute();

  // Get the template id.
  if (empty($tplname))  $tplname = $project;
  $potid = btr::db_query(
    'SELECT potid FROM {btr_templates}
     WHERE pguid = :pguid AND tplname = :tplname',
    array(
      ':pguid' => sha1($origin . $project),
      ':tplname' => $tplname,
    ))
    ->fetchField();

  // Check that the location does not already exist.
  $lid = btr::db_query(
    'SELECT lid FROM {btr_locations}
     WHERE sguid = :sguid AND potid = :potid',
    array(
      ':sguid' => $sguid,
      ':potid' => $potid,
    ))
    ->fetchField();
  if (!empty($lid)) {
    $msg = t('This string already exists.');
    return array(NULL, array(array($msg, 'error')));
  }

  // Insert a new location.
  btr::db_insert('btr_locations')
    ->fields(array(
        'sguid' => $sguid,
        'potid' => $potid,
      ))
    ->execute();

  // Insert the string to the materialized view.
  if ($origin=='vocabulary') {
    $table = 'btr_mv_' . strtolower($project);
    btr::db_insert($table)
      ->fields(array('string' => $string))
      ->execute();
  }

  // Notify users about the new string.
  if ($notify) {
    _btr_new_string_notification($project, $string, $sguid);
  }

  return array($sguid, array());
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
  $notifications = array();
  foreach ($users as $key => $user) {
    $params = array(
      'type' => 'notify-on-new-vocabulary-term',
      'uid' => $user->uid,
      'username' => $user->name,
      'recipient' => $user->name . ' <' . $user->mail . '>',
      'project' => $project,
      'string' => $string,
      'sguid' => $sguid,
      'author' => $GLOBALS['user']->name,
    );
    $notifications[] = $params;
  }
  btr::queue('notifications', $notifications);
}
