<?php
/**
 * @file
 * Import strings and translations from POT/PO files of projects.
 */

/**
 * Menu callback: translations/addterm
 * Add a new term on the vocabulary.
 */
function l10n_feedback_addterm() {
  $output[] = drupal_get_form('l10n_feedback_addterm_form');
  if(user_access('administer')) {
    $output[] = drupal_get_form('l10n_feedback_delterm_form');
  }
  return $output;
}

/**
 * Form: addterm
 */
function l10n_feedback_addterm_form() {
  $form = array(
    '#prefix' => '<div class="l10n-feedback-filter clear-block">',
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
function l10n_feedback_addterm_form_submit($form, &$form_state) {

  //dpm($form_state['values']);  //debug
  $string = check_plain(trim($form_state['values']['newterm']));
  $context = '';
  $sguid = sha1($string . $context);

  $db = $GLOBALS['l10n_feedback_db'];

  // check whether this string already exists or not
  $query = "SELECT sguid FROM l10n_feedback_strings WHERE sguid = :sguid";
  $args = array(':sguid' => $sguid);
  $field = $db->query($query, $args)->fetchField();
  if (!empty($field)) {
    drupal_set_message(t('This term already exists.'));
    return;
  }

  // insert the new string
  $db->insert('l10n_feedback_strings')
    ->fields(array(
        'string' => $string,
        'context' => $context,
        'sguid' => $sguid,
        'uid' => 1,
        'time' => date('Y-m-d H:m:s'),
        'count' => 1,
      ))
    ->execute();

  // get the template id
  $origin = 'misc';
  $project = 'vocabulary';
  $potname = 'vocabulary';
  $potid = $db->select('l10n_feedback_templates', 't')
    ->fields('t', array('potid'))
    ->condition('pguid', sha1($origin . $project))
    ->condition('tplname', $potname)
    ->execute()
    ->fetchField();

  // insert a new location
  $db->insert('l10n_feedback_locations')
    ->fields(array(
        'sguid' => $sguid,
        'potid' => $potid,
      ))
    ->execute();

  // redirect to translating the term
  $lng = variable_get('l10n_feedback_translation_lng', 'fr');
  drupal_goto("translations/$lng/$sguid");
}

/**
 * Form: delterm
 */
function l10n_feedback_delterm_form() {
  $form = array(
    '#prefix' => '<div class="l10n-feedback-filter clear-block">',
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
function l10n_feedback_delterm_form_submit($form, &$form_state) {

  $sguid = check_plain(trim($form_state['values']['sguid']));

  $db = $GLOBALS['l10n_feedback_db'];
  $db->delete('l10n_feedback_strings')->condition('sguid', $sguid)->execute();
  $db->delete('l10n_feedback_locations')->condition('sguid', $sguid)->execute();
  $db->delete('l10n_feedback_translations')->condition('sguid', $sguid)->execute();

  // redirect to the list of terms
  $lng = variable_get('l10n_feedback_translation_lng', 'fr');
  drupal_goto("translations/search",
    array('query' => array(
        'lng' => $lng,
        'project' => 'vocabulary',
        'limit' => 10,
      )));
}


/**
 * Menu callback: translations/import
 * Import strings and translations from POT/PO files of projects.
 */
function l10n_feedback_import() {
  return 'Not implemented yet.';
}
