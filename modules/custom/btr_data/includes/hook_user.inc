<?php

/**
 * Implements hook_user_load().
 * Act on user objects when loaded from the database.
 */
function btr_data_user_load($users) {
  foreach($users as $user) {
    _btr_data_user_get_fields($user);
  }
}


/**
 * Implements hook_user_isert().
 * It is called when a new user account is created.
 */
function btr_data_user_insert(&$edit, $account, $category) {
  _btr_user_insert(
    $umail = $account->init,  // initial email that the user used for registration
    $ulng = $account->field_translation_lng['und'][0]['value'],
    $uid = $account->uid,
    $name = $account->name,
    $status = $account->status
  );
}


/**
 * Implements hook_user_update().
 * It is called after a user account has been updated.
 */
function btr_data_user_update(&$edit, $account, $category) {
  _btr_user_update(
    $ulng = $account->field_translation_lng['und'][0]['value'],
    $uid = $account->uid,
    $name = $account->name,
    $status = $account->status
  );
}


/**
 * Implements hook_user_cancel().
 */
function btr_data_user_cancel(&$edit, $account, $category) {
  _btr_user_disable(
    $ulng = $account->field_translation_lng['und'][0]['value'],
    $uid = $account->uid
  );
}


/**
 * Implements hook_user_delete().
 */
function btr_data_user_delete($account) {
  _btr_user_disable(
    $ulng = $account->field_translation_lng['und'][0]['value'],
    $uid = $account->uid
  );
}


/**
 * Implements hook_user_presave().
 * It is called before the user profile page is saved.
 */
function btr_data_user_presave(&$edit, $account, $category) {
  _btr_data_user_set_data_sequential($edit, $account);
  _btr_data_user_set_fields($edit, $account);
}


/**
 * Build an index object that is needed for visiting strings
 * sequentially and set it to $edit['data_sequential'].
 */
function _btr_data_user_set_data_sequential(&$edit, $account) {

  // if skip_presave is defined, then user data is being saved
  // from the code, not from the profile interface
  if (isset($edit['skip_presave'])) {
    unset($edit['skip_presave']);
    return;
  }

  $lang = LANGUAGE_NONE;
  $obj_edit = (object)$edit;
  _btr_data_user_get_fields($obj_edit);
  $account = user_load($account->uid);

  // if string-order is random, no need for 'field_data_sequential'
  if ($obj_edit->string_order == 'random') {
    $edit['data_sequential'] = NULL;
    return;
  }

  // if there is no change on the preferred projects,
  // then there is nothing to do, just keep the existing value of 'field_data_sequential'
  $prev_projects = implode(';', $account->preferred_projects);
  $new_projects = implode(';', $obj_edit->preferred_projects);
  if ($account->string_order=='sequential' and $prev_projects==$new_projects) {
    return;
  }

  // For each preferred project, get the min and max location ids
  // and store them in the object $sequential.
  // The data in this object makes it possible for a user to visit
  // the strings of his preferred projects sequentially (in the same
  // order that they appear on the PO file), rather than randomly.
  $arr_projects = $obj_edit->preferred_projects;
  list($where_condition, $args) = _btr_projects_to_where_condition($arr_projects);
  if ($where_condition == '') {
    $sequential = NULL;
  }
  else {
    $get_all_min_and_max_locations = "
      SELECT min(l.lid) AS lmin, max(l.lid) AS lmax
      FROM {btr_locations} l
      RIGHT JOIN {btr_templates} t ON (l.potid = t.potid)
      RIGHT JOIN {btr_projects} p ON (t.pguid = p.pguid)
      WHERE $where_condition
      GROUP BY p.project
    ";
    $result = $GLOBALS['btr_db']->query($get_all_min_and_max_locations, $args);
    $sequential->projects = $result->fetchAll();
    $sequential->idx = 0;
    $sequential->lid = $sequential->projects[0]->lmin;
  }
  $edit['data_sequential'] = $sequential;
}


/**
 * Get the values of the fields and put them
 * to the attributes string_order,
 * preferred_projects, data_sequential,
 * auxiliary_languages, translations_per_day
 * and feedback_channels to the proper place
 * in the structure of the $user.
 * This is called after a user account is loaded,
 * in hook_user_load().
 */
