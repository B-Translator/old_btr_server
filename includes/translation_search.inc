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
  dpm($filter, '$filter');  //debug

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

  // Get an array of strings and translations.
  $strings = array();
  $query = l10n_suggestions_build_query($filter);
  if ($query) dpq($query);  //debug
  if ($query) {
    $arr_recs = $query->execute()->fetchAll();
    $strings = l10n_suggestions_convert_to_hierarchical_array($arr_recs);;
    //dpm($strings, '$strings');  //debug
  }

  // Output the actual strings.
  if (empty($strings)) {
    drupal_set_message(t('No strings found. Try adjusting the filter options.'));
  }
  else {
    $output[] = drupal_get_form('l10n_suggestions_translate_form', $filter, $strings);
  }

  return $output;
}


// = Translation form building =================================================


/**
 * Form callback: List translations and suggestions.
 *
 * @param $form_state
 *   The form state array.
 * @param $filter
 *   An array of filters applied to the strings.
 * @param $strings
 *   The strings to render.
 */
function l10n_suggestions_translate_form($form, &$form_state, $filter, $strings) {
  $pager = theme('pager', array('tags' => NULL, 'element' => 0));

  // The form will show but the submit buttons will only appear if the user has
  // permissions to submit suggestions. This allows the use of this form to review
  // strings in the database.
  $form = array(
    'target' => array(
      '#type' => 'value',
      '#value' => $_GET,
    ),
    'langcode' => array(
      '#type' => 'value',
      '#value' => $filter['lng'],
    ),
    'pager_top' => array(
      '#weight' => -10,
      '#markup' => $pager,
    ),
    'strings' => array(
      '#tree' => TRUE,
      '#theme' => 'l10n_suggestions_translate_table',
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save changes'),
      //'#access' => user_access('submit suggestions'),
    ),
    'pager_bottom' => array(
      '#weight' => 10,
      '#markup' => $pager,
    ),
  );

  // Fill in string values for the editor.
  foreach ($strings as $string) {
    $pid = $string['pid'];
    $form['strings'][$pid] = _l10n_suggestions_translate_form_item($form_state, $string, $filter);
  }

  dpm($form, '$form');  //debug
  return $form;
}

/**
 * Creates the form fragment for a source string.
 */
function _l10n_suggestions_translate_form_item(&$form_state, $source, $filter) {

  $source_unpacked = $source['phrase'];
  $source['phrase'] = l10n_suggestions_unpack_string($source['phrase']);

  $form = array(
    '#string' => $source,
    '#langcode' => $filter['lng'],
    /*
    'filters_match' => array(
      '#type' => 'value',
      '#value' => ($source_match = (!empty($filters['search']) && (stripos($source_unpacked, $filters['search']) !== FALSE))),
    ),
    */
    'source' => array(
      'string' => array('#markup' => _l10n_suggestions_translate_render_textarray($source['phrase'])),
    ),
  );

  /*
  if (user_access('submit suggestions')) {
    $form['source']['edit'] = array(
      '#markup' => t('Translate'),
      '#prefix' => '<label title="' . t('Translate') . '">',
      '#suffix' => '</label>',
    );
  }
  */

  //---------------- Add translations. --------------------

  $translations = $source['translations'];

  // If there is no translation yet, simulate with a visible placeholder.
  if (empty($translations)) {
    $translations[] = array('tid' => '0', 'translation' => array(t('(not translated)')));
  }

  foreach ($translations as $translation) {
    $translation['translation'] = l10n_suggestions_unpack_string($translation['translation']);
    // Add the translation to the list.
    $tid = $translation['tid'];
    $form[$tid] = _l10n_suggestions_translate_translation($form_state, $translation, $source, $filter, $source_match);
  }

  /*
  // If the user may add new suggestions, display a textarea.
  if (user_access('submit suggestions')) {
    $textarea = _l10n_suggestions_translate_translation_textarea($source, $language->plurals);
    $form[$textarea['tid']] = _l10n_suggestions_translate_translation($form_state, $textarea, $source, $filter, $source_match);
  }
  */

  return $form;
}

/**
 * Build mock object for new textarea.
 */
function _l10n_suggestions_translate_translation_textarea($source, $nplurals) {
  global $user;

  return array(
    'pid' => $source['pid'],
    'tid' => 'new',
    // Fill in with as many items as required. If the source was plural, we
    // need to fill in with a number adequate for this language.
    'translation' => array_fill(0, count($source->value) > 1 ? $nplurals : 1, ''),
    'is_active' => '1',
    //'is_suggestion' => '1',
    'uid_entered' => $user->uid,
  );
}

/**
 * Creates the form fragment for a translated string.
 */
