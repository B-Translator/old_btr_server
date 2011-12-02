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
    // permissions to submit votes and suggestions.
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
  foreach ($strings as $sid => $string) {
    $form['strings'][$sid] = _l10n_suggestions_translate_form_item($form_state, $string, $lng);
  }

  dpm($form, '$form');  //debug
  return $form;
}

/**
 * Creates the form fragment for a source string and its translations.
 */
function _l10n_suggestions_translate_form_item(&$form_state, $string, $lng) {

  $string_unpacked = $string->string;
  $string->string = l10n_suggestions_unpack_string($string->string);

  $form = array(
    '#string' => $string,
    '#langcode' => $lng,
    'source' => array(
      'string' => array('#markup' => _l10n_suggestions_translate_render_textarray($string->string)),
    ),
  );

  if (user_access('submit suggestions')) {
    $form['source']['edit'] = array(
      '#markup' => t('Translate'),
      '#prefix' => '<label title="' . t('Translate') . '">',
      '#suffix' => '</label>',
    );
  }

  // Add alternative strings (in other languages).
  /*******
   * TODO: Improve alternatives in other languages.
  $arr_items = array();
  foreach ($string->alternatives as $langcode => $string) {
    $string = l10n_suggestions_unpack_string($string);
    $rendered_string = _l10n_suggestions_translate_render_textarray($string);
    $arr_items = array(
      '#markup' => "<strong>$langcode:</strong><label class='l10n-string'>$rendered_string</label>",
    );
  }
  $form['alternatives'] = array(
    '#theme' => 'item_list',
    '#title' => t('Alternatives in other languages:'),
    '#items' => $arr_items,
    '#prefix' => '<div class="l10n-usage">',
    '#suffix' => '</div>',
  );
  */

  //---------------- Add translations. --------------------

  // Translations are stored in an array.
  $translations = $string->translations;

  // If there is no translation yet, display a visible placeholder.
  if (empty($translations)) {
    $translations['0'] = (object) array(
      'sid' => $string->sid,
      'tid' => '0',
      'lng' => $lng,
      'translation' => t('(not translated)'),
      'uid_entered' => 0,
      'votes' => array(),
    );
  }

  foreach ($translations as $tid => $translation) {
    // Add the translation to the list.
    $form[$tid] = _l10n_suggestions_translate_translation($translation, $string->sid, $lng);
  }

  // If the user may add new suggestions, display a textarea.
  if (user_access('submit suggestions')) {
    $textarea = _l10n_suggestions_translate_translation_textarea($string, $lng);
    $form[$textarea->tid] = _l10n_suggestions_translate_translation($textarea, $string->sid, $lng);
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
  $arr_translations = array_fill(0, count($string->string) > 1 ? $nplurals : 1, '');
  $translation = implode('\0', $arr_translations);

  return (object) array(
    'sid' => $string->sid,
    'tid' => 'new',
    'lng' => $lng,
    'translation' => $translation,
    'uid_entered' => $user->uid,
    'votes' => array(),
  );
}

/**
 * Creates the form fragment for a translated string.
 */
function _l10n_suggestions_translate_translation($translation, $string_sid, $lng) {
  global $user;

  $translation->translation = l10n_suggestions_unpack_string($translation->translation);

  $is_own = ($user->uid == $translation->uid_entered);
  $is_approved = in_array($user->uid, array_keys($translation->votes));
  $is_new = ($translation->tid == 'new');
  $no_translation = ($translation->tid == '0');
  $may_moderate = ($is_own ? user_access('moderate own suggestions') : user_access('moderate suggestions from others'));

  $form = array(
    '#theme' => 'l10n_suggestions_translate_translation',
    'original' => array(
      '#type' => 'value',
      '#value' => $translation,
    ),
  );

  // The 'approved' radio/checkbox is used to pick the approved (voted/liked) translation(s).
  $voting_mode = variable_get('l10n_suggestions_voting_mode', 'single');
  $type = ($voting_mode == 'single') ? 'radio' : 'checkbox';
  $form['approved'] = array(
    '#type' => $type,
    '#theme' => 'l10n_suggestions_translate_radio',
    '#theme_wrappers' => array(),
    '#title' => _l10n_suggestions_translate_render_textarray($translation->translation, $is_new ? t('(empty)') : FALSE),
    '#return_value' => $translation->tid,
    '#default_value' => $is_approved ? $translation->tid : '',
    '#disabled' => !user_access('submit votes') || $no_translation,
    '#attributes' => array('class' => array('selector')),
  );
  if ($voting_mode == 'single') {
    $form['approved']['#checked'] = $is_approved;
    $form['approved']['#parents'] = array('strings', $string_sid, 'approved');
  }

  if ($may_moderate && !$is_new && !$no_translation) {
    $form['declined'] = array(
      '#type' => 'checkbox',
      '#title' => t('Decline'),
      '#default_value' => false,
    );
  }

  if ($no_translation) {
    //nothing else to add
  }
  elseif ($is_new) {
    // Fill in with as many textareas as required to enter translation
    // for this string.
    $form['value'] = array_fill(0, count($translation->translation), array(
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
    if (isset($translation->author)) {
      $title = l10n_suggestions_translate_byline($translation->author, $translation->uid_entered, $translation->time_entered, -1, -1, FALSE);

      $form['author'] = array(
        '#markup' => $title,
        //'#prefix' => '<div class="l10n-byline"><a href="' . url('translation/details/' . $translation->tid) . '" class="l10n-more-link" title="' . t('Show full details for the translation.') . '">',
        //'#suffix' => '</a><div class="l10n-more-info"></div></div>',
      );
    }
    //TODO: Improve displaying of vote count and the voters.
    if ($translation->vcount != '0') {
      $voters = array();
      foreach ($translation->votes as $uid=>$vote) {
        $voters[] = theme('username', array('account' => (object) array('name' => $vote->name, 'uid' => $uid)));
      }
      $form['votes'] = array(
        '#type' => 'fieldset',
        '#title' => t('Number of Votes: @vcount', array('@vcount' => $translation->vcount)),
        //'#prefix' => '<div class="l10n-more-info">',
        //'#suffix' => '</div>',
        '#collapsible' => true,
        '#collapsed' => true,
        'voters' => array(
          '#markup' => implode(', ', $voters),
        ),
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


?>