<?php
/**
 * @file
 *   Functions specific to the menu path: translation/get/lng/hash .
 */

/**
 * Include utility and theme functions.
 */
require_once dirname(__FILE__) . '/includes/utility_functions.inc';
require_once dirname(__FILE__) . '/includes/theme_functions.inc';
require_once dirname(__FILE__) . '/includes/ajax_callbacks.inc';


/**
 * Menu callback: translation/get/lng/hash
 * Get translation suggestions for a given phrase.
 * 'lng' and 'hash' are passed as parameters to the function.
 */
function l10n_suggestions_get($lng, $hash) {
  drupal_add_css(drupal_get_path('module', 'l10n_suggestions') . '/editor/editor.css');

  /*
  // Add RTL style if the current language's direction is RTL
  $language = l10n_suggestions_get_language($filter['lng']);
  if ($language->direction == LANGUAGE_RTL) {
    drupal_add_css(drupal_get_path('module', 'l10n_suggestions') . '/editor-rtl.css');
  }
  */

  // Add missing breadcrumb.
  drupal_set_breadcrumb(
    array(
      l(t('Home'), NULL),
      l(t('Get Translations'), 'translation/get'),
    )
  );

  // Get the matching string and its translations.
  $arr_strings = l10n_suggestions_get_translations($hash, $lng);
  dpm($arr_strings[0]);  //debug

  // If no strings were returned, display an empty message.
  if (!$arr_strings) {
    $output = array(
      '#markup' => t('No matching strings found. Try instead to search with: !search_path',
                 array('!search_path' => l('translation/search', 'translation/search')))
    );
    return $output;
  }

  // Output the string and its translations.
  $output = drupal_get_form('l10n_suggestions_translation_get_form', $arr_strings[0], $lng);

  return $output;
}


/**
 * Get the string that has a given hash, and its translations in
 * a given language.
 *
 * @param $hash
 *   The hash (sha1) of the l10n string to be returned.
 * @param $lng
 *   The language code of the translations that are to be returned.
 * @return
 *   An array of string and translation records from the database.
 */
function l10n_suggestions_get_translations($hash, $lng) {

  //check that the given language code is correct
  if ( ! in_array($lng, array('fr', 'sq')) ) {
    drupal_set_message(t("There are no translations for the language '@lng'.", array('@lng'=>$lng)), 'error');
    return false;
  }

  //get the matching string and the corresponding translations
  $get_string_by_hash =
    " SELECT p.pid, p.phrase, hex(p.hash) AS p_hash,
             t.tid, t.lng, t.translation, hex(t.hash) AS t_hash,
             t.time_entered, t.uid_entered, u.name AS username, t.vcount
      FROM {l10n_suggestions_phrases} p
      LEFT OUTER JOIN {l10n_suggestions_translations} t ON (p.pid = t.pid)
      LEFT OUTER JOIN {users} u ON u.uid = t.uid_entered
      WHERE p.hash = unhex(:hash) AND t.lng = :lng
      ORDER BY t.vcount DESC";
  //$params = array(':hash' => $hash, ':lng' => $lng);
  $params = array(':hash' => '5cead848f38540b70c048428225c04440fa4c641', ':lng' => $lng);  //debug
  $result = db_query($get_string_by_hash, $params, array('fetch' => PDO::FETCH_ASSOC));
  $arr_recs = $result->fetchAll();

  //if there are no results, display an error message and return false
  if (!$arr_recs) {
    drupal_set_message(t("No strings found with hash '@hash'.", array('@hash'=>$hash)), 'error');
    return false;
  }

  //convert the results to a hierarchical array format that is
  //more suitable for displaying and handling, and return them
  return l10n_suggestions_convert_to_hierarchical_array($arr_recs);;
}

/**
 * Form callback: List translations and suggestions.
 *
 * @param $form_state
 *   The form state array.
 * @param $string
 *   The array of the string andt its translations that are to be rendered.
 * @param $lng
 *   The language code of the translations.
 * @return
 *   A render array of the page (which actually doesn't have to be a form).
 */
function l10n_suggestions_translation_get_form($form, &$form_state, $string, $lng) {

  $string['phrase'] = l10n_suggestions_unpack_string($string['phrase']);
  $pid = $string['pid'];

  $form = array(
    'strings' => array(
      '#tree' => TRUE,
      '#theme' => 'l10n_suggestions_translate_table',
      $pid => array(
        '#string' => $string,
        '#langcode' => $lng,
        'source' => array(
          'string' => array('#markup' => _l10n_suggestions_translate_render_textarray($string['phrase'])),
        ),
      ),
    ),
  );

  //--------- Add data to the form for each translation ------------

  $translations = $string['translations'];

  // If there is no translation yet, simulate with a visible placeholder.
  if (empty($translations)) {
    $translations[] = array('tid' => '0', 'translation' => array(t('(not translated)')));
  }

  foreach ($translations as $translation) {

    $translation['translation'] = l10n_suggestions_unpack_string($translation['translation']);

    // Add the translation to the list.
    $tid = $translation['tid'];

    $form['strings'][$pid][$tid] = array(
      '#theme' => 'l10n_suggestions_translate_translation',
      'original' => array(
        '#type' => 'value',
        '#value' => $translation,
      ),
      'active' => array(
        '#type' => 'radio',
        '#theme' => 'l10n_suggestions_translate_radio',
        '#theme_wrappers' => array(),
        '#title' => _l10n_suggestions_translate_render_textarray($translation['translation'], FALSE),
        '#return_value' => $tid,
        '#default_value' => false,
        '#parents' => array('strings', $translation['pid'], 'active'),
        '#disabled' => true,
        '#attributes' => array('class' => array('selector')),
      ),
    );

    // Add the author of the translation.
    if (isset($translation['username'])) {
      $title = l10n_suggestions_translate_byline($translation['username'], $translation['uid_entered'], $translation['time_entered'], -1, -1, FALSE);

      $form['strings'][$pid][$tid]['author'] = array(
        '#markup' => $title,
        '#prefix' => '<div class="l10n-byline"><a href="' . url('translation/translation-details/' . $tid) . '" class="l10n-more-link" title="' . t('Show full history for translation.') . '">',
        '#suffix' => '</a><div class="l10n-more-info"></div></div>',
      );
    }
  }

  dpm($form);  //debug
  return $form;
}

?>