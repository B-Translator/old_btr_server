<?php
/**
 * @file
 * Alter user_profile_form, user_register_form, etc.
 */

/**
 * Implements hook_form_FORM_ID_alter() for user_profile_form.
 */
function btrUser_form_user_profile_form_alter(&$form, &$form_state, $form_id) {
  // Replace 'field_projects' with a list of subscribed projects.
  $arr_projects = field_get_items('user', $form['#user'], 'field_projects');
  if ($arr_projects) {
    $lng = $form['#user']->translation_lng;
    $base_url = btr::utils_get_client_url($lng);
    $items = [];
    foreach ($arr_projects as $proj) {
      $project = $proj['value'];
      $url = "$base_url/btr/project/$project/$lng/dashboard";
      $items[] = "<a href='$url' class='btn btn-default' target='_blank'>$project/$lng</a>";
    }
    $form['field_projects'] = [
      '#type'  => 'fieldset',
      '#title' => t('Subscribed Projects'),
      'subscribed_projects' => [
        '#markup' => implode(' ', $items),
      ],
    ];
  }
  else {
    $form['field_projects']['#access'] = user_access('btranslator-admin');
  }

  // Hide 'field_auxiliary_languages', it is not useful yet.
  $form['field_auxiliary_languages']['#access'] = FALSE;

  // Add fields for admin_projects and moderate_projects.
  $form['admin'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Fields that can be seen and modified only by an administrator'),
    '#access' => in_array('administrator', $GLOBALS['user']->roles),
    '#weight' => -100,   // display it on the top
  );
  $form['admin']['admin_projects'] = array(
    '#type' => 'textarea',
    '#title' => t('The list of projects that user can administrate'),
    '#description' => t("Set the projects that the user can admin. Enter each project on a separate line, in the form <em>origin/project</em>."),
    '#default_value' => implode("\n", $form_state['user']->admin_projects),
  );
  $form['admin']['moderate_projects'] = array(
    '#type' => 'textarea',
    '#title' => t('The list of projects that user can moderate'),
    '#description' => t("Set the projects that the user can moderate. Enter each project on a separate line, in the form <em>origin/project</em>."),
    '#default_value' => implode("\n", $form_state['user']->moderate_projects),
  );

  array_unshift($form['#submit'], '_btrUser_form_user_profile_submit');
}

/**
 * Called before form_user_profile submit
 * in order to save the extra form fields.
 */
function _btrUser_form_user_profile_submit($form, &$form_state) {

  function _btrUser_update_user_project_roles($umail, $ulng, $projects, $role) {
    // Delete any existings records.
    btr::db_delete('btr_user_project_roles')
      ->condition('umail', $umail)
      ->condition('ulng', $ulng)
      ->condition('role', $role)
      ->execute();

    // Get the projects as an array.
    $arr_projects = array();
    $lines = preg_split('#\r\n|\r|\n#', $projects);
    foreach ($lines as $line) {
      $line = trim($line);
      if ($line == '')  continue;
      $arr_projects[] = $line;
    }
    if (!$arr_projects)  return;

    // Get project pguid-s and for each of them insert a record.
    list($condition, $args) = btr::utils_projects_to_where_condition($arr_projects);
    $query = "SELECT pguid FROM {btr_projects} WHERE $condition";
    $arr_pguid = btr::db_query($query, $args)->fetchCol();
    foreach ($arr_pguid as $pguid) {
      btr::db_insert('btr_user_project_roles')
        ->fields(array(
            'umail' => $umail,
            'ulng' => $ulng,
            'pguid' => $pguid,
            'role' => $role,
          ))
        ->execute();
    }

    // If a project is vocabulary, update its recipients of the contact form.
    foreach ($arr_projects as $project) {
      if (strpos($project, 'vocabulary/') !== FALSE) {
        $project = str_replace('vocabulary/', '', $project);
        $q = 'SELECT recipients FROM {contact} WHERE category = :project';
        $recipients = db_query($q, array(':project' => $project))->fetchField();
        $arr_recipients = explode(',', $recipients);
        if (!in_array($umail, $arr_recipients)) $arr_recipients[] = $umail;
        $arr_recipients = array_diff($arr_recipients, array(variable_get('site_mail')));
        db_update('contact')
          ->fields(array(
              'recipients' => implode(',', $arr_recipients),
            ))
          ->condition('category', $project)
          ->execute();
      }
    }
  }

  if (in_array('administrator', $GLOBALS['user']->roles)) {
    $umail = $form_state['user']->init;
    $ulng = $form_state['user']->translation_lng;
    if (isset($form_state['values']['admin_projects'])) {
      $projects = $form_state['values']['admin_projects'];
      _btrUser_update_user_project_roles($umail, $ulng, $projects, 'admin');
    }
    if (isset($form_state['values']['moderate_projects'])) {
      $projects = $form_state['values']['moderate_projects'];
      _btrUser_update_user_project_roles($umail, $ulng, $projects, 'moderator');
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for user_register_form.
 */
function btrUser_form_user_register_form_alter(&$form, &$form_state, $form_id) {
  // Hide 'field_projects', it can be modified with
  // the buttons subscribe/unsubscribe from project pages.
  $form['field_projects']['#access'] = FALSE;

  // Hide 'field_auxiliary_languages', it is not useful yet.
  $form['field_auxiliary_languages']['#access'] = FALSE;

  // Hide the language field if the language is set in the url.
  if (isset($_GET['lng'])) {
      $form['field_translation_lng']['#access'] = FALSE;
  }

  // Register a validation callback function,
  // where we can set the values for language and projects.
  $form['#validate'][] = '_btrUser_user_register_validate';
}

/**
 * Validation function for user_register_form.
 */
function _btrUser_user_register_validate($form, &$form_state) {
  $values = &$form_state['values'];

  // Set the value for the language field.
  if (isset($_GET['lng'])) {
      $values['field_translation_lng']['und'][0]['value'] = $_GET['lng'];
  }

  // Set the value for the projects.
  if (isset($_GET['proj'])) {
    $values['field_projects']['und'][0]['value'] = $_GET['proj'];
  }
}
