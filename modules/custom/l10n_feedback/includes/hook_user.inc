<?php
/**
 * @file
 * hook_user functions
 */

/**
 * Implements hook_user_isert().
 * It is called when a new user account is created.
 */
function l10n_feedback_user_insert(&$edit, $account, $category) {
  btr_user_insert(
    $umail = $account->init,  // initial email that the user used for registration
    $ulng = variable_get('btr_translation_lng', 'fr'),
    $uid = $account->uid,
    $name = $account->name,
    $status = $account->status
  );
}


/**
 * Implements hook_user_update().
 * It is called after a user account has been updated.
 */
function l10n_feedback_user_update(&$edit, $account, $category) {
  btr_user_update(
    $ulng = variable_get('btr_translation_lng', 'fr'),
    $uid = $account->uid,
    $name = $account->name,
    $status = $account->status
  );
}


/**
 * Implements hook_user_cancel().
 */
function l10n_feedback_user_cancel(&$edit, $account, $category) {
  btr_user_delete(
    $ulng = variable_get('btr_translation_lng', 'fr'),
    $uid = $account->uid
  );
}


/**
 * Implements hook_user_delete().
 */
function l10n_feedback_user_delete($account) {
  btr_user_delete(
    $ulng = variable_get('btr_translation_lng', 'fr'),
    $uid = $account->uid
  );
}


/**
 * Implements hook_user_presave().
 * It is called before the user profile page is saved.
 * Store the value for 'field_data_sequential'.
 */
function l10n_feedback_user_presave(&$edit, $account, $category) {

  // if skip_presave is defined, then user data is being saved
  // from the code, not from the profile interface
  if (isset($edit['skip_presave'])) {
    unset($edit['skip_presave']);
    return;
  }

  $lang = 'und';
  $obj_edit = (object)$edit;

  // get the string-order (random|sequential)
  $string_order = l10n_feedback_get_string_order($obj_edit);

  // if string-order is random, no need for 'field_data_sequential'
  if ($string_order == 'random') {
    $edit['field_data_sequential'] = serialize(NULL);
    return;
  }

  // get the preferred projects from the user settings
  $arr_projects = l10n_feedback_get_preferred_projects($obj_edit);

  // if there is no change on the preferred projects,
  // then there is nothing to do, just keep the existing value of 'field_data_sequential'
  $prev_string_order = l10n_feedback_get_string_order($account);
  $prev_projects = l10n_feedback_get_preferred_projects($account);
  if ( $prev_string_order=='sequential'
    and implode(';', $prev_projects) == implode(';', $arr_projects) ) {

    return;
  }

  // for each preferred project, get the min and max location ids
  // and store them on the object $sequential
  $sequential = btr_get_sequential_data($arr_projects);

  // save the object $sequential on the field 'field_data_sequential'
  $edit['field_data_sequential'][$lang][0]['value'] = serialize($sequential);
}
