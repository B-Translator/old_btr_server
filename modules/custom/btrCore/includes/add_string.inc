<?php
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
function btr_add_string($origin, $project, $tplname =NULL, $string, $context =NULL, $notify =FALSE) {
  if ($context === NULL)  $context = '';
  $sguid = sha1($string . $context);

  $db = $GLOBALS['btr_db'];

  // Check whether this string already exists or not.
  $query = "SELECT sguid FROM {btr_strings} WHERE sguid = :sguid";
  $args = array(':sguid' => $sguid);
  $field = $db->query($query, $args)->fetchField();
  if (empty($field)) {
    // Insert a new string.
    $db->insert('btr_strings')
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
  $query = "SELECT potid FROM {btr_templates}
            WHERE pguid = :pguid AND tplname = :tplname";
  $args = array(
    ':pguid' => sha1($origin . $project),
    ':tplname' => $tplname,
  );
  $potid = $db->query($query, $args)->fetchField();

  // Check that the location does not already exist.
  $query = "SELECT lid FROM {btr_locations}
            WHERE sguid = :sguid AND potid = :potid";
  $args = array(
    ':sguid' => $sguid,
    ':potid' => $potid,
  );
  $lid = $db->query($query, $args)->fetchField();
  if (!empty($lid)) {
    return NULL;
  }

  // Insert a new location.
  $db->insert('btr_locations')
    ->fields(array(
        'sguid' => $sguid,
        'potid' => $potid,
      ))
    ->execute();

  // Notify translators about the new string.
  if ($notify) {
    _btr_new_string_notification($project, $string, $sguid);
  }

  return $sguid;
}


/**
 * Delete the string with the given id.
 */
function btr_del_string($sguid) {
  $db = $GLOBALS['btr_db'];
  $db->delete('btr_strings')->condition('sguid', $sguid)->execute();
  $db->delete('btr_locations')->condition('sguid', $sguid)->execute();
  $db->delete('btr_translations')->condition('sguid', $sguid)->execute();
}


/**
 * Notify translators about the new string that was added.
 */
function _btr_new_string_notification($project, $string, $sguid) {
  // Get the language of the project.
  $lng = preg_replace('/^.*_/', '', $project);

  // Get all the translators for this language.
  $query = "
    SELECT t1.uid FROM users_roles t1
    INNER JOIN role t2 ON (t2.rid = t1.rid)
    LEFT JOIN field_data_field_translation_lng t3 ON (t3.entity_id = t1.uid)
    WHERE t2.name = 'translator'
      AND t3.field_translation_lng_value = :lng";
  $uids = db_query($query, array(':lng' => $lng))->fetchCol();
  $translators = user_load_multiple($uids);

  // Notify the translators about the new term.
  $queue = DrupalQueue::get('notifications');
  $queue->createQueue();  // There is no harm in trying to recreate existing.
  foreach ($translators as $translator) {
    $notification_params = array(
      'type' => 'notify-translator-on-new-term',
      'uid' => $translator->uid,
      'username' => $translator->name,
      'recipient' => $translator->name . ' <' . $translator->mail . '>',
      'project' => $project,
      'string' => $string,
      'sguid' => $sguid,
      'author' => $GLOBALS['user']->name,
    );
    $queue->createItem((object)$notification_params);
  }
}
