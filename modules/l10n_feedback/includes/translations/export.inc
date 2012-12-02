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
  // can also choose an export algorithm different from the default one.
  if (user_access('btranslator-export')) {
    $form['export']['algorithm'] = array(
      '#type' => 'select',
      '#title' => t('Algorithm'),
      '#description' => t('The algorithm that should be used for export.'),
      '#options' => array(
        'most_voted' => t('Most voted'),
        'my_preferred' => t('My vote takes precedence')
      ),
      '#default_value' => 'most_voted',
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
  if (empty($project)) {
    $project = 'all';
  }
  $algorithm = isset($values['algorithm']) ? $values['algorithm'] : '';

  $origin = check_plain($origin);
  $project = check_plain($project);
  $algorithm = check_plain($algorithm);

  if ($algorithm == 'my_preferred') {
    drupal_set_message(t("Export algorithm '!algorithm' has not been implemented yet!",
        array('!algorithm' => t('My vote takes precedence'))), 'warning');
  }

  $queue = DrupalQueue::get('export_project');
  $queue->createQueue();  // There is no harm in trying to recreate existing.
  global $user;
  $params = array(
    'uid' => $user->uid,
    'origin' => $origin,
    'project' => $project,
    'algorithm' => $algorithm,
  );
  $queue->createItem((object)$params);

  drupal_set_message(t("Export of '!project' is scheduled. You will be notified by email when it is done.",
      array('!project' => "$origin/$project")));

  $notify_admin = variable_get('l10n_feedback_export_notify_admin', TRUE);
  if ($notify_admin) {
    $queue = DrupalQueue::get('notifications');
    $params['type'] = 'notify-admin-on-export-request';
    $params['recipient'] = user_load(1)->mail;
    $queue->createItem((object)$params);
  }
}

/**
 * Data validation for export form.
 */
function l10n_feedback_export_form_validate($form, &$form_state) {
  $origin = $form_state['values']['origin'];
  $project = $form_state['values']['project'];
  $origin = check_plain($origin);
  $project = check_plain($project);

  if (empty($project)) {
    $query = "SELECT DISTINCT origin FROM {l10n_feedback_projects} WHERE origin = :origin";
    $params = array(':origin' => $origin);
  }
  else {
    $query = "SELECT project FROM {l10n_feedback_projects} WHERE origin = :origin AND project = :project";
    $params = array(':origin' => $origin, ':project' => $project);
  }

  $db = $GLOBALS['l10n_feedback_db'];
  $result = $db->query($query, $params)->fetchField();
  if (!$result) {
    form_set_error('', t("The project '!project' does not exist.", array('!project' => "$origin/$project")));
  }
}

/**
 * The callback function for the menu 'translations/exports'.
 * The URL is of the form 'translations/exports/filename.tgz'
 * where the filename is passed as a parameter to the function.
 */
function l10n_feedback_get_exported_file($filename =NULL) {

  $filename = check_plain($filename);
  if (empty($filename) || !file_exists($filename)) {
    drupal_set_message(t("Export file '!filename' does not exist!",
			 array('!filename' => $filename)), 'error');
    drupal_goto("translations");
    return;
  }

  // Get the full path of the export file.
  $export_path = variable_get('l10n_feedback_export_path', '/var/www/exports');
  $export_file = $export_path . '/' . $filename;

  // Send the headers.
  header('Content-Type: application/octet-stream');
  header('Content-Disposition: attachment; filename="' . $filename . '"');
  header('Content-Transfer-Encoding: binary');
  header("Content-Length: " . filesize($export_file));

  // Open the file in a binary mode and dump it to the browser.
  $fp = fopen($export_file, 'rb');
  fpassthru($fp);

  // Stop execution.
  exit(0);
}
