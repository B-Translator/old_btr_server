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
function l10n_suggestions_get_strings($filter_query, $lng) {
  //get the IDs of the strings that are returned by the filter query
  $assoc_arr_sid = $filter_query->execute()->fetchAllAssoc('sid');
  if (empty($assoc_arr_sid))  return array();
  $arr_sid = array_keys($assoc_arr_sid);

  //get string details
  $get_strings =
    " SELECT sid, string, hash
      FROM {l10n_suggestions_strings}
      WHERE sid IN (:arr_sid)";
  $result = db_query($get_strings, array(':arr_sid' => $arr_sid));
  $arr_strings = $result->fetchAllAssoc('sid');

  //get translations
  $get_translations =
    " SELECT s.sid, t.tid, t.lng, t.translation, t.hash,
             t.time, t.uid, u.name AS author, t.count
      FROM {l10n_suggestions_strings} s
      LEFT OUTER JOIN {l10n_suggestions_translations} t ON (s.sid = t.sid)
      LEFT OUTER JOIN {users} u ON (u.uid = t.uid)
      WHERE (t.lng = :lng) AND s.sid IN (:arr_sid)
      ORDER BY t.count DESC";
  $result = db_query($get_translations, array(':lng' => $lng, ':arr_sid' => $arr_sid));
  $arr_translations = $result->fetchAllAssoc('tid');

  //get votes
  $arr_tid = array_keys($arr_translations);
  if (empty($arr_tid)) {
    $arr_votes = array();
  }
  else {
    $get_votes =
      " SELECT t.tid, v.vid, v.uid, u.name, v.time
        FROM {l10n_suggestions_translations} t
        LEFT OUTER JOIN {l10n_suggestions_votes} v ON (v.tid = t.tid)
        LEFT OUTER JOIN {users} u ON (u.uid = v.uid)
        WHERE t.tid IN (:arr_tid)
        ORDER BY v.time DESC";
    $result = db_query($get_votes, array(':arr_tid' => $arr_tid));
    $arr_votes = $result->fetchAllAssoc('vid');
  }

  //get alternatives (from other languages)
  //they are the best translations (max count) from the alternative languages
  $get_alternatives =
    " SELECT DISTINCT t.sid, t.tid, t.lng, t.translation, t.count
      FROM (SELECT sid, lng, MAX(count) AS max_count
	    FROM l10n_suggestions_translations
	    WHERE lng IN (:arr_lng) AND sid IN (:arr_sid)
	    GROUP BY sid, lng
	    ) AS m
      INNER JOIN l10n_suggestions_translations AS t
	    ON m.sid = t.sid AND m.lng = t.lng AND m.max_count = t.count
      GROUP BY t.sid, t.lng, t.count";
  $arr_lng = array('fr', 'sq');
  $result = db_query($get_alternatives, array(':arr_lng' => $arr_lng, ':arr_sid' => $arr_sid));
  $arr_alternatives = $result->fetchAllAssoc('tid');
  //dpm($arr_alternatives, '$arr_alternatives');  //debug

  // Put alternatives as nested array under strings.
  foreach ($arr_alternatives as $tid => $alternative) {
    $sid = $alternative->sid;
    $lng = $alternative->lng;
    $arr_strings[$sid]->alternatives[$lng] = $alternative->translation;
  }

  // Put votes as nested arrays inside translations.
  // Votes are already ordered by time (desc).
  foreach ($arr_votes as $vid => $vote) {
    $tid = $vote->tid;
    $uid = $vote->uid;
    $arr_translations[$tid]->votes[$uid] = $vote;
  }

  // Put translations as nested arrays inside strings.
  // Translations are already ordered by count (desc).
  // Make sure that each translation has an array of votes
  // (even though it may be empty).
  foreach ($arr_translations as $tid => $translation) {
    if (!isset($translation->votes))  $translation->votes = array();
    $sid = $translation->sid;
    $arr_strings[$sid]->translations[$tid] = $translation;
  }

  // Put strings in the same order as $arr_sid.
  // Make sure as well that each string has an array of translations
  // (even though it may be empty).
  foreach ($arr_sid as $sid) {
    $string = $arr_strings[$sid];
    if (!isset($string->translations)) $string->translations = array();
    if (!isset($string->alternatives)) $string->alternatives = array();
    $strings[$sid] = $string;
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
function l10n_suggestions_unpack_string($string) {
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
function l10n_suggestions_pack_string($strings) {
  if (is_array($strings)) {
    return implode("\0", $strings);
  }
  else {
    return $strings;
  }
}

function l10n_suggestions_get_string_hash($l10n_string) {
  $l10n_string = preg_replace('/^ +/', '', $l10n_string);
  $l10n_string = preg_replace('/ +$/', '', $l10n_string);
  $l10n_string = sha1($l10n_string);
  return $l10n_string;
}

?>