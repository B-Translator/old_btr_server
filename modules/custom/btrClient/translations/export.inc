<?php
/**
 * @file
 * Export the best translations of a project into PO format.
 */

/**
 * Menu callback: translations/export
 * Export the best translations of a project into PO format.
 */
function btrClient_export() {
  return drupal_get_form('btrClient_export_form');
}


/**
 * Export form.
 */
function btrClient_export_form() {
  $form = array(
    '#prefix' => '<div class="btr-ui-filter clear-block">',
    '#suffix' => '</div>',
  );

  $form['export'] = array(
    '#type' => 'fieldset',
    '#title' => t('Export a Project'),
    '#description' => t('<p>Submit a request for exporting a project. When the request is completed you will be notified by email.</p><br/>'),
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
    '#required' => !btr_user_access('btranslator-export'),
  );

  // Those that have the export access right (usually translators)
  // can also choose an export mode different from the default one.
  if (btr_user_access('btranslator-export')) {
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
 *
 * Send the export request to the B-Translator server.
 */
function btrClient_export_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $values += array(
    'origin' => NULL,
    'project' => NULL,
    'export_mode' => NULL,
    'friends' => NULL,
  );

  $params = array(
    'origin' => check_plain($values['origin']),
    'project' => check_plain($values['project']),
    'export_mode' => check_plain($values['export_mode']),
    'friends' => check_plain($values['friends']),
  );
  $result = $GLOBALS['btr']->export_project($params);
  btrClient_display_messages($result['messages']);
}
