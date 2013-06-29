<?php
/**
 * Call this with:
 *     drush [@alias] php-script update_user_settings.php
 */

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