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
require_once dirname(__FILE__) . '/form_submit.inc';
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
  $strings = l10n_suggestions_get_strings($query, $lng);

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

?>