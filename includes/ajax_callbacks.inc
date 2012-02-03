<?php

// = AJAX callbacks ============================================================

/**
 * Retrieve a JSON list of autocomplete suggestions for projects.
 */
function l10n_suggestions_project_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $query = "SELECT DISTINCT project
              FROM {l10n_suggestions_projects}
              WHERE project LIKE :str ORDER BY project";
    $result = db_query_range($query, 0, 10, array(':str' => $string.'%'));
    foreach ($result as $project) {
      $matches[$project->project] = check_plain($project->project);
    }
  }
  print drupal_json_encode($matches);
  exit();
}

/**
 * Retrieve a JSON list of autocomplete suggestions for origins of projects.
 */
function l10n_suggestions_origin_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $query = "SELECT DISTINCT origin
              FROM {l10n_suggestions_projects}
              WHERE origin LIKE :str ORDER BY origin";
    $result = db_query_range($query, 0, 10, array(':str' => $string.'%'));
    foreach ($result as $project) {
      $matches[$project->origin] = check_plain($project->origin);
    }
  }
  print drupal_json_encode($matches);
  exit();
}

/**
 * Retrieve a JSON list of autocomplete suggestions for users.
 */
function l10n_suggestions_user_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $query = "SELECT name FROM {users} WHERE name LIKE :str ORDER BY name";
    $result = db_query_range($query, 0, 10, array(':str' => $string.'%'));
    foreach ($result as $user) {
      $matches[$user->name] = check_plain($user->name);
    }
  }
  print drupal_json_encode($matches);
  exit();
}


/**
 * Return string context, a list of related projects (where the string appears), etc.
 * This callback is invoked from JavaScript and is used as an AJAX provider.
 *
 * @param $sguid
 *   Id of the string.
 */
function l10n_suggestions_string_details($sguid) {

  $output = '';

  // Get the context of this string.
  $context = db_query("SELECT context FROM l10n_suggestions_strings WHERE sguid = :sguid",
             array(':sguid' => $sguid))
    ->fetchField();
  if (!empty($context)) {
    $output .= '<h3>' . t('Used with context: %context', array('%context' => $context)) . '</h3>';
  }

  // List projects where this string is used.
  $output .= '<h3>' .  t('Used on these projects:') . '</h3>';
  $sql = "SELECT CONCAT(p.origin, ' / ', p.project) AS proj
          FROM l10n_suggestions_strings s
          RIGHT JOIN l10n_suggestions_locations l ON (l.sguid = s.sguid)
          RIGHT JOIN l10n_suggestions_templates t ON (t.potid = l.potid)
          RIGHT JOIN l10n_suggestions_projects p ON (p.pguid = t.pguid)
          WHERE s.sguid = :sguid";
  $project_list = db_query($sql, array(':sguid' => $sguid))->fetchCol();
  $output .= theme('item_list', array('items' => $project_list));

  print $output;
  exit(0);
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
  if (!empty($uid_submitted) && ($uid_submitted != $string->uid)) {
    // Turns out the user used for attribution is different to the user used for
    // the string storage.
    // TODO Convert "user_load" to "user_load_multiple" if "$string->uid" is other than a uid.
    // To return a single user object, wrap "user_load_multiple" with "array_shift" or equivalent.
    // Example: array_shift(user_load_multiple(array(), $string->uid))
    $account = user_load($string->uid);
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

?>