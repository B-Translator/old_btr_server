<?php
/**
 * @file
 *   Functions specific to the menu path: translations/vote .
 */

/**
 * Include utility and theme functions.
 */
require_once(dirname(__FILE__) . '/list/list.inc');
require_once(dirname(__FILE__) . '/utils.inc');

/**
 * Menu callback: translations/vote
 * Vote the best translation for a string, or suggest a better translation.
 */
function l10n_suggestions_vote() {

  // TODO: Get the translation language from the user settings.
  $lng = 'sq';

  // Add the the CSS and JS files.
  drupal_add_css(drupal_get_path('module', 'l10n_suggestions') . '/editor/editor.css');
  drupal_add_js(drupal_get_path('module', 'l10n_suggestions') . '/editor/jquery.worddiff.js');
  drupal_add_js(drupal_get_path('module', 'l10n_suggestions') . '/editor/editor.js');

  //get languages and language codes
  $languages = l10n_suggestions_get_languages();
  $lng_codes = array_keys($languages);

  // Add RTL style if the current language's direction is RTL
  if ($languages[$lng]['direction'] == LANGUAGE_RTL) {
    drupal_add_css(drupal_get_path('module', 'l10n_suggestions') . '/editor-rtl.css');
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
  drupal_set_title(t('Vote Translations'));

  // Get the sguid of a random string.
  $sguid = l10n_suggestions_get_random_sguid();

  // Get the matching string and its translations.
  $query = db_select('l10n_suggestions_strings', 's')
    ->fields('s', array('sguid'))
    ->where('s.sguid = :sguid', array(':sguid' => $sguid));
  $strings = l10n_suggestions_get_strings($query, $lng);
  //if ($strings) dpm($strings[0]);  //debug

  // Output the string and its translations.
  $output = drupal_get_form('l10n_suggestions_translate_form', $strings, $lng);

  return $output;

}

/**
 * Return a random sguid from the strings that should be voted.
 */
function l10n_suggestions_get_random_sguid() {

  // Condition for selecting projects
  // from which to get a random string.
  $where = "(origin='KDE' AND project='kturtle')"
         . " OR (origin='ubuntu' AND project='pingus')";

  // Get the total number of strings from which we can choose.
  $sql_count = "
    SELECT COUNT(*) AS number_of_strings
    FROM (SELECT pid FROM l10n_suggestions_projects WHERE $where) p
    LEFT JOIN l10n_suggestions_locations l ON (l.pid = p.pid)
    LEFT JOIN l10n_suggestions_strings s ON (s.sguid = l.sguid)
  ";
  $nr_strings = db_query($sql_count)->fetchField();

  // Get a random row number.
  $row_number = rand(0, $nr_strings - 1);

  // Get the sguid of the random row.
  $sql_get_sguid = "
    SELECT s.sguid
    FROM (SELECT pid FROM l10n_suggestions_projects WHERE $where) p
    LEFT JOIN l10n_suggestions_locations l ON (l.pid = p.pid)
    LEFT JOIN l10n_suggestions_strings s ON (s.sguid = l.sguid)
    LIMIT $row_number, 1
  ";
  $random_sguid = db_query($sql_get_sguid)->fetchField();

  // Save it in the session.
  $_SESSION['random_sguid'] = $random_sguid;

  return $random_sguid;
}

?>
