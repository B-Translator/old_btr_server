<?php
/**
 * @file
 *   Translation view and editing pages for localization community.
 */

/**
 * Include utility and theme functions.
 */
require_once dirname(__FILE__) . '/includes/utility_functions.inc';
require_once dirname(__FILE__) . '/includes/theme_functions.inc';
require_once dirname(__FILE__) . '/includes/ajax_callbacks.inc';


/**
 * Menu callback: translation/search
 * Search phrases and translations using various filters.
 */
function l10n_suggestions_search($lng =NULL, $string_hash =NULL) {
  drupal_add_css(drupal_get_path('module', 'l10n_suggestions') . '/editor/editor.css');
  drupal_add_js(drupal_get_path('module', 'l10n_suggestions') . '/editor/jquery.worddiff.js');
  drupal_add_js(drupal_get_path('module', 'l10n_suggestions') . '/editor/editor.js');

  $filter = l10n_suggestions_build_filter($lng, $string_hash);
  $strings = l10n_suggestions_get_strings($filter);
  $arr_strings = l10n_suggestions_convert_to_hierarchical_array($strings);
  if (empty($arr_strings)) dpm('no strings'); else dpm($arr_strings);  //debug

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
      l(t('Get Translation'), 'translation/get'),
    )
  );

  // Add the filter form.
  $output = array(
    drupal_get_form('l10n_suggestions_filter_form', $filter)
  );

  // Output the actual strings.
  if (empty($strings)) {
    drupal_set_message(t('No strings found. Try adjusting the filter options.'));
  }
  else {
    $output[] = drupal_get_form('l10n_suggestions_translate_form', $filter, $arr_strings);
  }

  return $output;
}

// = Filter form handling ======================================================

/**
 * Check and sanitize arguments and build the filter array.
 *
 * @param $lng
 *   The language code given in the path (translation/get/lng/hash).
 * @param $string_hash
 *   The string hash given in the path (translation/get/lng/hash).
 */
function l10n_suggestions_build_filter($lng, $string_hash) {

  //if $string_hash is given in the path, then we try to make an exact match
  if ($string_hash != NULL) {
    $filter['exact_match'] = true;
    $filter['string_hash'] = $string_hash;
    //$lng is given in the path as well
    $filter['lng'] = in_array($lng, array('sq','fr')) ? $lng : 'sq';
  }
  else {
    $params = $_REQUEST;
    //get filter values from $params
    $filter['exact_match'] = isset($params['exact_match']) && in_array($params['exact_match'], array('true', 'yes','1')) ? true : false;
    $filter['lng'] = isset($params['lng']) && in_array($params['lng'], array('sq', 'fr')) ? $params['lng'] : 'sq';
    $FILTER['l10n_string'] = isset($params['l10n_string']) ? $params['l10n_string'] : '';
    $filter['project'] = isset($params['project']) ? trim($params['project']) : '';
    $filter['limit'] = (isset($params['limit']) && in_array($params['limit'], array(5, 10, 20, 30, 50))) ? (int) $params['limit'] : 5;
  }

  return $filter;
}

/**
 * Translation form filter.
 *
 * @param $filters
 *   Array of filter options.
 */