function _l10n_suggestions_translate_translation(&$form_state, $string, $source, $filter, $source_match) {
  global $user;

  $is_own = ($user->uid == $string['uid_entered']);
  //$is_active = $string->is_active && !$string->is_suggestion;
  $is_new = ($string['tid'] == 'new');
  $may_moderate = ($is_own ? user_access('moderate own suggestions') : user_access('moderate suggestions from others'));

  // This string is a match if it was data from the database and was entered by
  // the searched user or its text included the searched portion.
  $filters_matched = array();
  /*
  $filters_to_match = 0;
  if ((int) $string['tid'] > 0) {
    // If we had a real tid for this, it has a uid_entered and translation loaded.
    if (!empty($filters['author'])) {
      $filters_matched[] = $string->uid_entered == $filters['author']->uid;
      $filters_to_match++;
    }
    if (!empty($filters['search'])) {
      // Search is matched if the source matched the search and the translation
      // matched the user or the translation matched both.
      $filters_matched[] = (!empty($filters['author']) && $source_match) || (stripos(l10n_suggestions_pack_string($string->translation), $filters['search']) !== FALSE);
      $filters_to_match++;
    }
    $filters_matched = array_filter($filters_matched);
  }
  */

  $form = array(
    '#theme' => 'l10n_suggestions_translate_translation',
    'original' => array(
      '#type' => 'value',
      '#value' => $string,
    ),
    'filters_match' => array(
      '#type' => 'value',
      '#value' => ($filters_to_match > 0) && (count($filters_matched) == $filters_to_match),
    ),
  );

  // Active radio box is used to pick the approved translation.
  $form['active'] = array(
    '#type' => 'radio',
    '#theme' => 'l10n_suggestions_translate_radio',
    '#theme_wrappers' => array(),
    '#title' => _l10n_suggestions_translate_render_textarray($string['translation'], $is_new ? t('(empty)') : FALSE),
    '#return_value' => $string['tid'],
    '#default_value' => $is_active ? $string['tid'] : NULL,
    '#parents' => array('strings', $source['pid'], 'active'),
    // Let a moderator roll back to the current translation even if they
    // would otherwise not have permission to approve such a string.
    '#disabled' => !$may_moderate && !$is_active,
    '#attributes' => array('class' => array('selector')),
  );

  if ($string['tid']) {
    if ($may_moderate && $string['tid'] != 'new') {
      $form['declined'] = array(
        '#type' => 'checkbox',
        '#title' => t('Decline'),
        '#default_value' => !($string['is_active'] || $string['is_suggestion']),
      );
    }
    if ($string['tid'] == 'new') {
      // Fill in with as many textareas as required to enter translation
      // for this string.
      $form['value'] = array_fill(0, count($string->translation), array(
                         '#type' => 'textarea',
                         '#cols' => 60,
                         '#rows' => 3,
                         '#default_value' => t('<New translation>'),
                       ));
    }
    else {
      if (user_access('submit suggestions')) {
        $form['edit'] = array(
          '#markup' => t('Edit a copy'),
          '#prefix' => '<label title="' . t('Edit a copy') . '">',
          '#suffix' => '</label>',
        );
      }
      if (isset($string['username'])) {
        $title = l10n_suggestions_translate_byline($string['username'], $string['uid_entered'], $string['time_entered'], -1, -1, FALSE);

        $form['author'] = array(
          '#markup' => $title,
          '#prefix' => '<div class="l10n-byline"><a href="' . url('translate/translation-details/' . $string['tid']) . '" class="l10n-more-link" title="' . t('Show full history for translation.') . '">',
          '#suffix' => '</a><div class="l10n-more-info"></div></div>',
        );
      }
    }
  }
  return $form;
}

// = Translation form submission ===============================================

/**
 * Form submit callback for l10n_suggestions_translate_form().
 *
 * @see l10n_suggestions_translate_form().
 */
function l10n_suggestions_translate_form_submit($form, &$form_state) {
  global $user;

  $lng = $form_state['values']['lng'];

  // Iterate outer structure built in l10n_suggestions_translate_form().
  foreach ($form_state['values']['strings'] as $sid => $string) {

    // Iterate inner structure built in _l10n_suggestions_translate_form_item().
    // Form items have numeric $tid values and other keys here.
    foreach ($string as $tid => $options) {

      // Store new suggestion.
      $empty_values = 0;
      // $options['value'] is the result of (a series of) textareas.
      if (isset($options['value']) && is_array($options['value'])) {
        foreach ($options['value'] as $key => $value) {
          if ($value === t('<New translation>')) {
            $options['value'] = '';
            $empty_values++;
          }
        }
        // If we had value in any of the textareas, add new suggestion.
        if ($tid === 'new' && count($options['value']) > $empty_values) {
          $tid = l10n_suggestions_add_suggestion($sid, l10n_suggestions_pack_string($options['value']), $lng, $user->uid, $user->uid, L10N_SERVER_MEDIUM_WEB);
          if ($tid) {
            if ($string['active'] === 'new') {
              // This new string was selected to be approved, so remember $tid
              // for later, so we can save this as an approved translation.
              $string['active'] = $tid;
              l10n_suggestions_counter(L10N_COUNT_ADDED);
            }
            else {
              l10n_suggestions_counter(L10N_COUNT_SUGGESTED);
            }
          }
          elseif ($tid === FALSE) {
            // We found this as an active string already in the DB.
            l10n_suggestions_counter(L10N_COUNT_DUPLICATE);
          }
        }
      }

      if (is_numeric($tid) && $tid > 0) {
        if ($tid == $string['active']) {
          if ($options['original']->is_suggestion) {
            // $tid is a suggestion that was made active.
            l10n_suggestions_approve_string($lng, $sid, $tid);
            l10n_suggestions_counter(L10N_COUNT_APPROVED);
          }
        }
        elseif (!empty($options['declined'])) {
          // The decline checkbox for this suggestion was checked.
          l10n_suggestions_counter($options['original']->is_suggestion ? L10N_COUNT_SUGGESTION_DECLINED : L10N_COUNT_DECLINED);
          l10n_suggestions_decline_string($lng, $sid, $tid, $user->uid);
        }
      }
    }
  }

  // Tell the user what happened.
  l10n_suggestions_update_message();

  // Keep existing filters and other query arguments on form submission.
  $redirect_args = $form_state['values']['target'];
  unset($redirect_args['q']);
  $form_state['redirect'] = array($form_state['values']['target']['q'], array('query' => $redirect_args));
}

?>