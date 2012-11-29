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
    '#description' => t('Submit a request for exporting a project. When the request is completed you will be notified by email. Only single projects can be exported. If you need to export many projects (for example all the projects from a certain origin), contact the site administrator.'),
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
    '#required' => TRUE,
    '#description' => t('The name of the project.'),
    '#autocomplete_path' => 'translations/autocomplete/project',
  );

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
  $algorithm = $values['algorithm'];

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
  $export_data = (object) array(
    'uid' => $user->uid,
    'origin' => $origin,
    'project' => $project,
    'algorithm' => $algorithm,
  );
  $queue->createItem($export_data);

  drupal_set_message(t("Export of '!project' is scheduled. You will be notified by email when it is done.",
      array('!project' => "$origin/$project")));
}

