<?php

/**
 * Add a new term to the vocabulary.
 * Return the sguid of the new term,
 * or NULL if such a term already exists.
 */
function btr_add_term($string) {
  $context = 'vocabulary';
  $sguid = sha1($string . $context);

  $db = $GLOBALS['btr_db'];

  // check whether this string already exists or not
  $query = "SELECT sguid FROM {btr_strings} WHERE sguid = :sguid";
  $args = array(':sguid' => $sguid);
  $field = $db->query($query, $args)->fetchField();
  if (!empty($field)) {
    drupal_set_message(t('This term already exists.'));
    return NULL;
  }

  // insert the new string
  $db->insert('btr_strings')
    ->fields(array(
        'string' => $string,
        'context' => $context,
        'sguid' => $sguid,
        'uid' => 1,
        'time' => date('Y-m-d H:m:s'),
        'count' => 1,
      ))
    ->execute();

  // get the template id
  $origin = 'misc';
  $project = 'vocabulary';
  $potname = 'vocabulary';
  $potid = $db->select('btr_templates', 't')
    ->fields('t', array('potid'))
    ->condition('pguid', sha1($origin . $project))
    ->condition('tplname', $potname)
    ->execute()
    ->fetchField();

  // insert a new location
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
function btr_del_term($sguid) {
  $db = $GLOBALS['btr_db'];
  $db->delete('btr_strings')->condition('sguid', $sguid)->execute();
  $db->delete('btr_locations')->condition('sguid', $sguid)->execute();
  $db->delete('btr_translations')->condition('sguid', $sguid)->execute();
}
