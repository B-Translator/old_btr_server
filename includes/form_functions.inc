<?php
/**
 * The function l10n_suggestions_translate_form() builds a render array
 * for the strings and their corresponding translations/suggestions.
 * The edit and submit functionality will be available only when suitable.
 */

/**
 * Form callback: List strings and the corresponding translations/suggestions.
 *
 * @param $form_state
 *   The form state array.
 * @param $string
 *   A multi-dimentional associative array of the string and the corresponding
 *   translations that are to be rendered.
 * @param $lng
 *   The language code of the translations.
 * @return
 *   A render array of the page.
 */
function l10n_suggestions_translate_form($form, &$form_state, $strings, $lng) {
  $pager = theme('pager', array('tags' => NULL, 'element' => 0));
  $form = array(
    'target' => array(
      '#type' => 'value',
      '#value' => $_GET,
    ),
    'langcode' => array(
      '#type' => 'value',
      '#value' => $lng,
    ),
    'pager_top' => array(
      '#weight' => -10,
      '#markup' => $pager,
    ),
    'strings' => array(
      '#tree' => TRUE,
      '#theme' => 'l10n_suggestions_translate_table',
    ),

    // The submit buttons will appear only when the user has
    // permissions to submit suggestions.
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save changes'),
      '#access' => user_access('submit suggestions'),
    ),

    'pager_bottom' => array(
      '#weight' => 10,
      '#markup' => $pager,
    ),
  );

  // Fill in string values for the editor.
  foreach ($strings as $string) {
    $pid = $string['pid'];
    $form['strings'][$pid] = _l10n_suggestions_translate_form_item($form_state, $string, $lng);
  }

  dpm($form, '$form');  //debug
  return $form;
}

/**
 * Creates the form fragment for a source string and its translations.
 */
function _l10n_suggestions_translate_form_item(&$form_state, $string, $lng) {

  $string_unpacked = $string['phrase'];
  $string['phrase'] = l10n_suggestions_unpack_string($string['phrase']);

  $form = array(
    '#string' => $string,
    '#langcode' => $lng,
    'source' => array(
      'string' => array('#markup' => _l10n_suggestions_translate_render_textarray($string['phrase'])),
    ),
  );

  if (user_access('submit suggestions')) {
    $form['source']['edit'] = array(
      '#markup' => t('Translate'),
      '#prefix' => '<label title="' . t('Translate') . '">',
      '#suffix' => '</label>',
    );
  }

  //---------------- Add translations. --------------------

  // Translations are stored in a sub-array of the string.
  $translations = $string['translations'];

  // If there is no translation yet, display a visible placeholder.
  if (isset($translations['0'])) {
    $translations['0']['translation'] = t('(not translated)');
  }

  foreach ($translations as $translation) {
    // Add the translation to the list.
    $tid = $translation['tid'];
    $form[$tid] = _l10n_suggestions_translate_translation($translation, $string['pid'], $lng);
  }

  // If the user may add new suggestions, display a textarea.
  if (user_access('submit suggestions')) {
    $textarea = _l10n_suggestions_translate_translation_textarea($string, $lng);
    $form[$textarea['tid']] = _l10n_suggestions_translate_translation($textarea, $string['pid'], $lng);
  }

  return $form;
}

/**
 * Build mock object for new textarea.
 */
function _l10n_suggestions_translate_translation_textarea($string, $lng) {
  global $user;

  // Fill in with as many items as required. If the source was plural, we
  // need to fill in with a number adequate for this language.
  $languages = l10n_suggestions_get_languages();
  $nplurals = $languages[$lng]['plurals'];
  $arr_translations = array_fill(0, count($string['phrase']) > 1 ? $nplurals : 1, '');
  $translation = implode('\0', $arr_translations);

  return array(
    'pid' => $string['pid'],
    'tid' => 'new',
    'translation' => $translation,
    'is_active' => '1',
    'is_suggestion' => '1',
    'uid_entered' => $user->uid,
  );
}

/**
 * Creates the form fragment for a translated string.
 */
function _l10n_suggestions_translate_translation($translation, $string_pid, $lng) {
  global $user;

  $translation['translation'] = l10n_suggestions_unpack_string($translation['translation']);

  $is_own = ($user->uid == $translation['uid_entered']);
  //$is_active = $translation->is_active && !$translation->is_suggestion;
  $is_active = user_access('submit vote');
  $is_new = ($translation['tid'] == 'new');
  $may_moderate = ($is_own ? user_access('moderate own suggestions') : user_access('moderate suggestions from others'));

  $form = array(
    '#theme' => 'l10n_suggestions_translate_translation',
    'original' => array(
      '#type' => 'value',
      '#value' => $translation,
    ),
  );

  // Active radio box is used to pick the approved translation.
  $form['active'] = array(
    '#type' => 'radio',
    '#theme' => 'l10n_suggestions_translate_radio',
    '#theme_wrappers' => array(),
    '#title' => _l10n_suggestions_translate_render_textarray($translation['translation'], $is_new ? t('(empty)') : FALSE),
    '#return_value' => $translation['tid'],
    '#default_value' => false,
    '#parents' => array('strings', $string_pid, 'active'),
    // Let a moderator roll back to the current translation even if they
    // would otherwise not have permission to approve such a string.
    '#disabled' => !$may_moderate && !$is_active,
    '#attributes' => array('class' => array('selector')),
  );

  if ($may_moderate && !$is_new) {
    $form['declined'] = array(
      '#type' => 'checkbox',
      '#title' => t('Decline'),
      /* '#default_value' => !($translation['is_active'] || $translation['is_suggestion']), */
      '#default_value' => true,
    );
  }
  if ($is_new) {
    // Fill in with as many textareas as required to enter translation
    // for this string.
    $form['value'] = array_fill(0, count($translation['translation']), array(
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
    if (isset($translation['username'])) {
      $title = l10n_suggestions_translate_byline($translation['username'], $translation['uid_entered'], $translation['time_entered'], -1, -1, FALSE);

      $form['author'] = array(
        '#markup' => $title,
        '#prefix' => '<div class="l10n-byline"><a href="' . url('translate/translation-details/' . $translation['tid']) . '" class="l10n-more-link" title="' . t('Show full history for translation.') . '">',
        '#suffix' => '</a><div class="l10n-more-info"></div></div>',
      );
    }
  }

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
 * Generates the byline containing meta information about a string.
 */
function l10n_suggestions_translate_byline($name, $uid, $time, $medium, $type, $link_user = TRUE) {
  $params = array(
    '!author' => $uid ? ($link_user ? theme('username', array('account' => (object) array('name' => $name, 'uid' => $uid))) : check_plain($name)) : t('uknown user'),
    // Also skip handling time if uid was not specified (for decline entries
    // in the update, which have time for ordering reasons, but no uid).
    '@date' => $time && $uid ? format_date(strtotime($time)) : t('unknown time'),
    '@ago' => $time ? t('@time ago', array('@time' => format_interval(REQUEST_TIME - strtotime($time)))) : t('no time record available'),
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