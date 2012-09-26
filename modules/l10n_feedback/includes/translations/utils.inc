<?php
/**
 * Functions that are common for all the translation pages.
 */

/**
 * Get the details of strings, translations and votes and return them
 * as an associative array, in a suitable format for being displayed.
 *
 * @param $filter_query
 *   A db_select query object that returns the strings that should be
 *   displayed, in the descending orders of matching scores.
 * @param $lng
 *   Language code of the translations.
 * @return
 *   An array of strings, translations and votes, where each string
 *   is an associative array, with translations and votes as nested
 *   associative arrays.
 */
function l10n_feedback_get_strings($filter_query, $lng) {

  $db = $GLOBALS['l10n_feedback_db'];

  //get the IDs of the strings that are returned by the filter query
  $assoc_arr_sguid = $filter_query->execute()->fetchAllAssoc('sguid');
  if (empty($assoc_arr_sguid))  return array();
  $arr_sguid = array_keys($assoc_arr_sguid);

  //get string details
  $get_strings = "
      SELECT sguid, string
      FROM {l10n_feedback_strings}
      WHERE sguid IN (:arr_sguid)
  ";
  $args = array(':arr_sguid' => $arr_sguid);
  $result = $db->query($get_strings, $args);
  $arr_strings = $result->fetchAllAssoc('sguid');

  //get translations
  $get_translations = "
      SELECT s.sguid, t.tguid, t.lng, t.translation,
             t.time, u.name AS author, u.umail, u.ulng, u.uid, t.count
      FROM {l10n_feedback_strings} s
      LEFT OUTER JOIN {l10n_feedback_translations} t ON (s.sguid = t.sguid)
      LEFT OUTER JOIN {l10n_feedback_users} u ON (u.umail = t.umail AND u.ulng = t.ulng)
      WHERE (t.lng = :lng) AND s.sguid IN (:arr_sguid)
      ORDER BY t.count DESC
  ";
  $args = array(':lng' => $lng, ':arr_sguid' => $arr_sguid);
  $result = $db->query($get_translations, $args);
  $arr_translations = $result->fetchAllAssoc('tguid');

  //get votes
  $arr_tguid = array_keys($arr_translations);
  if (empty($arr_tguid)) {
    $arr_votes = array();
  }
  else {
    $get_votes = "
        SELECT t.tguid, v.vid, u.name, u.umail, u.ulng, u.uid, v.time
        FROM {l10n_feedback_translations} t
        LEFT OUTER JOIN {l10n_feedback_votes} v ON (v.tguid = t.tguid)
        LEFT OUTER JOIN {l10n_feedback_users} u ON (u.umail = v.umail AND u.ulng = v.ulng)
        WHERE t.tguid IN (:arr_tguid)
        ORDER BY v.time DESC
    ";
    $args = array(':arr_tguid' => $arr_tguid);
    $result = $db->query($get_votes, $args);
    $arr_votes = $result->fetchAllAssoc('vid');
  }

  //get alternatives (from other languages)
  //they are the best translations (max count) from the alternative languages
  global $user;
  $arr_lng = l10n_feedback_get_auxiliary_languages(user_load($user->uid));
  if (empty($arr_lng)) {
    $arr_alternatives = array();
  }
  else {
    $get_alternatives = "
        SELECT DISTINCT t.sguid, t.tguid, t.lng, t.translation, t.count
        FROM (SELECT sguid, lng, MAX(count) AS max_count
	      FROM l10n_feedback_translations
	      WHERE lng IN (:arr_lng) AND sguid IN (:arr_sguid)
	      GROUP BY sguid, lng
	      ) AS m
        INNER JOIN l10n_feedback_translations AS t
	      ON m.sguid = t.sguid AND m.lng = t.lng AND m.max_count = t.count
        GROUP BY t.sguid, t.lng, t.count
    ";
    $args = array(':arr_lng' => $arr_lng, ':arr_sguid' => $arr_sguid);
    $result = $db->query($get_alternatives, $args);
    $arr_alternatives = $result->fetchAllAssoc('tguid');
  }
  //dpm($arr_alternatives, '$arr_alternatives');  //debug

  // Put alternatives as nested array under strings.
  foreach ($arr_alternatives as $tguid => $alternative) {
    $sguid = $alternative->sguid;
    $lng = $alternative->lng;
    $arr_strings[$sguid]->alternatives[$lng] = $alternative->translation;
  }

  // Put votes as nested arrays inside translations.
  // Votes are already ordered by time (desc).
  foreach ($arr_votes as $vid => $vote) {
    $tguid = $vote->tguid;
    $name = $vote->name;
    $arr_translations[$tguid]->votes[$name] = $vote;
  }

  // Put translations as nested arrays inside strings.
  // Translations are already ordered by count (desc).
  // Make sure that each translation has an array of votes
  // (even though it may be empty).
  foreach ($arr_translations as $tguid => $translation) {
    if (!isset($translation->votes))  $translation->votes = array();
    $sguid = $translation->sguid;
    $arr_strings[$sguid]->translations[$tguid] = $translation;
  }

  // Put strings in the same order as $arr_sguid.
  // Make sure as well that each string has an array of translations
  // (even though it may be empty).
  foreach ($arr_sguid as $sguid) {
    $string = $arr_strings[$sguid];
    if (!isset($string->translations)) $string->translations = array();
    if (!isset($string->alternatives)) $string->alternatives = array();
    $strings[$sguid] = $string;
  }

  return $strings;
}

/**
 * Unpacks a string as retrieved from the database.
 *
 * Creates an array out of the string. If it was a single string, the array
 * will have one item. If the string was a plural string, the array will have
 * as many items as the language requires (two for source strings).
 *
 * @param $string
 *   The string with optional separation markers (NULL bytes)
 * @return
 *   An array of strings with one element for each plural form in case of
 *   a plural string, or one element in case of a regular string. This
 *  is called a $textarray elsewhere.
 */
function l10n_feedback_unpack_string($string) {
  return explode("\0", $string);
}

/**
 * Packs a string for storage in the database.
 *
 * @param $string
 *   An array of strings.
 * @return
 *   A packed string with NULL bytes separating each string.
 */
function l10n_feedback_pack_string($strings) {
  if (is_array($strings)) {
    return implode("\0", $strings);
  }
  else {
    return $strings;
  }
}

?>