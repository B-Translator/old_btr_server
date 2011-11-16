<?php
/**
 * Utility functions that are common for all the pages.
 */

/**
 * Returns an array of languages and their details.
 */
function l10n_suggestions_get_languages() {

  $arr_langs = array(
    'fr' => array(
      'code' => 'fr',
      'name' => 'French',
      'encoding' => 'latin1',
      'direction' => LANGUAGE_LTR,
      'plurals' => 2,
    ),
    'sq' => array(
      'code' => 'sq',
      'name' => 'Albanian',
      'encoding' => 'latin1',
      'direction' => LANGUAGE_LTR,
      'plurals' => 2,
    ),
  );

  return $arr_langs;
}

/**
 * Arrange the string/translation data returned from the DB
 * in another structure of arrays.
 *
 * @param $records
 *   An array of records, which are the query results
 *   returned from the DB (ordered by pid).
 *
 * @return
 *   A hierarchical associative array of strings and the corresponding
 *   translations.
 */
function l10n_suggestions_convert_to_hierarchical_array($records) {
  $arr_strings = array();
  $pid = '';
  foreach ($records as $rec) {
    if ($rec->pid != $pid) {
      $pid = $rec->pid;
      $arr_strings[$pid] = array(
        'pid' => $rec->pid,
        'phrase' => $rec->phrase,
        'p_hash' => $rec->p_hash,
        'translations' => array(),
      );
    }
    $tid = is_null($rec->tid) ? '0' : $rec->tid;
    $arr_strings[$pid]['translations'][$tid] = array(
      'tid' => $tid,
      'lng' => $rec->lng,
      'translation' => $rec->translation,
      't_hash' => $rec->t_hash,
      'time_entered' => $rec->time_entered,
      'uid_entered' => $rec->uid_entered,
      'username' => $rec->username,
      'vcount' => $rec->vcount,
    );
  }
  return $arr_strings;
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
  return implode("\0", $strings);
}

function l10n_suggestions_get_string_hash($l10n_string) {
  $l10n_string = preg_replace('/^ +/', '', $l10n_string);
  $l10n_string = preg_replace('/ +$/', '', $l10n_string);
  $l10n_string = sha1($l10n_string);
  return $l10n_string;
}

?>