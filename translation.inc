<?php
/**
 * @file
 *   Translation view and editing pages for localization community.
 */

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

/**
 * Menu callback: translation/vote
 * Vote the best translation for a phrase, or suggest a better translation.
 */
function l10n_suggestions_vote($lng =NULL, $string_hash =NULL) {
  $page = "lng='$lng' hash='$string_hash'";
  return $page;
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
 * Generate markup for an unpacked string.
 *
 * @param $textarray
 *   An array of strings as generated by l10n_suggestions_unpack_string().
 * @param $empty
 *   Specific data to include as the data to use when empty.
 */
function _l10n_suggestions_translate_render_textarray($textarray, $empty = '') {
  // data-empty is a proprietary attribute used in editor.css to be displayed when
  // starting to submit a new suggestion.
  $empty = !empty($empty) ? ' data-empty="' . check_plain($empty) . '"' : '';
  return "<span$empty>" . implode("</span><br /><span$empty>", array_map('check_plain', $textarray)) . '</span>';
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

/**
 * Generates the byline containing meta information about a string.
 */
function l10n_suggestions_translate_byline($name, $uid, $time, $medium, $type, $link_user = TRUE) {
  $params = array(
    '!author' => $uid ? ($link_user ? theme('username', array('account' => (object) array('name' => $name, 'uid' => $uid))) : check_plain($name)) : t('uknown user'),
    // Also skip handling time if uid was not specified (for decline entries
    // in the update, which have time for ordering reasons, but no uid).
    '@date' => $time && $uid ? format_date($time) : t('unknown time'),
    '@ago' => $time ? t('@time ago', array('@time' => format_interval(REQUEST_TIME - $time))) : t('no time record available'),
  );
  switch ($type) {
    case L10N_SERVER_ACTION_ADD:
      switch ($medium) {
        case L10N_SERVER_MEDIUM_IMPORT:
          return t('imported by !author <span title="@ago">on @date</span>', $params);
        case L10N_SERVER_MEDIUM_REMOTE:
          return t('remotely submitted by !author <span title="@ago">on @date</span>', $params);
        case L10N_SERVER_MEDIUM_WEB:
          return t('suggested on the web by !author <span title="@ago">on @date</span>', $params);
        case L10N_SERVER_MEDIUM_UNKNOWN:
          return t('suggested by !author <span title="@ago">on @date</span> (source unknown)', $params);
      }
      return;
    case L10N_SERVER_ACTION_READD:
      switch ($medium) {
        case L10N_SERVER_MEDIUM_IMPORT:
          return t('re-imported by !author <span title="@ago">on @date</span>', $params);
        case L10N_SERVER_MEDIUM_REMOTE:
          return t('remotely re-submitted by !author <span title="@ago">on @date</span>', $params);
        case L10N_SERVER_MEDIUM_WEB:
          return t('re-suggested on the web by !author <span title="@ago">on @date</span>', $params);
          // L10N_SERVER_MEDIUM_UNKNOWN does not apply, because we only have that
          // for backwards compatibility and L10N_SERVER_ACTION_READD did not
          // happen with data migrated (at least we did not know about it).
      }
      return;
    case L10N_SERVER_ACTION_APPROVE:
      return t('approved by !author <span title="@ago">on @date</span>', $params);
    case L10N_SERVER_ACTION_DECLINE:
      return t('declined by !author <span title="@ago">on @date</span>', $params);
    case L10N_SERVER_ACTION_DEMOTE:
      return t('demoted by !author <span title="@ago">on @date</span>', $params);
    default:
      // Default byline that work as a click-target to get more information.
      return t('by !author <span title="@ago">on @date</span>', $params);
  }
}

// = Translation form theming ==================================================

/**
 * Main theme function for translation table.
 */
function theme_l10n_suggestions_translate_table($variables) {

  $element = $variables['element'];
  $header = array(
    array(
      'data' => t('Source text'),
      'colspan' => 2,
    ),
    t('Translations'),
  );

  $rows = array();

  foreach (element_children($element) as $key) {
    $lng = $element[$key]['#langcode'];
    $hash = $element[$key]['#string']['p_hash'];
    $rows[] = array(
      array(
        'class' => array('sid'),
        'data' => l('#', "translation/get/$lng/$hash", array(), array('attributes' => array('title' => t('Direct and permanent link to this string.')))),
      ),
      array(
        'class' => array('source'),
        'data' => theme('l10n_suggestions_translate_source', array('element' => $element[$key])),
      ),
      array(
        'class' => array('translation'),
        'data' => theme('l10n_suggestions_translate_translation_list', array('element' => $element[$key])),
      ),
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('l10n-table'))));
}

/**
 * Theme function for a source cell in the translation table.
 */
function theme_l10n_suggestions_translate_source($variables) {
  $element = $variables['element'];
  $output = theme('l10n_suggestions_translate_actions', array('element' => $element['source']));
  $output .= '<label class="l10n-string' . ($element['filters_match']['#value'] ? ' filter-match' : ' filter-no-match') . '">' . drupal_render($element['source']['string']) . '</label>';
  $output .= theme('l10n_suggestions_in_context', array('source' => $element['#string']));

  $output .= '<div class="l10n-usage"><a href="' . url('translation/source-details/' . $element['#string']['pid']) . '" class="l10n-more-link" title="' . t('Show list of projects and releases where this text is used.') . '">' . t('Show related projects') . '</a><div class="l10n-more-info"></div></div>';
  return $output;
}

/**
 * Theme appropriate actions for the given string element.
 */
function theme_l10n_suggestions_translate_actions($variables) {
  $element = $variables['element'];
  $actions = '';
  foreach (array('declined', 'edit') as $type) {
    if (isset($element[$type])) {
      $actions .= '<li class="' . $type . '">' . drupal_render($element[$type]) . '</li>';
    }
  }
  if (!empty($actions)) {
    return '<ul class="actions">' . $actions . '</ul>';
  }
  else {
    return '';
  }
}

/**
 * Theme context information for source strings.
 *
 * @param $string
 *   Source string object.
 */
function theme_l10n_suggestions_in_context($variables) {
  $string = $variables['source'];
  if (!empty($string->context)) {
    return '<div class="string-context">' . t('in context: @context', array('@context' => $string->context)) . '</div>';
  }
  return '';
}

/**
 * Theme a suggestion/translation.
 */
function theme_l10n_suggestions_translate_translation($variables) {
  $element = $variables['element'];
  if (!isset($element['#attributes']['class'])) {
    $element['#attributes']['class'] = array();
  }
  $element['#attributes']['class'][] = 'clearfix';
  $element['#attributes']['class'][] = 'translation';

  // Add is-selectable and is-declinable helpers for JS.
  if (!$element['active']['#disabled']) {
    $element['#attributes']['class'][] = 'is-selectable';
  }
  if (isset($element['declined'])) {
    $element['#attributes']['class'][] = 'is-declinable';
  }

  // Add information on whether this matched the filter.
  if ((int) $element['active']['#return_value'] > 0) {
    $element['#attributes']['class'][] = ($element['filters_match']['#value']) ? 'filter-match' : 'filter-no-match';
  }

  switch ($element['active']['#return_value']) {
    case 'new':
      $element['#attributes']['class'][] = 'new-translation';
      break;
    case '0':
      $element['#attributes']['class'][] = 'no-translation';
      // Fallthrough.
    default:
      if ($element['active']['#value'] !== '') {
        $element['#attributes']['class'][] = 'is-active default';
      }
  }

  $output = '<li' . drupal_attributes($element['#attributes']) . '>';
  $output .= theme('l10n_suggestions_translate_actions', array('element' => $element));
  // Add the radio box to pick the active translation.
  $output .= drupal_render($element['active']);

  if (isset($element['author'])) {
    $output .= '<div class="author">' . drupal_render($element['author']) . '</div>';
  }

  if (isset($element['value'])) {
    $output .= drupal_render($element['value']);
  }
  return $output  . '</li>';
}

/**
 * Theme a radio button to pick the active translation.
 */
function theme_l10n_suggestions_translate_radio($variables) {
  $element = $variables['element'];
  _form_set_class($element, array('form-radio'));
  $output = '<input type="radio" ';
  $output .= 'id="' . $element['#id'] . '" ';
  $output .= 'name="' . $element['#name'] . '" ';
  $output .= 'value="' . $element['#return_value'] . '" ';
  $output .= (check_plain($element['#value']) == $element['#return_value']) ? ' checked="checked" ' : ' ';
  $output .= drupal_attributes($element['#attributes']) . ' />';

  if (isset($element['#title'])) {
    $output .= '<label class="l10n-string" for="' . $element['#id'] . '">' . $element['#title'] . '</label>';
  }
  return $output;
}

/**
 * Theme a list of suggestions for a string.
 */
function theme_l10n_suggestions_translate_translation_list($variables) {
  $element = $variables['element'];
  $output = '<ul>';
  foreach (element_children($element) as $child) {
    if (is_numeric($child) || $child == 'new') {
      $output .= drupal_render($element[$child]);
    }
  }
  $output .= '</ul>';
  return $output;
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

function l10n_suggestions_get_string_hash($l10n_string) {
  $l10n_string = preg_replace('/^ +/', '', $l10n_string);
  $l10n_string = preg_replace('/ +$/', '', $l10n_string);
  $l10n_string = sha1($l10n_string);
  return $l10n_string;
}

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

  //the case of path translation/get/lng/path
  if (!empty($string_hash)) {
    $params = array(':hash' => $string_hash, ':lng' => $lng);
    $result = db_query($get_string_by_hash, $params, array('fetch' => PDO::FETCH_ASSOC));
    return $result->fetchAll();
  }

  //the case of path translation/get

  //if l10n_string is empty, there is nothing to search for
  if (trim($l10n_string) == '') {
    return array();
  }

  //when an exact match for $l10n_string is required
  if ($filter['exact_match']) {
    $hash = l10n_suggestions_get_string_hash($l10n_string);
    //$params = array(':hash' => $hash, ':lng' => $lng);
    $params = array(':hash' => '4c66f534e609ea3a6262e9e11667216892e5862a', ':lng' => $lng);
    $result = db_query($get_string_by_hash, $params, array('fetch' => PDO::FETCH_ASSOC));
    return $result->fetchAll();
  }

  //---------- the general case -----------------
  return array();

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

/**
 * Arrange the string/translation data returned from the DB
 * in another structure of arrays.
 *
 * @param $strings
 *   An array of associative arrays, which are the query results
 *   returned from the DB
 *
 * @return
 *   An array of strings (as associative arrays), where each
 *   string has an array of translations on the key 'translations'.
 *   Each translation is an associative array.
 */
function l10n_suggestions_convert_to_hierarchical_array($strings) {
  $arr_strings = array();
  $current_pid = '';
  foreach ($strings as $string) {
    extract($string);
    if ($pid != $current_pid) {
      $current_pid = $pid;
      $str = compact('pid', 'phrase', 'p_hash');
      $str['translations'] = array();
      $arr_strings[] = $str;
    }
    $translation = compact('tid', 'lng', 'translation', 't_hash',
                   'time_entered', 'uid_entered', 'username', 'vcount');
    $i = sizeof($arr_strings) - 1;
    $arr_strings[$i]['translations'][] = $translation;
  }
  return $arr_strings;
}

/**
 * Unpacks a string as retrieved from the database.
 *
 * Creates an array out of the string. If it was a single string, the array
 * will have one item. If the string was a plural string, the array will have
 * as many items as the language requires (two for source strings).
 *
 * @param $string
 *   The string with optional separation markers (NULL bytes)
 * @return
 *   An array of strings with one element for each plural form in case of
 *   a plural string, or one element in case of a regular string. This
 *  is called a $textarray elsewhere.
 */
function l10n_suggestions_unpack_string($string) {
  return explode("\0", $string);
}

/**
 * Packs a string for storage in the database.
 *
 * @param $string
 *   An array of strings.
 * @return
 *   A packed string with NULL bytes separating each string.
 */
function l10n_suggestions_pack_string($strings) {
  return implode("\0", $strings);
}

// = AJAX callbacks ============================================================

/**
 * Generate list of projects and releases of where a string appears.
 *
 * We could provide much more information (down to line numbers of files), but
 * usability should also be kept in mind. It is possible to investigate hidden
 * information sources though, like tooltips on the release titles presented.
 *
 * This callback is invoked from JavaScript and is used as an AJAX provider.
 *
 * @param $sid
 *   Source string id.
 * @param $ajax
 *   Whether the request came through AJAX, in which case no page
 *   theming should be applied. Non-AJAX support is a fallback if JS is
 *   turned off.
 */
function l10n_suggestions_string_details($sid = 0, $ajax = 0) {

  $output = '';
  if ($ajax) {
    // Prevent devel module information if doing AJAX.
    $GLOBALS['devel_shutdown'] = FALSE;
  }
  else {
    // Get data about this source string.
    $string = db_query(
      'SELECT value, context FROM {l10n_server_string} WHERE sid = :sid',
      array(':sid' => $sid)
    )->fetchObject();
    $unpacked = l10n_suggestions_unpack_string($string->value);
    $output .= '<h3>' . t('Source string') . '</h3>' . theme('item_list', array('items' => $unpacked));
    $output .= '<h3>' . (empty($string->context) ? t('Used at the following places') : t('Used at the following places in context %context', array('%context' => $string->context))) . '</h3>';
  }

  // List of project releases, where this string is used.
  $result = db_query('SELECT l.pid, p.title project_title, l.rid, r.title release_title, COUNT(l.lineno) as occurrence_count FROM {l10n_server_line} l INNER JOIN {l10n_server_project} p ON l.pid = p.pid INNER JOIN {l10n_server_release} r ON l.rid = r.rid WHERE l.sid = :sid AND p.status = 1 GROUP BY l.rid ORDER BY l.pid, l.rid', array(':sid' => $sid));

  $version_list = array();
  $project_list = array();
  $previous_project = '';
  foreach ($result as $instance) {
    $release_info = $instance->release_title . ' <span title="' . format_plural($instance->occurrence_count, 'Appears once in this release.', 'Appears @count times in this release.') . '">(' . $instance->occurrence_count . ')</span>';
    if ($instance->project_title != $previous_project) {
      if (!empty($version_list)) {
        $project_list[] = join(', ', $version_list);
      }
      $version_list = array('<em>' . $instance->project_title . ':</em> ' . $release_info);
    }
    else {
      $version_list[] = $release_info;
    }
    $previous_project = $instance->project_title;
  }
  $project_list[] = join(', ', $version_list);
  $usage_list = theme('item_list', array('items' => $project_list));
  if ($ajax) {
    print $usage_list;
    exit;
  }
  else {
    $output .= $usage_list;
    return $output;
  }
}

/**
 * Provide full history information about translation.
 *
 * @param $tid
 *   Translation id.
 * @param $ajax
 *   Whether the request came through AJAX, in which case no page
 *   theming should be applied. Non-AJAX support is a fallback if JS is
 *   turned off.
 */
function l10n_suggestions_translation_details($tid = 0, $ajax = 0) {

  // Get data about this translation.
  $string = db_query(
    'SELECT * FROM {l10n_server_translation} WHERE tid = :tid',
    array(':tid' => $tid)
  )->fetchObject();

  $output = '';
  if ($ajax) {
    // Prevent devel module information if doing AJAX.
    $GLOBALS['devel_shutdown'] = FALSE;
  }
  else {
    $unpacked = l10n_suggestions_unpack_string($string->translation);
    $output .= '<h3>' . t('Translation') . '</h3>' . theme('item_list', array('items' => $unpacked)) . '<h3>' . t('History') . '</h3>';
  }

  // List of project releases, where this string is used.
  $result = db_query('SELECT h.*, u.name FROM {l10n_server_translation_history} h INNER JOIN {users} u ON h.uid_action = u.uid WHERE tid = :tid ORDER BY time_action DESC, type_action DESC', array(':tid' => $tid));

  $uid_submitted = 0;
  $history_list = array();
  foreach ($result as $item) {
    $history_list[] = l10n_suggestions_translate_byline($item->name, $item->uid_action, $item->time_action, $item->medium_action, $item->type_action);
    if ($item->type_action == L10N_SERVER_ACTION_ADD) {
      // Remember the first uid who submitted this. This will get overwritten, and since we are going backwards in time,
      // the last value kept will be the first uid who submitted this string. We need this in case it is different to
      // the user we used for attribution, so we can display the difference to the translator/moderator.
      $uid_submitted = $item->uid_action;
    }
  }
  if (!empty($uid_submitted) && ($uid_submitted != $string->uid_entered)) {
    // Turns out the user used for attribution is different to the user used for
    // the string storage.
    // TODO Convert "user_load" to "user_load_multiple" if "$string->uid_entered" is other than a uid.
    // To return a single user object, wrap "user_load_multiple" with "array_shift" or equivalent.
    // Example: array_shift(user_load_multiple(array(), $string->uid_entered))
    $account = user_load($string->uid_entered);
    $author = theme('username', array('account' => $account));
    array_unshift($history_list, t('by !author', array('!author' => $author)));
  }
  if (count($history_list)) {
    $output .= theme('item_list', array('items' => $history_list));
  }
  if ($ajax) {
    print $output;
    exit;
  }
  else {
    return $output;
  }
}
