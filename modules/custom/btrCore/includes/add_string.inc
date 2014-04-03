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
  if (!empty($field)) {
    return NULL;
  }

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

  // Get the template id.
  if (empty($tplname))  $tplname = $project;
  $query = "SELECT potid FROM {btr_templates}
            WHERE pguid = :pguid AND tplname = :tplname";
  $args = array(
    ':pguid' => sha1($origin . $project),
    ':tplname' => $tplname,
  );
  $potid = $db->query($query, $args)->fetchField();

  // Insert a new location.
  $db->insert('btr_locations')
    ->fields(array(
        'sguid' => $sguid,
        'potid' => $potid,
      ))
    ->execute();

  // Notify translators about the new string.
  if ($notify) {
    _btr_new_string_notification($string, $sguid);
  }

  return $sguid;
}


/**
 * Delete the term with the given id.
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
function _btr_new_string_notification($string, $sguid) {

  // Get all the users with role 'translator'.
  $query = "SELECT ur.uid FROM users_roles ur
            RIGHT JOIN role r ON (ur.rid = r.rid)
            WHERE r.name = 'translator' ";
  $uids = db_query($query)->fetchCol();
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
      'sguid' => $sguid,
      'string' => $string,
      'author' => $GLOBALS['user']->name,
    );
    $queue->createItem((object)$notification_params);
  }
}
