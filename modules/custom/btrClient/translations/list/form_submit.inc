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
    $_SESSION['btr']['translate_form']['state'] = $form_state;
    oauth2_login();
  }

  // Save the values selected on the form (votes or new suggestions).
  if (user_is_logged_in()) {
    _btrClient_translate_form_save($form_values);
  }
  else {
    drupal_set_message(t("You need to be logged in, in order to be able to submit votes and suggestions."));
  }

  $_SESSION['btr']['same_project'] = isset($form_state['input']['same_project']) ? TRUE : FALSE;
  if ($op == t('Previous')) {
    if (isset($_SESSION['btr']['previous_url'])) {
      $previous_url = $_SESSION['btr']['previous_url'];
      $_SESSION['btr']['previous_url'] = htmlentities(request_uri());
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
    $_SESSION['btr']['previous_url'] = htmlentities(request_uri());
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

  // keep track of the status, so that propper notification
  // can be displayed to the user
  global $_btrClient_notification_messages;
  $_btrClient_notification_messages = array(
    'messages' => array(),
    'nr_votes' => 0,
    'nr_suggestions' => 0,
    'nr_deletions' => 0,
  );

  // Get the voting mode.
  $voting_mode = variable_get('btr_voting_mode', 'single');

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
	_btrClient_delete_translation($translation);
      }
    }
  }

  // Tell the user what happened.
  btrClient_display_notification_messages();
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
    btrClient_add_suggestion($sguid, $lng, $string['new']['value']);
    return;
  }

  $tguid = $string['approved'];
  if (strlen($tguid) == 40) {
    // If this is not an existing vote,
    // then add a new vote for this translation.
    $previous_votes = $string[$tguid]['original']['votes'];
    global $user;
    if (!in_array($user->name, array_keys($previous_votes))) {
      $umail = $user->init;  // initial mail of the user
      btrClient_add_vote($tguid, $umail);
    }
  }
}

function _btrClient_translate_form_submit_multiple($sguid, $tguid, $lng, $translation) {

  global $user;

  $approved = $translation['approved'];
  if ($tguid == 'new' and is_not_empty_translation($translation['value'])) {
    btrClient_add_suggestion($sguid, $lng, $translation['value']);
  }
  elseif ($approved != '') {
    // Add a new vote for this translation
    // if such a vote does not exist.
    $previous_votes = $translation['original']['votes'];
    if (!in_array($user->name, array_keys($previous_votes))) {
      $umail = $user->init;  // initial mail of the user
      btrClient_add_vote($tguid, $umail);
    }
  }
  elseif ($approved == '') {
    // Remove this vote, if it exists.
    $previous_votes = $translation['original']['votes'];
    if (in_array($user->name, array_keys($previous_votes))) {
      if (btr_user_access('btranslator-vote')) {
	$umail = $user->init;  // initial mail of the user
	_btrClient_clean_previous_votes($tguid, $umail, $sguid, $lng);
      }
      else {
	global $_btrClient_notification_messages;
	$_btrClient_notification_messages['messages'][] = array(t('You do not have enough rights for submitting votes!'), 'error');
      }
    }
  }
}

/**
 * Add a vote for the given translation from the given user.
 * Make sure that any previous vote is cleaned first
 * (don't allow multiple votes for the same translation).
 *
 * @param $tguid
 *   ID of the translation.
 * @param $umail
 *   The user email.
 * @return
 *   The ID of the new vote, or NULL.
 */
function btrClient_add_vote($tguid, $umail) {
  // Check access permissions.
  if (!btr_user_access('btranslator-vote')) {
    global $_btrClient_notification_messages;
    $_btrClient_notification_messages['messages'][] = array(t('You do not have enough rights for submitting votes!'), 'error');
    return NULL;
  }

  // Add a vote.
  $lng = variable_get('btrClient_translation_lng', 'fr');
  $vid = btr_add_vote($tguid, $umail, $lng);

  // Increment the number of the saved votes.
  global $_btrClient_notification_messages;
  if ($vid) {
    $_btrClient_notification_messages['nr_votes']++;
  }

  return $vid;
}


/**
 * Adds a new translation suggestion to a source string.
 *
 * @param $sguid
 *   The string ID for which a new suggestion should be added.
 * @param $lng
 *   The language code of the new suggestion.
 * @param $values
 *   Array of strings containing the new translation suggestion
 *   for the singular version and for plural version(s) (if any).
 * @return
 *   The ID of the new translation ($tguid),
 *   or FALSE if no translation was added.
 */
function btrClient_add_suggestion($sguid, $lng, $values) {
  $translation = btrClient_pack_string($values);
  $translation = str_replace(t('<New translation>'), '', $translation);

  // Check access permissions.
  if (!btr_user_access('btranslator-suggest')) {
    global $_btrClient_notification_messages;
    $_btrClient_notification_messages['messages'][] = array(t('You do not have enough rights for making suggestions!'), 'error');
    return FALSE;
  }

  // Add the translation suggestion.
  $tguid  = btr_add_translation($sguid, $lng, $translation);
  if (!$tguid)  return FALSE;  // no translation was added

  // Increment the number of the saved suggestions.
  global $_btrClient_notification_messages;
  $_btrClient_notification_messages['nr_suggestions']++;

  return $tguid;
}


/**
 * Delete the translation and any related votes.
 * Notify the author and the voters about the deletion.
 *
 * $translation is an array/object structure with all the
 * information about the translation, votes, etc.
 */
function _btrClient_delete_translation($translation) {
  //dpm($translation);  //debug
  $trans = $translation['original'];

  // Check that the current user has the right to delete translations.
  $is_own = ($GLOBALS['user']->name == $trans['author']);
  if (!$is_own and !btr_user_access('btranslator-resolve')) {
    drupal_set_message(t('You are not allowed to delete this translation!'), 'error');
    return;
  }

  // Delete the translation.
  $account = user_load($GLOBALS['user']->uid);
  btr_del_translation(
    $tguid = $trans['tguid'],   // id of the translation to be deleted
    $umail = $account->init,  // email of the user that is deleting it
    $ulng = variable_get('btrClient_translation_lng')
  );

  global $_btrClient_notification_messages;
  $_btrClient_notification_messages['nr_deletions']++;
}


/**
 * Display the number of the votes and translations that
 * are added, deleted, etc.
 */
function btrClient_display_notification_messages() {
  global $_btrClient_notification_messages;
  extract($_btrClient_notification_messages);

  if ($nr_suggestions > 0) {
    $msg = format_plural($nr_suggestions, '1 suggestion saved', '@count suggestions saved');
    $messages[] = array($msg, 'status');
  }
  if ($nr_votes > 0) {
    $msg = format_plural($nr_votes, '1 vote saved', '@count votes saved');
    $messages[] = array($msg, 'status');
  }
  if ($nr_deletions > 0) {
    $msg = format_plural($nr_deletions, '1 translation deleted', '@count translations deleted');
    $messages[] = array($msg, 'status');
  }

  // Display messages, warnings and errors.
  foreach ($messages as $message) {
    list($msg, $type) = $message;
    drupal_set_message($msg, $type);
  }
}