function l10n_suggestions_filter_form($form, &$form_state, $filters) {

  //set some initial default values
  if (empty($form_state['values'])) {
    $form_state['values'] = array(
      'l10n_string' => '',
      'exact_match' => false,
      'lng' => 'fr',
      'project' => '',
      'limit' => 5,
    );
  }

  $form = array(
    '#prefix' => '<div class="l10n-suggestions-filter clear-block">',
    '#suffix' => '</div>',
  );

  $form['lng'] = array(
    '#type' => 'select',
    '#title' => t('Translation language'),
    '#options' => array('sq'=>'Albanian', 'fr'=>'French'),
    '#default_value' => $form_state['values']['lng'],
  );

  $form['l10n_string'] = array(
    '#type' => 'textarea',
    '#title' => t('The string to be searched for'),
    '#rows' => '2',
    '#default_value' => $form_state['values']['l10n_string'],
  );

  $form['exact_match'] = array(
    '#type' => 'checkbox',
    '#title' => t('When checked, only an exact string will be matched (no similar strings).'),
    '#default_value' => $form_state['values']['exact_match'],
  );

  $form['project'] = array(
    '#type' => 'textfield',
    '#title' => t('Project'),
    '#default_value' => $form_state['values']['project'],
    '#autocomplete_path' => 'translation/project-autocomplete',
    '#size' => 20,
    '#states' => array(
      'visible' => array(
        ':input[name="exact_match"]' => array('checked' => false),
      ),
    ),
  );

  $form['limit'] = array(
    '#type' => 'select',
    '#title' => t('Limit'),
    '#options' => drupal_map_assoc(array(5, 10, 20, 30, 50)),
    '#default_value' => $form_state['values']['limit'],
    '#display_none' => $form_state['values']['limit'] == 10,
    '#states' => array(
      'visible' => array(
        ':input[name="exact_match"]' => array('checked' => false),
      ),
    ),
  );

  $form['buttons'] = array(
    '#prefix' => '<div class="filter-submit">',
    '#suffix' => '</div>',
  );
  $form['buttons']['submit'] = array(
    '#value' => t('Filter'),
    '#type' => 'submit',
  );
  $form['buttons']['reset'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="reset-link">' . l(t('Clear all filters'), 'translation/get', array('attributes' => array('class' => array('filter-exclude')))) . '</div>',
  );

  return $form;
}

/**
 * Theme function for l10n_suggestions_filter_form elements.
 */
function theme_l10n_suggestions_filter_form_element($variables) {
  $element = $variables['element'];

  // Bubble up a js-hide class to the container.
  $class = '';
  if (!empty($element['#display_none'])) {
    $class = ' js-hide';
  }
  return '<div class="filter-widget' . $class . '">' . $element['#children'] . '</div>';
}

/**
 * Submission handler for filtering form.
 */
