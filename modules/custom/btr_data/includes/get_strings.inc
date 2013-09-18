<?php

function btr_get_string($sguid) {
  $sql = 'SELECT string FROM {btr_strings} WHERE sguid = :sguid';
  $args = array(':sguid' => $sguid);
  $string = $GLOBALS['btr_db']->query($sql, $args)->fetchField();
  return $string;
}

function btr_get_translation($tguid) {
  $sql = 'SELECT translation FROM {btr_translations} WHERE tguid = :tguid';
  $args = array(':tguid' => $tguid);
  $translation = $GLOBALS['btr_db']->query($sql, $args)->fetchField();
  return $translation;
}

function btr_get_search_results($filter, $lng) {
  //get a query for selecting strings that match the filter
  $query = btr_build_search_query($filter);
  if (!$query) {
    drupal_set_message(t('Filter is empty. Put something on the filter options.'));
  }
  //dpq($query);  //debug

  //get the strings that match the filter and the corresponding translations
  $strings = btr_get_query_strings($query, $lng);

  return $strings;
}

function btr_get_strings($arr_sguid, $lng, $alternative_langs = array()) {
  $query = $GLOBALS['btr_db']->select('btr_strings', 's')
    ->fields('s', array('sguid'))
    ->condition('s.sguid', $arr_sguid, 'IN');
  return btr_get_query_strings($filter_query, $lng, $alternative_langs);
}


/**
 * Get the details of strings, translations and votes and return them
 * as an associative array, in a suitable format for being displayed.
 *
 * @param $filter_query
 *   A db_select query object that returns the strings that should be
 *   displayed, in the descending orders of matching scores.
 * @param $lng
 *   Language code of the translations.
 * @param $alternative_langs
 *   Array of alternative (auxiliary) language codes. These languages
 *   are an alternative to English, in case that the translator is not
 *   quite familiar with English or needs some help from another language.
 * @return
 *   An array of strings, translations and votes, where each string
 *   is an associative array, with translations and votes as nested
 *   associative arrays.
 */
function btr_get_query_strings($filter_query, $lng, $alternative_langs = array()) {

  $db = $GLOBALS['btr_db'];

  //get the IDs of the strings that are returned by the filter query
  $assoc_arr_sguid = $filter_query->execute()->fetchAllAssoc('sguid');
  if (empty($assoc_arr_sguid))  return array();
  $arr_sguid = array_keys($assoc_arr_sguid);

  //get string details
  $get_strings = "
      SELECT sguid, string
      FROM {btr_strings}
      WHERE sguid IN (:arr_sguid)
  ";
  $args = array(':arr_sguid' => $arr_sguid);
  $result = $db->query($get_strings, $args);
  $arr_strings = $result->fetchAllAssoc('sguid');

  //get translations
  $get_translations = "
      SELECT s.sguid, t.tguid, t.lng, t.translation,
             t.time, u.name AS author, u.umail, u.ulng, u.uid, t.count
      FROM {btr_strings} s
      LEFT OUTER JOIN {btr_translations} t ON (s.sguid = t.sguid)
      LEFT OUTER JOIN {btr_users} u ON (u.umail = t.umail AND u.ulng = t.ulng)
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
        FROM {btr_translations} t
        LEFT OUTER JOIN {btr_votes} v ON (v.tguid = t.tguid)
        LEFT OUTER JOIN {btr_users} u ON (u.umail = v.umail AND u.ulng = v.ulng)
        WHERE t.tguid IN (:arr_tguid)
        ORDER BY v.time DESC
    ";
    $args = array(':arr_tguid' => $arr_tguid);
    $result = $db->query($get_votes, $args);
    $arr_votes = $result->fetchAllAssoc('vid');
  }

  //get alternatives (from other languages)
  //they are the best translations (max count) from the alternative languages
  if (empty($alternative_langs)) {
    $arr_alternatives = array();
  }
  else {
    $get_alternatives = "
        SELECT DISTINCT t.sguid, t.tguid, t.lng, t.translation, t.count
        FROM (SELECT sguid, lng, MAX(count) AS max_count
	      FROM {btr_translations}
	      WHERE lng IN (:arr_lng) AND sguid IN (:arr_sguid)
	      GROUP BY sguid, lng
	      ) AS m
        INNER JOIN {btr_translations} AS t
	      ON m.sguid = t.sguid AND m.lng = t.lng AND m.max_count = t.count
        GROUP BY t.sguid, t.lng, t.count
    ";
    $args = array(':arr_lng' => $alternative_langs, ':arr_sguid' => $arr_sguid);
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
 * Return a string (and its translations) for the given $sguid and $lng.
 * return array($string, $translations)
 */
function btr_get_string_and_translations($sguid, $lng) {
  $db = $GLOBALS['btr_db'];
  $query = $db->select('btr_strings', 's')
    ->fields('s', array('sguid'))
    ->where('s.sguid = :sguid', array(':sguid' => $sguid));
  $strings = btr_get_query_strings($query, $lng);

  $string = $strings[$sguid]->string;
  $translations = array();
  foreach ($strings[$sguid]->translations as $tguid => $obj_translation) {
    $translations[] = $obj_translation->translation;
  }

  return array($string, $translations);
}
