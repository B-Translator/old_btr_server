<?php
/**
 * Uncheck the email option on the profile of each user,
 * so that cron does not send string review emails.
 *
 * Can be executed like this:
 *     drush [@alias] php-script disable-email-option.php
 */

// disable sending notification on user update
$action_id = db_query("SELECT aid FROM {trigger_assignments} WHERE hook='user_update'")->fetchField();
db_delete('trigger_assignments')->condition('hook', 'user_update')->execute();

// process each account
$accounts = entity_load('user');
foreach ($accounts as $account) {
  if ($account->uid < 2)  continue;
  //if ($account->status != 1)  continue;

  $field_arr = $account->field_feedback_channels['und'];
  $new_field_arr = array();
  if (is_array($field_arr)) {
    foreach ($field_arr as $item) {
      if ($item['value'] != 'email') {
        $new_field_arr[] = $item;
      }
    }
  }

  $edit = array(
    'field_feedback_channels' => array('und' => $new_field_arr),
  );
  user_save($account, $edit);
}

// re-enable sending notification on user update
db_insert('trigger_assignments')->fields(array(
    'hook' => 'user_update',
    'aid' => $action_id,
  )) ->execute();
