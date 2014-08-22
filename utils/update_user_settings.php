<?php
/**
 * Call this with:
 *     drush [@alias] php-script update_user_settings.php
 */

// disable sending notification on user update
$action_id = db_query("SELECT aid FROM {trigger_assignments} WHERE hook='user_update'")->fetchField();
db_delete('trigger_assignments')
  ->condition('hook', 'user_update')
  ->execute();

$edit = array(
  /*
  // enable feedback channels 'website' and 'email'
  'field_feedback_channels' => array(
    'und' => array(
      array('value' => 'website'),
      array('value' => 'email'),
    ),
  ),
  */
  'field_translation_lng' => array(
    'und' => array(array('value' => 'sq')),
  ),
);

$accounts = entity_load('user');
foreach ($accounts as $account) {
  if ($account->uid < 2)  continue;
  //if ($account->status != 1)  continue;
  user_save($account, $edit);
}

// re-enable sending notification on user update
db_insert('trigger_assignments')
  ->fields(array(
      'hook' => 'user_update',
      'aid' => $action_id,
    ))
  ->execute();

