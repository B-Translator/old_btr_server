<?php
/**
 * @file
 * Add hooks for user_load, user_insert, user_update, user_cancel, user_delete
 * and user_presave.
 */

/**
 * Implements hook_user_load().
 * Act on user objects when loaded from the database.
 */
function btrUser_user_load($users) {
  foreach($users as $user) {
    _btrUser_user_get_fields($user);
  }
}


/**
 * Implements hook_user_isert().
 * It is called when a new user account is created.
 */
function btrUser_user_insert(&$edit, $account, $category) {
  _btrUser_user_get_fields($account);
  _btr_user_update(
    $umail = $account->init,  // initial email that the user used for registration
    $ulng = $account->translation_lng,
    $ulng_old = 'und',  // undefined
    $uid = $account->uid,
    $name = $account->name,
    $status = 1
  );
}


/**
 * Implements hook_user_update().
 * It is called after a user account has been updated.
 */
function btrUser_user_update(&$edit, $account, $category) {
  _btrUser_user_get_fields($account);
  _btr_user_update(
    $umail = $account->init,
    $ulng = $account->translation_lng,
    $ulng_old = $account->original->translation_lng,
    $uid = $account->uid,
    $name = $account->name,
    $status = $account->status
  );
}


/**
 * Implements hook_user_cancel().
 */
function btrUser_user_cancel($edit, $account, $category) {
  _btrUser_user_get_fields($account);
  _btr_user_disable(
    $umail = $account->init,
    $ulng = $account->translation_lng
  );
}


/**
 * Implements hook_user_delete().
 */
function btrUser_user_delete($account) {
  _btrUser_user_get_fields($account);
  _btr_user_disable(
    $umail = $account->init,
    $ulng = $account->translation_lng
  );
}


/**
 * Implements hook_user_presave().
 * It is called before the user profile page is saved.
 */
function btrUser_user_presave(&$edit, $account, $category) {
  _btrUser_user_set_data_sequential($edit, $account);
  _btrUser_user_set_fields($edit, $account);
}


/**
 * Build an index object that is needed for visiting strings
 * sequentially and set it to $edit['data_sequential'].
 */
function _btrUser_user_set_data_sequential(&$edit, $account) {

  // if skip_presave is defined, then user data is being saved
  // from the code, not from the profile interface
  if (isset($edit['skip_presave'])) {
    unset($edit['skip_presave']);
    return;
  }

  $lang = LANGUAGE_NONE;
  $obj_edit = (object)$edit;
  _btrUser_user_get_fields($obj_edit);
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
  list($where_condition, $args) = btr::utils_projects_to_where_condition($arr_projects);
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
    $result = btr_query($get_all_min_and_max_locations, $args);
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
function _btrUser_user_get_fields(&$user) {
  $lang = LANGUAGE_NONE;

  // field_translation_lng
  $user->translation_lng = 'fr';
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

  // Get the projects for which the user is an admin.
  $get_managed_projects = "
    SELECT CONCAT(p.origin, '/', p.project) AS project
    FROM {btr_user_project_roles} r
    LEFT JOIN {btr_projects} p ON (p.pguid = r.pguid)
    WHERE umail = :umail AND ulng = :ulng AND role = :role
  ";
  $params = array(
    ':umail' => $user->init,
    ':ulng' => $user->translation_lng,
    ':role' => 'admin',
  );
  $user->admin_projects = btr_query($get_managed_projects, $params)->fetchCol();

  // Get the projects for which the user is a moderator.
  $params[':role'] = 'moderator';
  $user->moderate_projects = btr_query($get_managed_projects, $params)->fetchCol();
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
function _btrUser_user_set_fields(&$edit, $account) {

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
 * It is called when a new user account is created,
 * or after a user account has been updated.
 *
 * We want to make sure that there is only one record
 * with the same (umail, ulng), so we delete first any
 * existing record like that, and then insert a new one.
 */
function _btr_user_update($umail, $ulng, $ulng_old, $uid, $name, $status) {
  // Delete first any existing user which has the same umail and ulng.
  btr_delete('btr_users')
    ->condition('umail', $umail)
    ->condition(db_or()
      ->condition('ulng', $ulng)
      ->condition('ulng', $ulng_old)
    )
    ->execute();

  // Insert a new user with the given fields.
  btr_insert('btr_users')
    ->fields(array(
        'umail' => $umail,
        'ulng' => $ulng,
        'uid' => $uid,
        'name' => $name,
        'status' => $status,
      ))
    ->execute();
}


/**
 * It is called when a user is cancelled or deleted.
 */
function _btr_user_disable($umail, $ulng) {
  btr_update('btr_users')
    ->fields(array(
        'status' => 0,
      ))
    ->condition('umail', $umail)
    ->condition('ulng', $ulng)
    ->execute();
}
