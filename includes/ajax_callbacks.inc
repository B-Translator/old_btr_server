<?php

// = AJAX callbacks ============================================================

/**
 * Retrieve a JSON list of autocomplete suggestions for projects.
 */
function l10n_suggestions_project_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $query = "SELECT DISTINCT SUBSTRING(projectname,3) AS project
              FROM {l10n_suggestions_locations}
              WHERE projectname LIKE :str ORDER BY project";
    $result = db_query_range($query, 0, 10, array(':str' => '_/'.$string.'%'));
    foreach ($result as $project) {
      $matches[$project->project] = check_plain($project->project);
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

?>