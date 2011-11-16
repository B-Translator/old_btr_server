<?php
/**
 * @file
 *   Translation view and editing pages for localization community.
 */

/**
 * Include utility and theme functions.
 */
require_once dirname(__FILE__) . '/utility_functions.inc';
require_once dirname(__FILE__) . '/search_filter.inc';
require_once dirname(__FILE__) . '/search_query.inc';
require_once dirname(__FILE__) . '/form_functions.inc';
require_once dirname(__FILE__) . '/theme_functions.inc';
require_once dirname(__FILE__) . '/ajax_callbacks.inc';


/**
 * Menu callback: translation/search
 * Search phrases and translations using various filters.
 */
function l10n_suggestions_search() {

  // Add the the CSS and JS files.
  drupal_add_css(drupal_get_path('module', 'l10n_suggestions') . '/editor/editor.css');
  drupal_add_js(drupal_get_path('module', 'l10n_suggestions') . '/editor/jquery.worddiff.js');
  drupal_add_js(drupal_get_path('module', 'l10n_suggestions') . '/editor/editor.js');

  // Build the filter from the GET request parameters.
  $filter = l10n_suggestions_build_filter();
  //dpm($filter, '$filter');  //debug

  // Add RTL style if the current language's direction is RTL
  $lng = $filter['lng'];
  $languages = l10n_suggestions_get_languages();
  if ($languages[$lng]['direction'] == LANGUAGE_RTL) {
    drupal_add_css(drupal_get_path('module', 'l10n_suggestions') . '/editor-rtl.css');
  }

  // Add missing breadcrumb.
  drupal_set_breadcrumb(
    array(
      l(t('Home'), NULL),
      l(t('Search Translations'), 'translation/search'),
    )
  );

  // Add the filter form.
  $output = array(
    drupal_get_form('l10n_suggestions_filter_form', $filter)
  );

  // Get a query for selecting strings that match the filter.
  $query = l10n_suggestions_build_query($filter);
  if (!$query) {
    drupal_set_message(t('Filter is empty. Put something on the filter options.'));
    return $output;
  }
  //dpq($query);  //debug

  // Get the strings selected by the filter and the corresponding translations.
  $strings = _l10n_suggestions_get_strings($query, $lng);

  // Output the strings.
  if (empty($strings)) {
    drupal_set_message(t('No strings found. Try adjusting the filter options.'));
  }
  else {
    dpm($strings, '$strings');  //debug
    $output[] = drupal_get_form('l10n_suggestions_translate_form', $strings, $lng);
  }

  //dpm($output[1], 'translate_form');  //debug
  return $output;
}

/**
 * Get the strings selected by the filter and the corresponding translations.
 * The query returns the fields 'pid' and 'score' (ordered by the score desc).
 * Another query is built and run, in order to fetch the other details of the
 * strings and the corresponding translations.
 *
 * @param $query
 *   The query built from the filter parameters.
 * @return
 *   An array of strings, where each string is an associative array,
 *   with translations as nested associative arrays.
 */
function _l10n_suggestions_get_strings($filter_query, $lng) {
  //get the pid-s of the strings that are selected by the query
  $ordered_arr_pids = $filter_query->execute()->fetchAllAssoc('pid', PDO::FETCH_ASSOC);
  if (empty($ordered_arr_pids))  return array();
  $arr_pids = array_keys($ordered_arr_pids);

  //the query for retriving the strings and translations
  $get_selected_strings =
    " SELECT p.pid, p.phrase, hex(p.hash) AS p_hash,
             t.tid, t.lng, t.translation, hex(t.hash) AS t_hash,
             t.time_entered, t.uid_entered, u.name AS username, t.vcount
      FROM {l10n_suggestions_phrases} p
      LEFT OUTER JOIN {l10n_suggestions_translations} t ON (p.pid = t.pid)
      LEFT OUTER JOIN {users} u ON u.uid = t.uid_entered
      WHERE (t.lng = :lng OR t.lng IS NULL)
        AND p.pid IN (:pids)
      ORDER BY p.pid ASC, t.vcount DESC";

  //run the query and get the records
  $result = db_query($get_selected_strings, array(':lng' => $lng, ':pids' => $arr_pids));
  $arr_recs = $result->fetchAll();

  //convert them to a structured associative array, indexed by pid
  $arr_strings = l10n_suggestions_convert_to_hierarchical_array($arr_recs);

  //put them in the order returned by the filter query
  foreach ($ordered_arr_pids as $pid => $value) {
    $ordered_arr_strings[$pid] = $arr_strings[$pid];
  }

  return $ordered_arr_strings;
}

?>