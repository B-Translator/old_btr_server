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
 *
 * If the request header 'Accept: application/json' is set, then
 * the output will be in JSON, otherwise it will be an HTML page.
 * For example:
 *   curl -k -i -H 'Accept: application/json' \
 *        'https://dev.l10n.org.xx/translations/search?lng=sq&words=space'
 */
function btrClient_search() {
  // Get the search parameters from the GET request.
  $params = btrClient_get_search_params();

  // Get the strings that match the search params.
  $result = $GLOBALS['btr']->search($params);
  $filter = $result['filter'];
  $pager = $result['pager'];
  $strings = $result['strings'];

  // If the request has the header 'Accept: application/json'
  // return the output in JSON format and stop.
  if ($_SERVER['HTTP_ACCEPT'] == 'application/json') {
    drupal_add_http_header('Content-Type', 'application/json; utf-8');
    print json_encode($strings);
    exit;
  }

  // Add the CSS and JS files.
  drupal_add_css(drupal_get_path('module', 'btrClient') . '/editor/editor.css');
  drupal_add_js(drupal_get_path('module', 'btrClient') . '/editor/jquery.worddiff.js');
  drupal_add_js(drupal_get_path('module', 'btrClient') . '/editor/editor.js');

  // Add RTL style if the current language's direction is RTL
  $languages = btrClient_get_languages();
  $lng = variable_get('btrClient_translation_lng', 'fr');
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
  if (empty($strings)) {
    drupal_set_message(t('No strings found. Try adjusting the filter options.'));
  }
  else {
    pager_default_initialize($pager['number_of_items'], $pager['items_per_page']);
    $output[] = drupal_get_form('btrClient_translate_form', $strings, $lng);
  }

  return $output;
}
