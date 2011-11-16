<?php
/**
 * @file
 *   Functions specific to the menu path: translation/get/lng/hash .
 */

/**
 * Include utility and theme functions.
 */
require_once dirname(__FILE__) . '/utility_functions.inc';
require_once dirname(__FILE__) . '/form_functions.inc';
require_once dirname(__FILE__) . '/theme_functions.inc';
require_once dirname(__FILE__) . '/ajax_callbacks.inc';


/**
 * Menu callback: translation/get/lng/hash
 * Get translation suggestions for a given phrase.
 * 'lng' and 'hash' are passed as parameters to the function.
 */
function l10n_suggestions_get($lng =NULL, $hash =NULL) {

  // Add the the CSS and JS files.
  drupal_add_css(drupal_get_path('module', 'l10n_suggestions') . '/editor/editor.css');
  drupal_add_js(drupal_get_path('module', 'l10n_suggestions') . '/editor/jquery.worddiff.js');
  drupal_add_js(drupal_get_path('module', 'l10n_suggestions') . '/editor/editor.js');

  //get languages and language codes
  $languages = l10n_suggestions_get_languages();
  $lng_codes = array_keys($languages);

  //check the correct usage of parameters
  if ($lng==NULL or $hash==NULL) {
    drupal_set_message(t("Missing parameters lng/hash."), 'error');
    $output = array(
      '#markup' => t("The correct usage of this interface is: <strong>translation/get/lng/hash</strong> , where <strong>lng</strong> is one of: <strong>!lng_codes</strong> .",
                 array(
                   '!lng_codes' => implode(', ', $lng_codes),
                 ))
      );
    return $output;
  }

  //check that the given language code is correct
  if (!in_array($lng, $lng_codes)) {
    drupal_set_message(t("There are no translations for the language '@lng'.", array('@lng'=>$lng)), 'error');
    $output = array(
      '#markup' => t("The language '<strong>!lng</strong>' is not supported yet. Available languages are: <strong>!lng_codes</strong> . <br/> Try instead to search with: !search_path",
                 array(
                   '!lng' => $lng,
                   '!lng_codes' => implode(', ', $lng_codes),
                   '!search_path' => l('translation/search', 'translation/search')
                 )),
    );
    return $output;
  }

  // Add CSS styles.
  drupal_add_css(drupal_get_path('module', 'l10n_suggestions') . '/editor/editor.css');

  // Add RTL style if the current language's direction is RTL
  if ($languages[$lng]['direction'] == LANGUAGE_RTL) {
    drupal_add_css(drupal_get_path('module', 'l10n_suggestions') . '/editor-rtl.css');
  }

  // Add missing breadcrumb.
  drupal_set_breadcrumb(
    array(
      l(t('Home'), NULL),
      l(t('Get Translations'), 'translation/get'),
    )
  );

  // Get the matching string and its translations.
  $strings = l10n_suggestions_get_translations($lng, $hash);
  //if ($strings) dpm($strings[0]);  //debug

  // If no strings were returned, display an empty message.
  if (!$strings) {
    drupal_set_message(t("No strings with hash '<strong>!hash</strong>' found.", array('!hash'=>$hash)), 'error');
    $output = array(
      '#markup' => t("No strings with hash '<strong>!hash</strong>' found. <br/> Try instead to search with: !search_path",
                 array(
                   '!hash' => $hash,
                   '!search_path' => l('translation/search', 'translation/search'),
                 ))
    );
    return $output;
  }

  // Output the string and its translations.
  $output = drupal_get_form('l10n_suggestions_translate_form', $strings, $lng);

  return $output;
}


/**
 * Get the string that has a given hash, and its translations in
 * a given language.
 *
 * @param $lng
 *   The language code of the translations that are to be returned.
 * @param $hash
 *   The hash (sha1) of the l10n string to be returned.
 * @return
 *   An array of string and translation records from the database.
 */
function l10n_suggestions_get_translations($lng, $hash) {

  //get the matching string and the corresponding translations
  $get_string_by_hash =
    " SELECT p.pid, p.phrase, hex(p.hash) AS p_hash,
             t.tid, t.lng, t.translation, hex(t.hash) AS t_hash,
             t.time_entered, t.uid_entered, u.name AS username, t.vcount
      FROM {l10n_suggestions_phrases} p
      LEFT OUTER JOIN {l10n_suggestions_translations} t ON (p.pid = t.pid)
      LEFT OUTER JOIN {users} u ON u.uid = t.uid_entered
      WHERE p.hash = unhex(:hash) AND (t.lng = :lng OR t.lng IS NULL)
      ORDER BY t.vcount DESC";

  $params = array(':hash' => $hash, ':lng' => $lng);
  //$params = array(':hash' => '5cead848f38540b70c048428225c04440fa4c641', ':lng' => $lng);  //debug
  $result = db_query($get_string_by_hash, $params);
  $arr_recs = $result->fetchAll();

  //if there are no results return false
  if (!$arr_recs)  return false;

  //convert the results to a hierarchical array format that is
  //more suitable for displaying and handling, and return them
  return l10n_suggestions_convert_to_hierarchical_array($arr_recs);;
}

?>