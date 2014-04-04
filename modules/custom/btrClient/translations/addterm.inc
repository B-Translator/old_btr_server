<?php
/**
 * @file
 * Add new terms in vocabulary.
 */

/**
 * Menu callback: translations/addterm
 * Add a new term on a vocabulary.
 */
function btrClient_addterm() {
  $output[] = drupal_get_form('btrClient_addterm_form');
  if (btr_user_access('btranslator-admin')) {
    $output[] = drupal_get_form('btrClient_delterm_form');
  }
  return $output;
}

/**
 * Form: addterm
 */
function btrClient_addterm_form() {
  // get vocabulary projects
  $lng = variable_get('btrClient_translation_lng', 'fr');
  $btr_server = variable_get('btrClient_server', NULL);
  if (empty($btr_server)) {
    $projects = array("ICT_$lng" => "ICT_$lng");
  }
  else {
    $url = "$btr_server/translations/project/list/vocabulary/*_$lng/json";
    $output = drupal_http_request($url);
    $arr_projects = json_decode($output->data, TRUE);
    $projects = array();
    foreach ($arr_projects as $item) {
      list($origin, $project) = preg_split('#/#', $item, 2);
      $projects += array($project => $project);
    }
  }
  if (empty($projects)) {
    $projects = array('ICT_sq' => 'ICT_sq');
  }
  $first_project = current(array_keys($projects));

  $form = array(
    '#prefix' => '<div class="btr-ui-filter clear-block">',
    '#suffix' => '</div>',
  );

  $form['addterm'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add a New Term'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['addterm']['project'] = array(
    '#type' => 'select',
    '#title' => t('Project'),
    '#options' => $projects,
    '#default_value' => $first_project,
    '#required' => TRUE,
  );

  $form['addterm']['newterm'] = array(
    '#type' => 'textfield',
    '#title' => t('New Term'),
    '#required' => TRUE,
  );

  $form['addterm']['buttons'] = array(
    //'#prefix' => '<div class="export-submit">',
    //'#suffix' => '</div>',
  );
  $form['addterm']['buttons']['submit'] = array(
    '#value' => t('Add'),
    '#type' => 'submit',
  );

  return $form;
}

/**
 * Submission handler for addterm form.
 */
function btrClient_addterm_form_submit($form, &$form_state) {
  $project = check_plain(trim($form_state['values']['project']));
  $string = check_plain(trim($form_state['values']['newterm']));

  $result = $GLOBALS['btr']->add_string(array(
              'origin' => 'vocabulary',
              'project' => $project,
              'tplname' => $project,
              'string' => $string,
              'context' => 'vocabulary',
              'notify' => TRUE,
            ));
  $sguid = $result['sguid'];

  if (empty($sguid)) {
    drupal_set_message(t('This term already exists.'));
    return;
  }

  // redirect to translating the term
  $lng = variable_get('btrClient_translation_lng', 'fr');
  drupal_goto("translations/$lng/$sguid");
}

/**
 * Form: delterm
 */
function btrClient_delterm_form() {
  $form = array(
    '#prefix' => '<div class="btr-ui-filter clear-block">',
    '#suffix' => '</div>',
  );

  $form['delterm'] = array(
    '#type' => 'fieldset',
    '#title' => t('Delete a Term'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['delterm']['sguid'] = array(
    '#type' => 'textfield',
    '#title' => t('String ID'),
    '#required' => TRUE,
  );

  $form['delterm']['buttons'] = array(
    //'#prefix' => '<div class="export-submit">',
    //'#suffix' => '</div>',
  );
  $form['delterm']['buttons']['submit'] = array(
    '#value' => t('Delete'),
    '#type' => 'submit',
  );

  return $form;
}

/**
 * Submission handler for delterm form.
 */
function btrClient_delterm_form_submit($form, &$form_state) {
  $sguid = check_plain(trim($form_state['values']['sguid']));
  $GLOBALS['btr']->del_string(array('sguid' => $sguid));

  // redirect to the list of terms
  $lng = variable_get('btrClient_translation_lng', 'fr');
  drupal_goto("translations/search",
    array('query' => array(
        'lng' => $lng,
        'project' => 'vocabulary',
        'limit' => 10,
      )));
}
