<?php
/**
 * @file
 * Add ne terms in vocabulary.
 */

/**
 * Menu callback: translations/addterm
 * Add a new term on the vocabulary.
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
  $form = array(
    '#prefix' => '<div class="btr-ui-filter clear-block">',
    '#suffix' => '</div>',
  );

  $form['addterm'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add a New Term'),
    '#description' => t('Add a new interesting term on the vocabulary.'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['addterm']['newterm'] = array(
    '#type' => 'textfield',
    '#title' => t('New Term'),
    '#required' => TRUE,
    //'#description' => t('The origin of the project.'),
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
  $string = check_plain(trim($form_state['values']['newterm']));

  $result = $GLOBALS['btr']->add_string(array(
              'origin' => 'misc',
              'project' => 'vocabulary',
              'tplname' => 'vocabulary',
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
    '#description' => t('Delete a term from the vocabulary.'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['delterm']['sguid'] = array(
    '#type' => 'textfield',
    '#title' => t('String ID'),
    '#required' => TRUE,
    //'#description' => t('The origin of the project.'),
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
