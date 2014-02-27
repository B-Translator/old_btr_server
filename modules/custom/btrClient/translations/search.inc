<?php
/**
 * @file
 * Translation view and editing pages for localization community.
 */

/**
 * Include utility and theme functions.
 */
require_once(dirname(__FILE__) . '/search_form.inc');
require_once(dirname(__FILE__) . '/list/list.inc');
require_once(dirname(__FILE__) . '/utils.inc');

/**
 * Menu callback: translations/search
 *
 * Search strings and translations using various filters.
 * If the request header 'Accept: application/json' is set, then
 * the output will be in JSON, otherwise it will be an HTML page.
 * For example:
 *   curl -k -i -H 'Accept: application/json' \
 *        'https://dev.l10n.org.xx/translations/search?lng=sq&words=space'
 */
function btrClient_search() {

  // Build the filter from the GET request parameters.
  $filter = btrClient_build_filter();
  //dpm($filter, '$filter');  //debug

  // Get the strings that match the filter and the corresponding translations.
  $lng = $filter['lng'];
  $strings = btr_get_search_results($filter, $lng);

  // If the request has the header 'Accept: application/json'
  // return the output in JSON format and stop.
  if ($_SERVER['HTTP_ACCEPT'] == 'application/json') {
    drupal_add_http_header('Content-Type', 'application/json; utf-8');
    print json_encode($strings);
    exit;
  }

  // Add the the CSS and JS files.
  drupal_add_css(drupal_get_path('module', 'btrClient') . '/editor/editor.css');
  drupal_add_js(drupal_get_path('module', 'btrClient') . '/editor/jquery.worddiff.js');
  drupal_add_js(drupal_get_path('module', 'btrClient') . '/editor/editor.js');

  // Add RTL style if the current language's direction is RTL
  $languages = btr_get_languages();
  if ($languages[$lng]['direction'] == LANGUAGE_RTL) {
    drupal_add_css(drupal_get_path('module', 'btrClient') . '/editor-rtl.css');
  }

  // Set the title.
  drupal_set_title(t('Search Translations'));

  // Add the filter form.
  $output = array(
    drupal_get_form('btrClient_filter_form', $filter)
  );

  // Output the strings.
  $strings = json_decode(json_encode($strings), true);
  if (empty($strings)) {
    drupal_set_message(t('No strings found. Try adjusting the filter options.'));
  }
  else {
    //dpm($strings, '$strings');  //debug
    $output[] = drupal_get_form('btrClient_translate_form', $strings, $lng);
  }

  //dpm($output[1], 'translate_form');  //debug
  return $output;
}
