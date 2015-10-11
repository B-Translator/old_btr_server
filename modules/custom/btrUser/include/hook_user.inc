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
  _btrUser_user_set_fields($edit, $account);
}


/**
 * Get the values of the fields and put them to the attributes
 * projects, auxiliary_languages to the proper place in the structure
 * of the $user.  This is called after a user account is loaded, in
 * hook_user_load().
 */
function _btrUser_user_get_fields(&$user) {
  $lang = LANGUAGE_NONE;

  // field_translation_lng
  $user->translation_lng = 'fr';
  if (isset($user->field_translation_lng[$lang][0]['value'])) {
    $user->translation_lng = $user->field_translation_lng[$lang][0]['value'];
  }

  // field_projects
  $user->subscribed_projects = array();
  if ( isset($user->field_projects[$lang]) and is_array($user->field_projects[$lang]) ) {
    $field_projects = $user->field_projects[$lang];
    foreach ($field_projects as $project) {
      $user->subscribed_projects[] = $project['value'];
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

  // Get the projects for which the user is an admin.
  $get_managed_projects = "
    SELECT CONCAT(p.origin, '/', p.project) AS project
    FROM {btr_user_project_roles} r
    LEFT JOIN {btr_projects} p ON (p.pguid = r.pguid)
    WHERE umail = :umail AND role = :role
  ";
  $params = array(
    ':umail' => $user->init,
    ':role' => 'admin',
  );
  $user->admin_projects = btr::db_query($get_managed_projects, $params)->fetchCol();

  // Get the projects for which the user is a moderator.
  $params[':role'] = 'moderator';
  $user->moderate_projects = btr::db_query($get_managed_projects, $params)->fetchCol();
}

/**
 * Save the values of attributes projects, and auxiliary_languages to the proper
 * place in the structure of the $edit.  This is called before a user account is
 * saved, in hook_user_presave().
 */
function _btrUser_user_set_fields(&$edit, $account) {

  $lang = LANGUAGE_NONE;

  if (isset($edit['translation_lng'])) {
    $edit['field_translation_lng'][$lang][0]['value'] = $edit['translation_lng'];
  }

  if (isset($edit['subscribed_projects']) && is_array($edit['subscribed_projects'])) {
    foreach ($edit['subscribed_projects'] as $project) {
      $edit['field_projects'][$lang][]['value'] = $project;
    }
  }

  if (isset($edit['auxiliary_languages']) && is_array($edit['auxiliary_languages'])) {
    foreach ($edit['auxiliary_languages'] as $language) {
      $edit['field_auxiliary_languages'][$lang][]['value'] = $language;
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
  btr::db_delete('btr_users')
    ->condition('umail', $umail)
    ->condition(db_or()
      ->condition('ulng', $ulng)
      ->condition('ulng', $ulng_old)
    )
    ->execute();

  // Insert a new user with the given fields.
  btr::db_insert('btr_users')
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
  btr::db_update('btr_users')
    ->fields(array(
        'status' => 0,
      ))
    ->condition('umail', $umail)
    ->condition('ulng', $ulng)
    ->execute();
}
