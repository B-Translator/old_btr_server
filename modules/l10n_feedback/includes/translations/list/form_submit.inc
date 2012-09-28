<?php

// = Translation form submission ===============================================

/**
 * Form submit callback for l10n_feedback_translate_form().
 *
 * @see l10n_feedback_translate_form().
 */
function l10n_feedback_translate_form_submit($form, &$form_state) {

  $form_values = $form_state['values'];
  //dpm($form_values);  //debug

  // Check that the button  clicked was either Save or Next or Previous.
  $op = $form_values['op'];
  if ( $op != t('Save') && $op != t('Next') && $op != t('Previous') ) {
    return;
  }

  // Save the values selected on the form (votes or new suggestions).
  _l10n_feedback_translate_form_save($form_values);

  if ($op == t('Previous')) {
    if (isset($_SESSION['previous_url'])) {
      $previous_url = $_SESSION['previous_url'];
      $_SESSION['previous_url'] = htmlentities($_SERVER['REQUEST_URI']);
      drupal_goto($previous_url);
    }
  }
  else if ($op == t('Next')) {
    $_SESSION['previous_url'] = htmlentities($_SERVER['REQUEST_URI']);
    $lng = $form_values['langcode'];
    drupal_goto("translations/$lng/");
  }
  else if ($op == t('Save')) {
    // Keep existing filters and other query arguments on form submission.
    $redirect_args = $form_values['target'];
    unset($redirect_args['q']);
    $form_state['redirect'] = array($form_values['target']['q'], array('query' => $redirect_args));
  }
}

/**
 * Save the values selected on the form (votes or new suggestions).
 */
function _l10n_feedback_translate_form_save($form_values) {

  $save_access = (user_access('btranslator-vote') || user_access('btranslator-suggest'));
  if (!$save_access) {
    drupal_set_message(t("You don't have access for giving feedback!"), 'error');
    return;
  }

  // get the langcode submitted with the form
  $lng = $form_values['langcode'];

  // check whether the submitted lng is valid for providing feedback on this site
  $translation_lng = variable_get('l10n_feedback_translation_lng');
  if ($lng != $translation_lng) {
    drupal_set_message(t("You cannot give feedback for the language '$lng' on this site!"), 'error');
    return;
  }

  // Get the voting mode.
  $voting_mode = variable_get('l10n_feedback_voting_mode', 'single');

  // keep track of the status, so that propper notification
  // can be displayed to the user
  global $l10n_feedback_save_status;
  $l10n_feedback_save_status = array(
    'cannot_vote' => 0,
    'cannot_suggest' => 0,
    'nr_votes' => 0,
    'nr_suggestions' => 0,
  );

  // Iterate outer structure built in l10n_feedback_translate_form().
  foreach ($form_values['strings'] as $sguid => $string) {

    if ($voting_mode == 'single') {
      _l10n_feedback_translate_form_submit_single($sguid, $lng, $string);
    }

    // Iterate inner structure built in _l10n_feedback_translate_form_item().
    // Form items have numeric $tguid values and other keys here.
    foreach ($string as $tguid => $translation) {
      if ($voting_mode == 'multiple') {
	_l10n_feedback_translate_form_submit_multiple($sguid, $tguid, $lng, $translation);
      }
      if ((strlen($tguid) == 40) && !empty($translation['declined'])) {
	//do something for declined translations
      }
    }
  }

  // Tell the user what happened.
  l10n_feedback_display_notification_messages();
}

function _l10n_feedback_translate_form_submit_single($sguid, $lng, $string) {

  $tguid = $string['approved'];

  if ($tguid == 'new' or $tguid == '') {
    //add a new suggestion
    $values = $string['new']['value'];
    l10n_feedback_add_suggestion($sguid, $lng, $values);
    return;
  }

  if (strlen($tguid) == 40) {
    // If this is not an existing vote,
    // then add a new vote for this translation.
    $previous_votes = $string[$tguid]['original']->votes;
    global $user;
    if (!in_array($user->name, array_keys($previous_votes))) {
      $umail = $user->init;  //initial mail of the user
      l10n_feedback_add_vote($tguid, $umail);
    }
  }
}