function l10n_suggestions_filter_form_submit($form, &$form_state) {

  if ($form_state['values']['op'] == t('Reset')) {
    // Just go with the redirection flow => removes URL params.
    return;
  }

  if ($form_state['values']['op'] == t('Filter')) {
    // Build the same form again, keeping the current values
    $form_state['rebuild'] = true;
    return;
  }
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

  dpm($form);  //debug
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

// = API functions =============================================================


/**
 * Get strings that match the given filter.
 *
 * @param $filter
 *   Filter conditions that should be matched.
 *   - 'string_hash'
 *     The hash of the string to be translated.
 *   - 'l10n_string'
 *     L10n string to be looked for, either by exact match or fuzzy match.
 *   - 'exact_match'
 *     True if 'l10n_string' should be matched exactly.
 *   - 'project'
 *     Limit string searching only to the matching projects.
 *   - 'lng'
 *     Language code of the translations to be returned.
 *   - 'limit'
 *     Number of the strings to be returned (displayed) for page.
 * @return
 *   An array of string records from database.
 */
function l10n_suggestions_get_strings($filter) {

  $lng = $filter['lng'];
  $l10n_string = $filter['l10n_string'];
  $string_hash = $filter['string_hash'];

  //if l10n_string is empty, there is nothing to search for
  if (trim($l10n_string) == '') {
    return array();
  }

  //the query for an exact match is done by checking for an equal hash
  $get_string_by_hash =
    " SELECT p.pid, p.phrase, hex(p.hash) AS p_hash,
             t.tid, t.lng, t.translation, hex(t.hash) AS t_hash,
             t.time_entered, t.uid_entered, u.name AS username, t.vcount
      FROM {l10n_suggestions_phrases} p
      LEFT JOIN {l10n_suggestions_translations} t ON (p.pid = t.pid)
      LEFT OUTER JOIN {users} u ON u.uid = t.uid_entered
      WHERE p.hash = unhex(:hash) AND t.lng = :lng
      ORDER BY p.pid ASC, t.vcount DESC";

  //trying to find strings similar to $l10n_string
  $query = db_select('l10n_suggestions_phrases', 'p');
  $query->leftJoin('l10n_suggestions_translations', 't', 'p.pid = t.pid');
  $query->fields('p', array());

  return array();
  //---------- end of function -----------------

  /*
  $query = db_select('l10n_server_string', 's')->distinct();
  $query->leftJoin('l10n_server_status_flag', 'ts',
    's.sid = ts.sid AND ts.language = :language', array(':language' => $lng));
  $query->leftJoin('l10n_server_translation', 't',
    'ts.sid = t.sid AND ts.language = t.language AND t.is_active = 1');
  $query->leftJoin('users', 'u', 'u.uid = t.uid_entered');
  $query
    ->fields('s', array('sid', 'value', 'context'))
    ->fields('t', array('tid', 'language', 'translation', 'uid_entered',
        'time_entered', 'time_changed', 'is_suggestion', 'is_active'))
    ->fields('ts', array('has_suggestion', 'has_translation'));
  $query->addField('u', 'name', 'username');

  // Add sid filtering.
  if (!empty($filters['sid'])) {
    $query->condition('s.sid', $filters['sid']);
  }

  // Add submitted by condition
  if (!empty($filters['author'])) {
    $query->condition('t.uid_entered', $filters['author']->uid);
  }

  // Release restriction.
  $release = empty($filters['release']) || $filters['release'] === 'all' ? NULL : $filters['release'];
  $project = $filters['project'];
  if ($release || $project) {
    $query->innerJoin('l10n_server_line', 'l', 's.sid = l.sid');
    // If we have a release we ignore the project
    if ($release) {
      // Release restriction.
      $query->condition('l.rid', $release);
    }
    elseif ($project) {
      $query->condition('l.pid', $project->pid);
    }
  }

  // Context based filtering.
  if (isset($filters['context']) && $filters['context'] != 'all') {
    // We use 'none' for no context, so '' can be the defaut (for all contexts).
    $context = $filters['context'] == 'none' ? '' : $filters['context'];
    $query->condition('s.context', $context);
  }

  if (!empty($filters['search'])) {
    // Search in the source or target strings.
    $search = $filters['search'];
    $query->condition(db_or()
      ->condition('s.value', '%' . db_like($search) . '%', 'LIKE')
      ->condition('t.translation', '%' . db_like($search) . '%', 'LIKE'));
  }

  // We either need a pager or a full result.
  if (isset($pager)) {
    $strings = $query->extend('PagerDefault')->limit($pager)->execute();
  }
  else {
    $strings = $query->execute();
  }
  $result = array();
  foreach ($strings as $string) {
    if ($string->is_suggestion) {
      // This string is not a translation, but we need that as a "parent" to display.
      if (!$string->has_translation) {
        // No parent translation. Pretend this does not exist.
        // The display code will call for the suggestions.
        $string->translation = '';
      }
      else {
	$q = db_select('l10n_server_translation', 't');
	$q->leftJoin('users', 'u', 'u.uid = t.uid_entered');
	$q->fields('t', array('tid', 'translation', 'uid_entered', 'time_entered', 'time_changed', 'is_suggestion', 'is_active'));
	$q->addField('u', 'name', 'username');
	$q->condition('t.language',  $string->language)
	  ->condition('t.sid', $string->sid)
	  ->condition('t.is_active', 1)
	  ->condition('t.is_suggestion', 0);
	$translation = $q->execute()->fetchAssoc();

	if (!empty($translation))
	  {
	    // It does have a translation however, so let's load it, and override.
	    foreach ($translation as $key => $value) {
	      $string->$key = $value;
	    }
	  }
      }
    }
    $result[] = $string;
  }
  return $result;
  */
}

?>