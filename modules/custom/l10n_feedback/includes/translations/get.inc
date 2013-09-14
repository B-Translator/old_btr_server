<?php
/**
 * @file
 * Functions specific to the menu path: translations/get/lng/sguid .
 */

/**
 * Include utility and theme functions.
 */
require_once(dirname(__FILE__) . '/list/list.inc');
require_once(dirname(__FILE__) . '/utils.inc');

/**
 * Menu callback: translations/get/lng/sguid
 * Get translation suggestions for a given string.
 * 'lng' and 'sguid' are passed as parameters to the function.
 */
function l10n_feedback_get($lng =NULL, $sguid =NULL) {

  // Add the the CSS and JS files.
  drupal_add_css(drupal_get_path('module', 'l10n_feedback') . '/editor/editor.css');
  drupal_add_js(drupal_get_path('module', 'l10n_feedback') . '/editor/jquery.worddiff.js');
  drupal_add_js(drupal_get_path('module', 'l10n_feedback') . '/editor/editor.js');

  //get languages and language codes
  $languages = l10n_feedback_get_languages();
  $lng_codes = array_keys($languages);

  //check the correct usage of parameters
  if ($lng==NULL or $sguid==NULL) {
    drupal_set_message(t("Missing parameters lng/sguid."), 'error');
    $output = array(
      '#markup' => t("The correct usage of this interface is: <strong>translations/get/lng/sguid</strong> , where <strong>lng</strong> is one of: <strong>!lng_codes</strong> .",
                 array(
                   '!lng_codes' => implode(', ', $lng_codes),
                 ))
      );
    return $output;
  }

  //check that the given language code is correct
  if (!in_array($lng, $lng_codes)) {
    drupal_set_message(t("There are no translations for the language '@lng'.", array('@lng' => $lng)), 'error');
    $output = array(
      '#markup' => t("The language '<strong>@lng</strong>' is not supported yet. Available languages are: <strong>@lng_codes</strong> . <br/> Try instead to search with: @search_path",
                 array(
                   '@lng' => $lng,
                   '@lng_codes' => implode(', ', $lng_codes),
                   '@search_path' => l('translations/search', 'translations/search'),
                 )),
    );
    return $output;
  }

  // Add RTL style if the current language's direction is RTL
  if ($languages[$lng]['direction'] == LANGUAGE_RTL) {
    drupal_add_css(drupal_get_path('module', 'l10n_feedback') . '/editor-rtl.css');
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
  drupal_set_title(t('Get Translations'));

  // Get the matching string and its translations.
  $query = $GLOBALS['btr_db']->select('btr_strings', 's')
    ->fields('s', array('sguid'))
    ->where('s.sguid = :sguid', array(':sguid' => $sguid));
  $strings = l10n_feedback_get_strings($query, $lng);
  //if ($strings) dpm($strings[0]);  //debug

  // If no strings were returned, display an empty message.
  if (!$strings) {
    drupal_set_message(t("No strings with GUID '<strong>@sguid</strong>' found.", array('@sguid' => $sguid)), 'error');
    $output = array(
      '#markup' => t("No strings with GUID '<strong>!sguid</strong>' found. <br/> Try instead to search with: !search_path",
                 array(
                   '!sguid' => $sguid,
                   '!search_path' => l('translations/search', 'translations/search'),
                 ))
    );
    return $output;
  }

  // Output the string and its translations.
  $output = drupal_get_form('l10n_feedback_translate_form', $strings, $lng);

  return $output;
}