function _btr_data_user_get_fields(&$user) {
  $lang = LANGUAGE_NONE;

  // field_translation_lng
  $user->translation_lng = variable_get('btr_translation_lng', 'fr');
  if (isset($user->field_translation_lng[$lang][0]['value'])) {
    $user->translation_lng = $user->field_translation_lng[$lang][0]['value'];
  }

  // field_order_of_strings
  $user->string_order = 'random';
  if (isset($user->field_order_of_strings[$lang][0]['value'])) {
    $user->string_order = $user->field_order_of_strings[$lang][0]['value'];
  }

  // field_preferred_projects
  $user->preferred_projects = array();
  if ( isset($user->field_preferred_projects[$lang]) and is_array($user->field_preferred_projects[$lang]) ) {
    $field_preferred_projects = $user->field_preferred_projects[$lang];
    foreach ($field_preferred_projects as $project) {
      $user->preferred_projects[] = $project['value'];
    }
  }

  // field_auxiliary_languages
  $user->auxiliary_languages = array();
  if ( isset($user->field_auxiliary_languages[$lang]) and is_array($user->field_auxiliary_languages[$lang]) ) {
    $field_auxiliary_languages = $user->field_auxiliary_languages[$lang];
    foreach ($field_auxiliary_languages as $language) {
      $user->auxiliary_languages[] = $language['value'];
    }
  }

  // field_data_sequential
  $user->data_sequential = NULL;
  if (isset($user->field_data_sequential[$lang][0]['value'])) {
    $user->data_sequential = unserialize($user->field_data_sequential[$lang][0]['value']);
  }

  // field_translations_per_day
  $user->translations_per_day = 1;
  if (isset($user->field_translations_per_day[$lang][0]['value'])) {
    $user->translations_per_day = $user->field_translations_per_day[$lang][0]['value'];
  }

  // field_feedback_channels
  $user->feedback_channels = array();
  if ( isset($user->field_feedback_channels[$lang]) and is_array($user->field_feedback_channels[$lang]) ) {
    $field_feedback_channels = $user->field_feedback_channels[$lang];
    foreach ($field_feedback_channels as $channel) {
      $user->feedback_channels[] = $channel['value'];
    }
  }
}

/**
 * Save the values of attributes string_order,
 * preferred_projects, data_sequential,
 * auxiliary_languages, translations_per_day
 * and feedback_channels to the proper place
 * in the structure of the $edit.
 * This is called before a user account is saved,
 * in hook_user_presave().
 */
function _btr_data_user_set_fields(&$edit, $account) {

  $lang = LANGUAGE_NONE;

  if (isset($edit['translation_lng'])) {
    $edit['field_translation_lng'][$lang][0]['value'] = $edit['translation_lng'];
  }

  if (isset($edit['string_order'])) {
    $edit['field_order_of_strings'][$lang][0]['value'] = $edit['string_order'];
  }

  if (isset($edit['preferred_projects']) && is_array($edit['preferred_projects'])) {
    foreach ($edit['preferred_projects'] as $project) {
      $edit['field_preferred_projects'][$lang][]['value'] = $project;
    }
  }

  if (isset($edit['auxiliary_languages']) && is_array($edit['auxiliary_languages'])) {
    foreach ($edit['auxiliary_languages'] as $language) {
      $edit['field_auxiliary_languages'][$lang][]['value'] = $language;
    }
  }

  if (isset($edit['data_sequential'])) {
    $edit['field_data_sequential'][$lang][0]['value'] = serialize($edit['data_sequential']);
  }

  if (isset($edit['translations_per_day'])) {
    $edit['field_translations_per_day'][$lang][0]['value'] = $edit['translations_per_day'];
  }

  if (isset($edit['feedback_channels']) && is_array($edit['feedback_channels'])) {
    foreach ($edit['feedback_channels'] as $channel) {
      $edit['field_feedback_channels'][$lang][]['value'] = $channel;
    }
  }
}


/**
 * It is called when a new user account is created.
 */
function _btr_user_insert($umail, $ulng, $uid, $name, $status) {

  $db = $GLOBALS['btr_db'];

  $args = array(
    ':umail' => $umail,
    ':ulng' => $ulng,
  );
  $select_user = "
    SELECT * FROM {btr_users}
    WHERE umail = :umail AND ulng = :ulng
  ";
  $result = $db->query($select_user, $args);

  $args[':uid'] = $uid;
  $args[':name'] = $name;

  if ($result->rowCount() > 0) {
    _btr_user_update($ulng, $uid, $name, $status);
    $update_user = "
      UPDATE {btr_users}
      SET uid = :uid, name = :name, status = 1
      WHERE umail = :umail AND ulng = :ulng
    ";
    $db->query($update_user, $args);
  }
  else {
    $insert_user = "
      INSERT INTO {btr_users} (umail, ulng, uid, name, status)
      VALUES (:umail, :ulng, :uid, :name, 1)
    ";
    $db->query($insert_user, $args);
  }
}


/**
 * It is called after a user account has been updated.
 */
function _btr_user_update($ulng, $uid, $name, $status) {
  $args = array(
    ':ulng' => $ulng,
    ':uid' => $uid,
    ':name' => $name,
    ':status' => $status,
  );
  $update_user = "
    UPDATE {btr_users}
    SET name = :name, status = :status
    WHERE uid = :uid AND :ulng = ulng
  ";
  $GLOBALS['btr_db']->query($update_user, $args);
}


/**
 * It is called when a user is cancelled or deleted.
 */
function _btr_user_disable($ulng, $uid) {
  $args = array(':ulng' => $ulng, ':uid' => $uid);
  $update_user = "
    UPDATE {btr_users}
    SET status = 0
    WHERE uid = :uid AND :ulng = ulng
  ";
  $GLOBALS['btr_db']->query($update_user, $args);
}
