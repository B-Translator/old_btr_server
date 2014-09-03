<?php
/**
 * @file
 * Function: search_build_filter()
 */

namespace BTranslator;
use \btr;

/**
 * Build the filter data from the given params.
 *
 * Check and sanize the data, and put default values where missing.
 *
 * @param $params
 *   Assoc array with filter parameters.
 *
 * @return
 *   Assoc array with filter data.
 */
function search_build_filter($params) {
  //get language
  $filter['lng'] = $params['lng'];

  //number of results to be returned
  $limit = isset($params['limit']) ? (int)trim($params['limit']) : 5;
  if ($limit < 5)  $limit = 5;
  if ($limit > 50) $limit = 50;
  $filter['limit'] = $limit;

  //search can be done either by similarity of l10n strings (natural search),
  //or by matching words according to a certain logic (boolean search);
  //search can be performed either on l10n strings or on the translations
  $search_mode_options = array(
    'natural-strings',
    'natural-translations',
    'boolean-strings',
    'boolean-translations',
  );
  $mode = isset($params['mode']) ? $params['mode'] : '';
  $filter['mode'] = in_array($mode, $search_mode_options) ? $mode : 'natural-strings';

  // if no searching words are given but there is a sguid in $params
  // search for that string (find strings similar to that one)
  $filter['words'] = isset($params['words']) ? $params['words'] : '';
  if ($filter['words'] == '' and isset($params['sguid'])) {
    $string = btr_get_string($params['sguid']);
    if ($string) {
      $filter['words'] = $string;
    }
  }

  //searching can be limited only to certain projects and/or origins
  $filter['project'] = isset($params['project']) ? trim($params['project']) : '';
  $filter['origin'] = isset($params['origin']) ? trim($params['origin']) : '';

  //limit search only to the strings touched (translated or voted) by the current user
  $filter['only_mine'] = isset($params['only_mine']) && (int)$params['only_mine'] ? 1 : 0;

  //limit search by the editing users (used by admins)
  $filter['translated_by'] = isset($params['translated_by']) ? trim($params['translated_by']) : '';
  $filter['voted_by'] = isset($params['voted_by']) ? trim($params['voted_by']) : '';

  //limit by date of string, translation or voting (used by admins)
  $date_filter_options = array('strings', 'translations', 'votes');
  $date_filter = isset($params['date_filter']) ? trim($params['date_filter']) : '';
  $filter['date_filter'] = in_array($date_filter, $date_filter_options) ? $date_filter : 'translations';

  //from_date
  $filter['from_date'] = isset($params['from_date']) ? trim($params['from_date']) : '';

  //to_date
  $filter['to_date'] = isset($params['to_date']) ? trim($params['to_date']) : '';

  return $filter;
}
