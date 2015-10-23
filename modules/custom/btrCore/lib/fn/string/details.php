<?php
/**
 * @file
 * Function: string_details()
 */

namespace BTranslator;
use \btr;

/**
 * Get the details of strings, translations and votes.
 *
 * @param $filter_query
 *   A db_select query object that returns the strings that should be
 *   extracted.
 *
 * @param $lng
 *   Language code of the translations.
 *
 * @param $alternative_langs
 *   Array of alternative (auxiliary) language codes. These will
 *   return translations of other languages, in case that the
 *   translator is not quite familiar with English or needs some help
 *   from another language.
 *
 * @return
 *   An array of strings, translations and votes, where each string
 *   is an associative array, with translations and votes as nested
 *   associative arrays.
 */
function string_details($filter_query, $lng, $alternative_langs = array()) {
  // Get the IDs of the strings that are returned by the filter query.
  $assoc_arr_sguid = $filter_query->execute()->fetchAllAssoc('sguid');
  if (empty($assoc_arr_sguid))  return array();
  $arr_sguid = array_keys($assoc_arr_sguid);

  // Get strings.
  $arr_strings = btr::db_query(
    'SELECT sguid, string FROM {btr_strings} WHERE sguid IN (:arr_sguid)',
    array(':arr_sguid' => $arr_sguid)
  )->fetchAllAssoc('sguid');

  // Get translations.
  $arr_translations = btr::db_query(
    'SELECT s.sguid, t.tguid, t.lng, t.translation,
            t.time, u.name AS author, u.umail, u.ulng, u.uid, t.count
     FROM {btr_strings} s
     JOIN {btr_translations} t ON (s.sguid = t.sguid)
     LEFT JOIN {btr_users} u ON (u.umail = t.umail AND u.ulng = t.ulng)
     WHERE (t.lng = :lng) AND s.sguid IN (:arr_sguid)
     ORDER BY t.count DESC',
    array(':lng' => $lng, ':arr_sguid' => $arr_sguid)
  )->fetchAllAssoc('tguid');

  // Get votes.
  $arr_tguid = array_keys($arr_translations);
  if (empty($arr_tguid)) {
    $arr_votes = array();
  }
  else {
    $arr_votes = btr::db_query(
      'SELECT t.tguid, v.vid, u.name, u.umail, u.ulng, u.uid, v.time
       FROM {btr_translations} t
       JOIN {btr_votes} v ON (v.tguid = t.tguid)
       JOIN {btr_users} u ON (u.umail = v.umail AND u.ulng = v.ulng)
       WHERE t.tguid IN (:arr_tguid)
       ORDER BY v.time DESC',
      array(':arr_tguid' => $arr_tguid)
    )->fetchAllAssoc('vid');
  }

  // Get alternatives (from other languages). They are the best
  // translations (max count) from the alternative languages.
  if (empty($alternative_langs)) {
    $arr_alternatives = array();
  }
  else {
    $arr_alternatives = btr::db_query(
      'SELECT DISTINCT t.sguid, t.tguid, t.lng, t.translation, t.count
       FROM (SELECT sguid, lng, MAX(count) AS max_count
	     FROM {btr_translations}
	     WHERE lng IN (:arr_lng) AND sguid IN (:arr_sguid)
	     GROUP BY sguid, lng
	     ) AS m
       INNER JOIN {btr_translations} AS t
	     ON (m.sguid = t.sguid AND m.lng = t.lng AND m.max_count = t.count)
       GROUP BY t.sguid, t.lng, t.count',
      array(
        ':arr_lng' => $alternative_langs,
        ':arr_sguid' => $arr_sguid,
      )
    )->fetchAllAssoc('tguid');
  }

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
  $strings = array();
  foreach ($arr_sguid as $sguid) {
    $string = $arr_strings[$sguid];
    if (!isset($string->alternatives)) $string->alternatives = array();
    if (!isset($string->translations)) $string->translations = array();
    $string->translations = array_values($string->translations);
    $strings[] = $string;
  }

  return $strings;
}
