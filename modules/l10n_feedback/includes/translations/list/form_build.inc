<?php
/**
 * @file
 * The function l10n_feedback_translate_form() builds a render array
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
function l10n_feedback_translate_form($form, &$form_state, $strings, $lng) {
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
      '#theme' => 'l10n_feedback_translate_table',
      '#lng' => $lng,
    ),

    'buttons' => array(
      //'#prefix' => '<div class="filter-submit">',
      //'#suffix' => '</div>',
    ),

    'pager_bottom' => array(
      '#weight' => 10,
      '#markup' => $pager,
    ),
  );

  // don't show the Back button on the search interface
  if ( current_path() != 'translations/search' && isset($_SESSION['previous_url']) ) {
    $form['buttons']['previous'] = array(
      '#type' => 'submit',
      '#value' => t('Previous'),
    );
  }

  // The submit buttons will appear only when the user has
  // permissions to submit votes and suggestions.
  $translation_lng = variable_get('l10n_feedback_translation_lng');
  $enable_submit = ($lng==$translation_lng) && (user_access('btranslator-vote') || user_access('btranslator-suggest'));
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#access' => $enable_submit,
  );

  // don't show the Next button on the search interface
  if (current_path() != 'translations/search') {
    $form['buttons']['next'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
    );
  }

  $disqus = sizeof($strings)==1 ? 'comments' : 'link';

  // Fill in string values for the editor.
  foreach ($strings as $sguid => $string) {
    $form['strings'][$sguid] = _l10n_feedback_translate_form_item($form_state, $string, $lng);
    if ($disqus == 'comments') {

      // set the page title (no longer than 20 chars)
      $title = strip_tags(str_replace("\n", ' ', $string->string[0]));
      if (strlen($title) > 20) {
        $title = substr($title, 0, strrpos(substr($title, 0, 17), ' '));
        $title .= '...';
      }
      drupal_set_title(t('String: !string', array('!string' => $title),
          array('context' => 'set the page title')));

      // get the comment title (no longer than 50 chars)
      $title = strip_tags(str_replace("\n", ' ', $string->string[0]));
      if (strlen($title) > 50) {
        $title = substr($title, 0, strrpos(substr($title, 0, 47), ' '));
        $title .= '...';
      }
      // define the disqus form element
      $form['disqus'] = array(
        '#type' => 'disqus',
        '#disqus' => array(
          'domain' => variable_get('disqus_domain', 'dev-btranslator'),
          'status' => TRUE,
          'url' => url("translations/$lng/$sguid", array('absolute' => TRUE)),
          'title' => $title,
          'identifier' => "translations/$lng/$sguid",
          'developer' => variable_get('disqus_developer', '1'),
        ),
        '#weight' => variable_get('disqus_weight', 50),
      );
    }
    /*
      else {
      $form['strings'][$sguid]['disqus'] = array(
      '#theme' => 'links',
      '#links' => array('disqus_comments_num' => array(
      'title' => t('Comments'),
      'href' => "translations/$lng/$sguid",
      'fragment' => 'disqus_thread',
      'attributes' => array(
      // Identify the node for Disqus with the unique identifier:
      // http://docs.disqus.com/developers/universal/#comment-count
      'data-disqus-identifier' => "translations/$lng/$sguid",
      )
      )),
      '#attributes' => array(
      'class' => array('links', 'inline'),
      ),
      );
      $form['strings'][$sguid]['#attached']['js'][] = drupal_get_path('module', 'disqus') . '/disqus.js';
      $form['strings'][$sguid]['#attached']['js'][] = array(
      'data' => array('disqusComments' => "l10n-$lng"),
      'type' => 'setting',
      );

      }
    */
  }

  //dpm($form, '$form');  //debug
  return $form;
}

/**
 * Creates the form fragment for a source string and its translations.
 */