function _l10n_feedback_translate_form_submit_multiple($sguid, $tguid, $lng, $translation) {

  global $user;

  $approved = $translation['approved'];
  if ($tguid == 'new') {
    //add a new suggestion
    $values = isset($translation['value']) ? $translation['value'] : array();
    l10n_feedback_add_suggestion($sguid, $lng, $values);
  }
  elseif ($approved != '') {
    // Add a new vote for this translation
    // if such a vote does not exist.
    $previous_votes = $translation['original']->votes;
    if (!in_array($user->name, array_keys($previous_votes))) {
      $umail = $user->init;  // initial mail of the user
      l10n_feedback_add_vote($tguid, $umail);
    }
  }
  elseif ($approved == '') {
    // Remove this vote, if it exists.
    $previous_votes = $translation['original']->votes;
    if (in_array($user->name, array_keys($previous_votes))) {
      $umail = $user->init;  // initial mail of the user
      _l10n_feedback_clean_previous_votes($tguid, $umail, $sguid, $lng);
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
function l10n_feedback_add_vote($tguid, $umail) {

  // Check access permissions.
  if (!user_access('btranslator-vote')) {
    global $l10n_feedback_save_status;
    $l10n_feedback_save_status['cannot_vote']++;
    return NULL;
  }

  // Fetch the translation details from the DB.
  $db = $GLOBALS['l10n_feedback_db'];
  $sql = 'SELECT * FROM {l10n_feedback_translations} WHERE tguid = :tguid';
  $args = array(':tguid' => $tguid);
  $trans = $db->query($sql, $args)->fetchObject();

  // If there is no such translation, return NULL.
  if (empty($trans))  return NULL;

  // Clean any previous vote.
  $nr = _l10n_feedback_clean_previous_votes($tguid, $umail, $trans->sguid, $trans->lng);

  // Add the vote.
  $vid = $db->insert('l10n_feedback_votes')
    ->fields(array(
        'tguid' => $tguid,
        'umail' => $umail,
        'ulng' => variable_get('l10n_feedback_translation_lng'),
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();

  // Update vote count of the translation.
  $sql = 'SELECT COUNT(*) FROM {l10n_feedback_votes} WHERE tguid = :tguid';
  $count = $db->query($sql, $args)->fetchField();
  $db->update('l10n_feedback_translations')
    ->fields(array('count' => $count))
    ->condition('tguid', $tguid)
    ->execute();

  // Increment the number of the saved votes.
  global $l10n_feedback_save_status;
  $l10n_feedback_save_status['nr_votes']++;

  return $vid;
}

/**
 * Clean any previous vote by this user for this translation.
 *
 * This depends on the voting mode option (set by the admin).
 * If the voting mode is 'single', then the user can select
 * only one translation for a given string (at most one vote
 * per string).
 * If the voting mode is 'multiple', then the user can approve
 * several translations for a string (at most one vote per
 * translation).
 *
 * @param $tguid
 *   ID of the translation.
 * @param $umail
 *   The mail of the user.
 * @param $sguid
 *   ID of the source string.
 * @param $lng
 *   Language code of the translation.
 * @return
 *   Number of previous votes that were deleted.
 *   (Normally should be 0, but can also be 1. If it is >1,
 *   something must be wrong.)
 */
function _l10n_feedback_clean_previous_votes($tguid, $umail, $sguid, $lng) {

  $db = $GLOBALS['l10n_feedback_db'];

  // Check access permissions.
  if (!user_access('btranslator-vote')) {
    global $l10n_feedback_save_status;
    $l10n_feedback_save_status['cannot_vote']++;
    return 0;
  }

  //TODO: Instead of deleting previous votes, save them in
  //      an archive table, so that the history of changing
  //      votes can be preserved.

  // Get the voting mode.
  $voting_mode = variable_get('l10n_feedback_voting_mode', 'single');

  $arr_tguid = array();
  if ($voting_mode == 'multiple') {
    $arr_tguid = array($tguid);
  }
  else { // ($voting_mode == 'single')
    // Get the other sibling translations (translations of the same
    // string and the same language) which the user has voted.
    $sql = '
      SELECT DISTINCT t.tguid FROM {l10n_feedback_translations} t
      LEFT JOIN {l10n_feedback_votes} v ON (v.tguid = t.tguid)
      WHERE t.sguid = :sguid AND t.lng = :lng AND v.umail = :umail AND v.ulng = :ulng
    ';
    $params = array(':sguid' => $sguid, ':lng' => $lng, ':umail' => $umail, ':ulng' => $lng);
    $arr_tguid = $db->query($sql, $params)->fetchCol();
  }

  if (empty($arr_tguid))  return 0;

  // Remove any votes by the user for each translation in $arr_tguid.
  $num_deleted = $db->delete('l10n_feedback_votes')
    ->condition('umail', $umail)
    ->condition('ulng', $lng)
    ->condition('tguid', $arr_tguid, 'IN')
    ->execute();

  // Decrement the vote count for each translation in $arr_tguid.
  $num_updated = $db->update('l10n_feedback_translations')
    ->expression('count', 'count - 1')
    ->condition('tguid', $arr_tguid, 'IN')
    ->execute();

  return $num_deleted;
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
 * @param $umail
 *   The mail of the user that submitted the suggestion. If missing,
 *   the mail of the logged in user will be used.
 */
function l10n_feedback_add_suggestion($sguid, $lng, $values, $umail =NULL) {

  if ($umail == NULL) {
    global $user;
    $umail = $user->init;
  }

  $translation = l10n_feedback_pack_string($values);
  $translation = str_replace(t('<New translation>'), '', $translation);

  // Don't add empty translations.
  if (trim($translation) == '')  return false;

  // Check access permissions.
  if (!user_access('btranslator-suggest')) {
    global $l10n_feedback_save_status;
    $l10n_feedback_save_status['cannot_suggest']++;
    return false;
  }

  // Load the string and adjust translation whitespace based on source.
  $db = $GLOBALS['l10n_feedback_db'];
  $query = 'SELECT string FROM {l10n_feedback_strings} WHERE sguid = :sguid';
  $source_string = $db->query($query, array(':sguid' => $sguid))->fetchField();
  $translation = l10n_feedback_trim($translation, $source_string);

  // Look for an existing translation, if any.
  $tguid = sha1($translation . $lng . $sguid);
  $query = 'SELECT translation FROM {l10n_feedback_translations} WHERE tguid = :tguid';
  $existing = $db->query($query, array(':tguid' => $tguid))->fetchField();

  // If this translation already exists, there is nothing to be added.
  if (!empty($existing))  return false;

  // Insert the new suggestion.
  $db->insert('l10n_feedback_translations')
    ->fields(array(
        'sguid' => $sguid,
        'lng' => $lng,
        'translation' => $translation,
	'tguid' => $tguid,
        'count' => 1,
	'umail' => $umail,
        'ulng' => $lng,
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();

  // Add also a vote for the new suggestion.
  $vid = l10n_feedback_add_vote($tguid, $umail);

  //TODO: Notify previous voters of this string that a new suggestion
  //      has been submitted. Maybe they would like to review it and
  //      change their vote.

  // Increment the number of the saved suggestions.
  global $l10n_feedback_save_status;
  $l10n_feedback_save_status['nr_suggestions']++;

  return $tguid;
}

/**
 * Make spacing and newlines the same in translation as in the source.
 *
 * @param $translation
 *   Translation string.
 * @param $source
 *   Source string.
 * @return
 *   Translation string with the right beginning and ending chars.
 */
function l10n_feedback_trim($translation, $source) {
  $matches = array();
  preg_match("/^(\s*).*\S(\s*)\$/s", $source, $matches);
  return $matches[1] . trim($translation) . $matches[2];
}

function l10n_feedback_display_notification_messages() {

  global $l10n_feedback_save_status;
  extract($l10n_feedback_save_status);

  if ($cannot_vote > 0) {
    drupal_set_message(t('You do not have enough rights for submitting votes!'), 'error');
  }

  if ($cannot_suggest > 0) {
    drupal_set_message(t('You do not have enough rights for making suggestions!'), 'error');
  }

  if ($nr_suggestions > 0) {
    drupal_set_message(t("The number of saved suggestions: $nr_suggestions"));
  }

  if ($nr_votes > 0) {
    drupal_set_message(t("The number of saved votes: $nr_votes"));
  }
}
?>