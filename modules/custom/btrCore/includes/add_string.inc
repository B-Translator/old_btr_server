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
function btr_add_string($origin, $project, $tplname =NULL, $string, $context =NULL) {
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
  $query = "SELECT potid FROM {btr_templates}
            WHERE pguid = :pguid AND tplname = :tplname";
  $args = array(
    ':pguid' => sha1($origin . $project),
    ':tplname' => $potname,
  );
  $potid = $db->query($query, $args)->fetchField();

  // Insert a new location.
  $db->insert('btr_locations')
    ->fields(array(
        'sguid' => $sguid,
        'potid' => $potid,
      ))
    ->execute();

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