function _l10n_feedback_translate_form_item(&$form_state, $string, $lng) {

  $string_unpacked = $string->string;
  $string->string = l10n_feedback_unpack_string($string->string);

  $form = array(
    '#string' => $string,
    '#langcode' => $lng,
    'source' => array(
      'string' => array('#markup' => _l10n_feedback_translate_render_textarray($string->string)),
    ),
  );

  if (user_access('btranslator-suggest')) {
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
   $string = l10n_feedback_unpack_string($string);
   $rendered_string = _l10n_feedback_translate_render_textarray($string);
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

  foreach ($translations as $tguid => $translation) {
    // Add the translation to the list.
    $form[$tguid] = _l10n_feedback_translate_translation($translation, $string->sguid, $lng);
  }

  // If the user may add new suggestions, display a textarea.
  if (user_access('btranslator-suggest')) {
    $textarea = _l10n_feedback_translate_translation_textarea($string, $lng);
    $form[$textarea->tguid] = _l10n_feedback_translate_translation($textarea, $string->sguid, $lng);
  }

  return $form;
}

/**
 * Build mock object for new textarea.
 */
function _l10n_feedback_translate_translation_textarea($string, $lng) {
  global $user;

  // Fill in with as many items as required. If the source was plural, we
  // need to fill in with a number adequate for this language.
  $languages = l10n_feedback_get_languages();
  $nplurals = $languages[$lng]['plurals'];
  $arr_translations = array_fill(0, count($string->string) > 1 ? $nplurals : 1, '');
  $translation = implode("\0", $arr_translations);

  return (object) array(
    'sguid' => $string->sguid,
    'tguid' => 'new',
    'lng' => $lng,
    'translation' => $translation,
    'author' => NULL,
    'uid' => $user->uid,
    'count' => '0',
    'votes' => array(),
  );
}

/**
 * Creates the form fragment for a translated string.
 */
function _l10n_feedback_translate_translation($translation, $string_sguid, $lng) {

  global $user;

  $translation->translation = l10n_feedback_unpack_string($translation->translation);

  $is_own = ($user->uid && ($user->name == $translation->author));
  $is_approved = ($user->uid && in_array($user->name, array_keys($translation->votes)));
  $is_new = ($translation->tguid == 'new');
  $may_moderate = ($is_own or user_access('btranslator-resolve'));

  $form = array(
    '#theme' => 'l10n_feedback_translate_translation',
    'original' => array(
      '#type' => 'value',
      '#value' => $translation,
    ),
  );

  // The 'approved' radio/checkbox is used to pick the approved (voted/liked) translation(s).
  $voting_mode = variable_get('l10n_feedback_voting_mode', 'single');
  $type = ($voting_mode == 'single') ? 'radio' : 'checkbox';
  $form['approved'] = array(
    '#type' => $type,
    '#theme' => 'l10n_feedback_translate_radio',
    '#theme_wrappers' => array(),
    '#title' => _l10n_feedback_translate_render_textarray($translation->translation, $is_new ? t('(empty)') : FALSE),
    '#return_value' => $translation->tguid,
    '#default_value' => $is_approved ? $translation->tguid : '',
    '#disabled' => !user_access('btranslator-vote'),
    '#attributes' => array('class' => array('selector')),
  );
  if ($voting_mode == 'single') {
    $form['approved']['#checked'] = $is_approved;
    $form['approved']['#parents'] = array('strings', $string_sguid, 'approved');
  }

  if ($may_moderate && !$is_new) {
    $form['declined'] = array(
      '#type' => 'checkbox',
      '#title' => t('Decline'),
      '#default_value' => FALSE,
    );
  }

  if ($is_new) {
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
    if (user_access('btranslator-suggest')) {
      $form['edit'] = array(
        '#markup' => t('Edit a copy'),
        '#prefix' => '<label title="' . t('Edit a copy') . '">',
        '#suffix' => '</label>',
      );
    }
    if ($translation->author != NULL) {
      $title = l10n_feedback_translate_byline($translation->author, $translation->uid, $translation->time);

      $form['author'] = array(
        '#markup' => $title,
        //'#prefix' => '<div class="l10n-byline"><a href="' . url('translations/details/' . $translation->tguid) . '" class="l10n-more-link" title="' . t('Show full details for the translation.') . '">',
        //'#suffix' => '</a><div class="l10n-more-info"></div></div>',
      );
    }
    //TODO: Improve displaying of vote count and the voters.
    if ($translation->count != '0') {
      $voters = array();
      foreach ($translation->votes as $name => $vote) {
        $voters[] = theme('username', array('account' => (object) array('name' => $name, 'uid' => $vote->uid)));
      }
      $form['votes'] = array(
        '#type' => 'fieldset',
        '#title' => t('Number of Votes: !count', array('!count' => $translation->count)),
        //'#prefix' => '<div class="l10n-more-info">',
        //'#suffix' => '</div>',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
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
 *   An array of strings as generated by l10n_feedback_unpack_string().
 * @param $empty
 *   Specific data to include as the data to use when empty.
 */
function _l10n_feedback_translate_render_textarray($textarray, $empty = '') {
  // data-empty is a proprietary attribute used in editor.css to be displayed when
  // starting to submit a new suggestion.
  $empty = !empty($empty) ? ' data-empty="' . check_plain($empty) . '"' : '';
  return "<span$empty>" . implode("</span><br /><span$empty>", array_map('check_plain', $textarray)) . '</span>';
}


/**
 * Generates the byline containing meta information about a string.
 */
function l10n_feedback_translate_byline($name, $uid, $time, $medium =-1, $type =-1, $link_user =TRUE) {
  $account = (object) array('name' => $name, 'uid' => $uid);
  $username = ($link_user ? theme('username', array('account' => $account)) : check_plain($name));
  //dpm($username);  //debug
  $params = array(
    '!author' => $uid ? $username : t('uknown user'),
    // Also skip handling time if uid was not specified (for decline entries
    // in the update, which have time for ordering reasons, but no uid).
    '@date' => $time && $uid ? format_date(strtotime($time)) : t('unknown time'),
    '@ago' => $time ? t('@time ago', array('@time' => format_interval(REQUEST_TIME - strtotime($time)))) : t('no time record available'),
  );

  return t('by !author <span title="@ago">on @date</span>', $params);

  /*
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
  */

}
