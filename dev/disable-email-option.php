<?php
/**
 * Uncheck the email option on the profile of each user,
 * so that cron does not send string review emails.
 *
 * Can be executed like this:
 *     drush [@alias] php-script disable-email-option.php
 */

$accounts = entity_load('user');
foreach ($accounts as $account) {
  if ($account->uid < 2)  continue;
  //if ($account->status != 1)  continue;

  $field_arr = $account->field_feedback_channels['und'];
  $feedback_channels = array();
  if (is_array($field_arr)) {
    foreach ($field_arr as $item) {
      $feedback_channels[] = $item['value'];
    }
  }

  $new_field_arr = array();
  foreach ($field_arr as $item) {
    if ($item == 'email')  continue;
    $new_field_arr[] = array('value' => $item);
  }
  $edit = array(
    'field_feedback_channels' => array('und' => $new_field_array()),
  );

  user_save($account, $edit);
}