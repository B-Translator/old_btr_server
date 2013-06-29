<?php
/**
 * Call this with:
 *     drush [@alias] php-script update_user_settings.php
 */

// disable sending notification on user update
$action_id = db_query("SELECT aid FROM {trigger_assignments} WHERE hook='user_update'")->fetchField();
db_query("DELETE FROM {trigger_assignments} WHERE hook='user_update'");

$edit = array(
  // enable feedback channels 'website' and 'email'
  'field_feedback_channels' => array(
    'und' => array(
      array('value' => 'website'),
      array('value' => 'email'),
    ),
  ),
);

$accounts = entity_load('user');
foreach ($accounts as $account) {
  if ($account->uid < 2)  continue;
  //if ($account->status != 1)  continue;
  user_save($account, $edit);
}

// re-enable sending notification on user update
db_query("INSERT INTO {trigger_assignments} (hook, aid) VALUES ('user_update', $action_id)");
