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
 * Search strings and translations using various filters.
 */
function btrClient_search() {

  // Add the the CSS and JS files.
  drupal_add_css(drupal_get_path('module', 'btrClient') . '/editor/editor.css');
  drupal_add_js(drupal_get_path('module', 'btrClient') . '/editor/jquery.worddiff.js');
  drupal_add_js(drupal_get_path('module', 'btrClient') . '/editor/editor.js');

  // Build the filter from the GET request parameters.
  $filter = btrClient_build_filter();
  //dpm($filter, '$filter');  //debug

  // Add RTL style if the current language's direction is RTL
  $lng = $filter['lng'];
  $languages = btr_get_languages();
  if ($languages[$lng]['direction'] == LANGUAGE_RTL) {
    drupal_add_css(drupal_get_path('module', 'btrClient') . '/editor-rtl.css');
  }

  /*
  // Add missing breadcrumb.
  drupal_set_breadcrumb(
    array(
      l(t('Home'), NULL),
      l(t('Translations'), 'translations'),
    )
  );
  */

  // Set the title.
  drupal_set_title(t('Search Translations'));

  // Add the filter form.
  $output = array(
    drupal_get_form('btrClient_filter_form', $filter)
  );

  // Get the strings that match the filter and the corresponding translations.
  $strings = btr_get_search_results($filter, $lng);
  $strings = json_decode(json_encode($strings), true);

  // Output the strings.
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
