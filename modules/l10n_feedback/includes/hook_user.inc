<?php
/**
 * Implements hook_user_isert().
 * It is called when a new user account is created.
 */
function l10n_feedback_user_insert(&$edit, $account, $category) {

  $db = $GLOBALS['l10n_feedback_db'];

  $args = array(
    ':umail' => $account->init,  //initial email that the user used for registration
    ':ulng' => variable_get('l10n_feedback_translation_lng'),
  );
  $select_user = "
    SELECT * FROM {l10n_feedback_users}
    WHERE umail = :umail AND ulng = :ulng
  ";
  $result = $db->query($select_user, $args);

  $args[':uid'] = $account->uid;
  $args[':name'] = $account->name;

  if ($result->rowCount() > 0) {
    l10n_feedback_user_update($edit, $account, $category);
    $update_user = "
      UPDATE {l10n_feedback_users}
      SET uid = :uid, name = :name, status = 1
      WHERE umail = :umail AND ulng = :ulng
    ";
    $db->query($update_user, $args);
  }
  else {
    $insert_user = "
      INSERT INTO {l10n_feedback_users} (umail, ulng, uid, name, status)
      VALUES (:umail, :ulng, :uid, :name, 1)
    ";
    $db->query($insert_user, $args);
  }
}


/**
 * Implements hook_user_update().
 * It is called after a user account has been updated.
 */
function l10n_feedback_user_update(&$edit, $account, $category) {

  $args = array(
    ':ulng' => variable_get('l10n_feedback_translation_lng'),
    ':uid' => $account->uid,
    ':name' => $account->name,
    ':status' => $account->status,
  );
  $update_user = "
    UPDATE {l10n_feedback_users}
    SET name = :name, status = :status
    WHERE uid = :uid AND :ulng = ulng
  ";
  $GLOBALS['l10n_feedback_db']->query($update_user, $args);
}


/**
 * Implements hook_user_cancel().
 */
function l10n_feedback_user_cancel(&$edit, $account, $category) {

  $args = array(
    ':ulng' => variable_get('l10n_feedback_translation_lng'),
    ':uid' => $account->uid,
  );
  $update_user = "
    UPDATE {l10n_feedback_users}
    SET status = 0
    WHERE uid = :uid AND :ulng = ulng
  ";
  $GLOBALS['l10n_feedback_db']->query($update_user, $args);
}


/**
 * Implements hook_user_delete().
 */
function l10n_feedback_user_delete($account) {

  $args = array(
    ':ulng' => variable_get('l10n_feedback_translation_lng'),
    ':uid' => $account->uid,
  );
  $update_user = "
    UPDATE {l10n_feedback_users}
    SET status = 0
    WHERE uid = :uid AND :ulng = ulng
  ";
  $GLOBALS['l10n_feedback_db']->query($update_user, $args);
}


/**
 * Implements hook_user_presave().
 * It is called before the user profile page is saved.
 * Store the value for 'field_data_sequential'.
 */
function l10n_feedback_user_presave(&$edit, $account, $category) {

  //dpm($edit);  dpm($account);  //debug

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
    $edit['field_data_sequential'] = serialize(null);
    return;
  }

  // get the preferred projects from the user settings
  $arr_projects = l10n_feedback_get_preferred_projects($obj_edit);

  // if there is no change on the preferred projects,
  // then there is nothing to do, just keep the existing value of 'field_data_sequential'
  $prev_string_order = l10n_feedback_get_string_order($account);
  $prev_projects = l10n_feedback_get_preferred_projects($account);
  if ( $prev_string_order=='sequential'
    and implode(';', $prev_projects) == implode(';', $arr_projects) )
    {
      return;
    }

  // for each preferred project, get the min and max location ids
  // and store them on the object $sequential
  list($where_condition, $args) = l10n_feedback_projects_to_where_condition($arr_projects);
  if ($where_condition == '') {
    $sequential = null;
  }
  else {
    $get_all_min_and_max_locations = "
      SELECT min(l.lid) AS lmin, max(l.lid) AS lmax
      FROM {l10n_feedback_locations} l
      RIGHT JOIN {l10n_feedback_templates} t ON (l.potid = t.potid)
      RIGHT JOIN {l10n_feedback_projects} p ON (t.pguid = p.pguid)
      WHERE $where_condition
      GROUP BY p.project
    ";
    $result = $GLOBALS['l10n_feedback_db']->query($get_all_min_and_max_locations, $args);
    $sequential->projects = $result->fetchAll();
    $sequential->idx = 0;
    $sequential->lid = $sequential->projects[0]->lmin;
  }

  // save the object $sequential on the field 'field_data_sequential'
  $edit['field_data_sequential'] = serialize($sequential);
}
?>