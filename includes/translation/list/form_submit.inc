<?php

// = Translation form submission ===============================================

/**
 * Form submit callback for l10n_suggestions_translate_form().
 *
 * @see l10n_suggestions_translate_form().
 */
function l10n_suggestions_translate_form_submit($form, &$form_state) {
  global $user;

  //TODO: rename 'active' to something related to voting

  $form_values = $form_state['values'];
  dpm($form_values, '$form_values');  //debug

  $lng = $form_values['langcode'];

  // Iterate outer structure built in l10n_suggestions_translate_form().
  foreach ($form_values['strings'] as $sid => $string) {

    $tid_voted = $string['active'];
    if (!$tid_voted)  continue;

    if (is_numeric($tid_voted) && $tid_voted > 0) {
      // This translation is voted by the user.
      // If this is not an existing vote,
      // then add a new vote for this translation.
      $previous_votes = $string[$tid_voted]['original']->votes;
      if (!in_array($user->uid, array_keys($previous_votes))) {
        l10n_suggestions_add_vote($tid_voted, $user->uid);
      }
    }
    else if ($tid_voted == 'new') {
      //add a new suggestion
      $values = $string['new']['value'];
      $suggestion = l10n_suggestions_pack_string($values);
      $suggestion = str_replace(t('<New translation>'), '', $suggestion);
      if (trim($suggestion) != '') {
        l10n_suggestions_add_suggestion($sid, $lng, $suggestion, $user->uid);
      }
    }

    // Iterate inner structure built in _l10n_suggestions_translate_form_item().
    // Form items have numeric $tid values and other keys here.
    foreach ($string as $tid => $options) {
      if (!empty($options['declined'])) {
        //do something for declined translations
      }
    }
  }

  /*
  // TODO:
  // Tell the user what happened.
  l10n_suggestions_update_message();
  */

  // Keep existing filters and other query arguments on form submission.
  $redirect_args = $form_state['values']['target'];
  unset($redirect_args['q']);
  $form_state['redirect'] = array($form_state['values']['target']['q'], array('query' => $redirect_args));
}

/**
 * Add a vote for the given translation from the given user.
 * Make sure that any previous vote is cleaned first
 * (don't allow multiple votes for the same translation).
 *
 * @param $tid
 *   ID of the translation.
 * @param $uid
 *   ID of the user.
 * @return
 *   The ID of the new vote, or NULL.
 */
function l10n_suggestions_add_vote($tid, $uid) {
  // Fetch the translation details from the DB.
  $sql = 'SELECT * FROM {l10n_suggestions_translations} WHERE tid = :tid';
  $trans = db_query($sql, array(':tid' => $tid))->fetchObject();

  // If there is no such translation, return NULL.
  if (empty($trans))  return NULL;

  // Clean any previous vote.
  $nr = _l10n_suggestions_clean_previous_votes($tid, $uid, $trans->pid, $trans->lng);

  // Add the vote.
  $vid = db_insert('l10n_suggestions_votes')
    ->fields(array(
        'tid' => $tid,
        'uid' => $uid,
        'vtime' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();

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
 * @param $tid
 *   ID of the translation.
 * @param $uid
 *   ID of the user.
 * @param $sid
 *   ID of the source string.
 * @param $lng
 *   Language code of the translation.
 * @return
 *   Number of previous votes that were deleted.
 *   (Normally should be 0, but can also be 1. If it is >1,
 *   something must be wrong.)
 */
function _l10n_suggestions_clean_previous_votes($tid, $uid, $sid, $lng) {

  //TODO: Instead of deleting previous votes, save them in
  //      an archive table, so that the history of changing
  //      votes can be preserved.

  //TODO: Add the configuration variable l10n_suggestions_voting_mode
  //      which can be changed by the admin.

  // Get the voting mode.
  $voting_mode = variable_get('l10n_suggestions_voting_mode', 'single');

  if ($voting_mode == 'multiple') {
    // Remove any other votes by the user for this translation.
    $num_deleted = db_delete('l10n_suggestions_votes')
      ->condition('uid', $uid)
      ->condition('tid', $tid)
      ->execute();

    return $num_deleted;
  }
  else { // ($voting_mode == 'single')
    // Get the other sibling translations
    // (translations of the same string for the same language).
    $sql = 'SELECT tid FROM {l10n_suggestions_translations} '
      . 'WHERE pid = :pid AND lng = :lng';
    $params = array(':pid' => $sid, ':lng' => $lng);
    $arr_tid = db_query($sql, $params)->fetchCol();

    if (empty($arr_tid))  return 0;

    // Remove any other votes by the user for this string.
    $num_deleted = db_delete('l10n_suggestions_votes')
      ->condition('uid', $uid)
      ->condition('tid', $arr_tid, 'IN')
      ->execute();

    return $num_deleted;
  }
}

/**
 * Adds a new translation suggestion to a source string.
 *
 * @param $sid
 *   The string ID for which a new suggestion should be added.
 * @param $lng
 *   The language code of the new suggestion.
 * @param $translation
 *   String representing the new translation suggestion.
 * @param $uid
 *   ID of the user that submitted the suggestion.
 */
function l10n_suggestions_add_suggestion($sid, $lng, $translation, $uid) {

  // Don't add empty translations.
  if (trim($translation) == '')  return false;

  // Load the string and adjust translation whitespace based on source.
  $query = 'SELECT phrase FROM {l10n_suggestions_phrases} WHERE pid = :pid';
  $source_string = db_query($query, array(':pid' => $sid))->fetchField();
  $translation = l10n_suggestions_trim($translation, $source_string);

  // Look for an existing translation, if any.
  // Use HASH matching to avoid marking case-corrections as duplicate.
  $hash = l10n_suggestions_get_string_hash($translation);
  $query = 'SELECT translation FROM {l10n_suggestions_translations} '
    . 'WHERE pid = :pid AND lng = :lng AND hash = UNHEX(:hash)';
  $params = array(':pid' => $sid, ':lng' => $lng, ':hash' => $hash);
  $existing = db_query($query, $params)->fetchField();

  // If this translation already exists, there is nothing to be added.
  if (!empty($existing))  return false;

  // Insert the new suggestion.
  $tid = db_insert('l10n_suggestions_translations')
    ->fields(array(
        'pid' => $sid,
        'lng' => $lng,
        'translation' => $translation,
        'vcount' => 1,
        'uid_entered' => $uid,
        'time_entered' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();
  db_query('UPDATE {l10n_suggestions_translations} SET hash = UNHEX(translation)');

  // Add also a vote for the new suggestion.
  $vid = l10n_suggestions_add_vote($tid, $uid);

  //TODO: Notify previous voters of this string that a new suggestion
  //      has been submitted. Maybe they would like to review it and
  //      change their vote.

  return $tid;
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
function l10n_suggestions_trim($translation, $source) {
  $matches = array();
  preg_match("/^(\s*).*\S(\s*)\$/s", $source, $matches);
  return $matches[1] . trim($translation) . $matches[2];
}

?>