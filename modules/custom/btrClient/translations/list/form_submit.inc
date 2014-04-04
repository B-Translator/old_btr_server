<?php
/**
 * @file
 * Translation form submission.
 * The form may contain more than one translations.
 */

/**
 * Form submit callback for btrClient_translate_form().
 *
 * @see btrClient_translate_form().
 */
function btrClient_translate_form_submit($form, &$form_state) {
  $form_values = $form_state['values'];

  // Check that the button clicked was either Save, or Next, or Previous, etc.
  $op = $form_values['op'];
  $operations = array(
    t('Login'),
    t('Previous'),
    t('Save'),
    t('Next'),
    t('Translated'),
    t('Untranslated'),
  );
  if (!in_array($op, $operations))  return;

  if ($op == t('Login')) {
    oauth2_login();
    // Function oauth2_login() calls drupal_goto(), so this function
    // practically ends here, does not continue further down.
  }

  if ($op == t('Save') and !user_is_logged_in()) {
    // Save $form_state to session and redirect to login.
    $_SESSION['btrClient']['translate_form']['state'] = $form_state;
    oauth2_login();
  }

  // Save the values selected on the form (votes or new suggestions).
  if (user_is_logged_in()) {
    _btrClient_translate_form_save($form_values);
  }
  else {
    drupal_set_message(t("You need to be logged in, in order to be able to submit votes and suggestions."));
  }

  $_SESSION['btrClient']['same_project'] = isset($form_state['input']['same_project']) ? TRUE : FALSE;
  if ($op == t('Previous')) {
    if (isset($_SESSION['btrClient']['previous_url'])) {
      $previous_url = $_SESSION['btrClient']['previous_url'];
      $_SESSION['btrClient']['previous_url'] = htmlentities(request_uri());
      drupal_goto($previous_url);
    }
  }
  elseif ($op == t('Save')) {
    // Keep existing filters and other query arguments on form submission.
    $redirect_args = $form_values['target'];
    unset($redirect_args['q']);
    $form_state['redirect'] = array($form_values['target']['q'], array('query' => $redirect_args));
  }
  else {
    $_SESSION['btrClient']['previous_url'] = htmlentities(request_uri());
    $lng = $form_values['langcode'];
    if ($op == t('Next')) {
      drupal_goto("translations/$lng/");
    }
    elseif ($op == t('Translated')) {
      drupal_goto("translations/$lng/translated");
    }
    elseif ($op == t('Untranslated')) {
      drupal_goto("translations/$lng/untranslated");
    }
  }
}

/**
 * Save the values selected on the form (votes or new suggestions).
 */
function _btrClient_translate_form_save($form_values) {

  $save_access = (btr_user_access('btranslator-vote') || btr_user_access('btranslator-suggest'));
  if (!$save_access) {
    drupal_set_message(t("You don't have access for giving feedback!"), 'error');
    return;
  }

  // get the langcode submitted with the form
  $lng = $form_values['langcode'];

  // check whether the submitted lng is valid for providing feedback on this site
  $translation_lng = variable_get('btrClient_translation_lng', 'fr');
  if ($lng != $translation_lng) {
    drupal_set_message(t("You cannot give feedback for the language '@lng' on this site!", array('@lng' => $lng)), 'error');
    return;
  }

  // Get the voting mode.
  $voting_mode = variable_get('btrClient_voting_mode', 'single');

  // Iterate outer structure built in btrClient_translate_form().
  foreach ($form_values['strings'] as $sguid => $string) {

    if ($voting_mode == 'single') {
      _btrClient_translate_form_submit_single($sguid, $lng, $string);
    }

    // Iterate inner structure built in _btrClient_translate_form_item().
    // Form items have numeric $tguid values and other keys here.
    foreach ($string as $tguid => $translation) {
      if ($voting_mode == 'multiple') {
        _btrClient_translate_form_submit_multiple($sguid, $tguid, $lng, $translation);
      }
      if ((strlen($tguid) == 40) && !empty($translation['declined'])) {
	// Delete translation.
	btrClient_add_action('del', array('tguid' => $tguid));
      }
    }
  }

  // Submit the actions.
  global $btr, $_btrClient_actions;
  if (empty($_btrClient_actions))  return;
  $result = $btr->submit($_btrClient_actions);

  // Display any messages, warnings and errors.
  btrClient_display_messages($result['messages']);
}

function btrClient_add_action($action, $params) {
  global $_btrClient_actions;
  $_btrClient_actions[] = array('action' => $action, 'params' => $params);
}

/**
 * Return true if a new translation has been submitted.
 */
function is_not_empty_translation($translation) {
  $translation = btrClient_pack_string($translation);
  $translation = str_replace(t('<New translation>'), '', $translation);
  $translation = trim($translation);
  return !empty($translation);
}

function _btrClient_translate_form_submit_single($sguid, $lng, $string) {

  if ( is_not_empty_translation($string['new']['value']) ) {
    // Add a new suggestion.
    btrClient_add_action('add', array(
        'sguid' => $sguid,
        'lng' => $lng,
        'translation' => $string['new']['value'],
      ));
    return;
  }

  $tguid = $string['approved'];
  if (strlen($tguid) == 40) {
    // If this is not an existing vote,
    // then add a new vote for this translation.
    $previous_votes = $string[$tguid]['original']['votes'];
    global $user;
    if (!in_array($user->name, array_keys($previous_votes))) {
      btrClient_add_action('vote', array('tguid' => $tguid));
    }
  }
}

function _btrClient_translate_form_submit_multiple($sguid, $tguid, $lng, $translation) {

  global $user;

  $approved = $translation['approved'];
  if ($tguid == 'new' and is_not_empty_translation($translation['value'])) {
    btrClient_add_action('add', array(
        'sguid' => $sguid,
        'lng' => $lng,
        'translation' => $translation['value'],
      ));
  }
  elseif ($approved != '') {
    // Add a new vote for this translation
    // if such a vote does not exist.
    $previous_votes = $translation['original']['votes'];
    if (!in_array($user->name, array_keys($previous_votes))) {
      btrClient_add_action('vote', array('tguid' => $tguid));
    }
  }
  elseif ($approved == '') {
    // Remove this vote, if it exists.
    $previous_votes = $translation['original']['votes'];
    if (in_array($user->name, array_keys($previous_votes))) {
      btrClient_add_action('del_vote', array('tguid' => $tguid));
    }
  }
}
