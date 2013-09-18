<?php
/**
 * @file
 * Export the most voted translations of a project into a PO file.
 */

/**
 * Menu callback: translations/export
 * Export the most voted translations of a project into a PO file.
 */
function l10n_feedback_export() {
  return drupal_get_form('l10n_feedback_export_form');
}


/**
 * Export form.
 */
function l10n_feedback_export_form() {
  $form = array(
    '#prefix' => '<div class="l10n-feedback-filter clear-block">',
    '#suffix' => '</div>',
  );

  $form['export'] = array(
    '#type' => 'fieldset',
    '#title' => t('Export a Project'),
    '#description' => t('Submit a request for exporting a project. When the request is completed you will be notified by email.'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['export']['origin'] = array(
    '#type' => 'textfield',
    '#title' => t('Origin'),
    '#required' => TRUE,
    '#description' => t('The origin of the project.'),
    '#autocomplete_path' => 'translations/autocomplete/origin',
  );

  $form['export']['project'] = array(
    '#type' => 'textfield',
    '#title' => t('Project'),
    '#description' => t('The name of the project.'),
    '#autocomplete_path' => 'translations/autocomplete/project',
    // Those that have the export access right (usually translators)
    // can also export all the projects from the same origin.
    // Contributors can export only a single project at a time.
    '#required' => !user_access('btranslator-export'),
  );

  // Those that have the export access right (usually translators)
  // can also choose an export mode different from the default one.
  if (user_access('btranslator-export')) {
    $form['export']['export_mode'] = array(
      '#type' => 'select',
      '#title' => t('Export Mode'),
      '#description' => t('The export mode that should be used.'),
      '#options' => array(
        'most_voted' => t('Export the most voted translations'),
        'preferred_by_me' => t('Prefer translations voted by me'),
        'preferred_by_my_friends' => t('Prefer translations voted by my friends'),
      ),
      '#default_value' => 'most_voted',
    );

    $form['export']['friends'] = array(
      '#type' => 'textarea',
      '#title' => t('List of Friends'),
      '#description' => t('Enter usernames of your friends, separated by comma.'),
      '#states' => array(
        'visible' => array(
          ':input[name="export_mode"]' => array('value' => 'preferred_by_my_friends'),
        ),
      ),
    );
  }

  $form['buttons'] = array(
    //'#prefix' => '<div class="export-submit">',
    //'#suffix' => '</div>',
  );
  $form['buttons']['submit'] = array(
    '#value' => t('Export'),
    '#type' => 'submit',
  );

  return $form;
}


/**
 * Submission handler for export form.
 */
function l10n_feedback_export_form_submit($form, &$form_state) {

  $values = $form_state['values'];
  //dpm($values);  //debug
  $origin = $values['origin'];
  $project = $values['project'];
  $origin = check_plain($origin);
  $project = check_plain($project);
  if (empty($project)) {
    $project = 'all';
  }

  $account = user_load($GLOBALS['user']->uid);
  $arr_voters[] = $account->init;

  $export_mode = isset($values['export_mode']) ? $values['export_mode'] : '';
  if ($export_mode == 'preferred_by_my_friends') {
    $friends = isset($values['friends']) ? $values['friends'] : '';
    $arr_friends = preg_split('/\s*,\s*/', trim($friends));
    foreach ($arr_friends as $username) {
      $account = user_load_by_name($username);
      $arr_voters[] = $account->init;
    }
  }

  $params = array(
    'uid' => $GLOBALS['user']->uid,
    'origin' => $origin,
    'project' => $project,
    'export_mode' => $export_mode,
    'voters' => implode(',', $arr_voters),
  );
  btr_queue('export_project', array($params));

  drupal_set_message(t("Export of '!project' is scheduled. You will be notified by email when it is done.",
      array('!project' => "$origin/$project")));

  $notify_admin = variable_get('btr_export_notify_admin', TRUE);
  if ($notify_admin) {
    $params['type'] = 'notify-admin-on-export-request';
    $params['recipient'] = user_load(1)->mail;
    btr_queue_notifications(array($params));
  }
}

/**
 * Data validation for export form.
 */
function l10n_feedback_export_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  $origin = $values['origin'];
  $project = $values['project'];
  $origin = check_plain($origin);
  $project = check_plain($project);

  if (empty($project)) {
    $query = "SELECT DISTINCT origin FROM {btr_projects} WHERE BINARY origin = :origin";
    $params = array(':origin' => $origin);
  }
  else {
    $query = "SELECT project FROM {btr_projects} WHERE BINARY origin = :origin AND BINARY project = :project";
    $params = array(':origin' => $origin, ':project' => $project);
  }

  $result = btr_query($query, $params)->fetchField();
  if (!$result) {
    form_set_error('', t("The project '!project' does not exist.", array('!project' => "$origin/$project")));
  }

  $export_mode = isset($values['export_mode']) ? $values['export_mode'] : '';
  if ($export_mode == 'preferred_by_my_friends') {
    $friends = isset($values['friends']) ? $values['friends'] : '';
    $arr_friends = preg_split('/\s*,\s*/', trim($friends));
    foreach ($arr_friends as $username) {
      if (!user_load_by_name($username)) {
        form_set_error('', t("The user '!username' does not exist.", array('!username' => $username)));
      }
    }
    $form_state['values']['friends'] = implode(',', $arr_friends);
  }
}
