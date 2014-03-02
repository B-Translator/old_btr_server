<?php
/**
 * @file
 * Callback functions for btrServices.
 */

/**
 * Getting reports of different kinds. Anybody can
 * retrieve them, there are no access restrictions.
 *
 * @param $report
 *   The name/id of the report.
 *
 * @param $params
 *   Parameters of the report, comming from the
 *   GET request. They depend on the kind of report.
 *
 * @return
 *   The data of the requested report.
 *
 * @example
 *   curl -k -i \
 *     'https://dev.l10n.org.xx/public/btr/report/statistics?lng=sq'
 *   curl -k -i \
 *     'https://dev.l10n.org.xx/public/btr/report/topcontrib?lng=sq&period=week'
 */
function _btr_report_retrieve($report, $params) {
  $report_function = '_btr_report_' . $report;
  if (! function_exists($report_function) ) {
    return services_error("Unknown report: $report", 406);
  }
  return $report_function($params);
}

/**
 * Getting general statistics (number of votes and
 * translations) for the last week, month and year.
 *
 * @param $params
 *   Parameters of the report, comming from the POST request.
 *   It contains these fields (variables):
 *   - lng: language of translations
 *
 * @return
 *   Array of general stats for week, month and year.
 *
 * @example
 *   curl -k -i -H "Content-type: application/json"  \
 *        -X POST https://dev.l10n.org.xx/public/btr/report/statistics \
 *        -d '{"lng": "sq"}'
 */
function _btr_report_statistics($params) {
  // get parameters and validate them
  $lng = $params['lng'];
  $arr_langs = array_keys(btr_get_languages());
  if (!in_array($lng, $arr_langs)) {
    return services_error('Language missing or not supported.', 406);
  }

  return btr_statistics($lng);
}

/**
 * Getting statistics about top contributors.
 *
 * @param $params
 *   Parameters of the report, comming from the POST request.
 *   It contains these fields (variables):
 *   - lng: language of translations
 *   - period: period of report (last day|week|month|year)
 *   - size: number of results (top contributers), between 5 and 20
 *
 * @return
 *   Array of users, where each user is an object with these attributes:
 *   uid, name, umail, score, translations, votes
 *
 * @example
 *   curl -k -i -H "Content-type: application/json"  \
 *     -X POST https://dev.l10n.org.xx/public/btr/report/topcontrib \
 *     -d '{"lng": "sq", "period": "week", "size": 10}'
 */
function _btr_report_topcontrib($params) {
  // get parameters and validate them
  $lng = $params['lng'];
  $arr_langs = array_keys(btr_get_languages());
  if (!in_array($lng, $arr_langs)) {
    return services_error('Language missing or not supported.', 406);
  }
  $period = $params['period'];
  if (!in_array($period, array('day', 'week', 'month', 'year'))) {
    return services_error('Period missing or not supported.', 406);
  }
  $size = (int) $params['size'];
  if ($size < 5)  $size = 5;
  if ($size > 20) $size = 20;

  return btr_stat_topcontrib($lng, $period, $size);
}

/**
 * Get a string, along with its translations votes and other details.
 *
 * @param $sguid
 *   The string (globally unique) id, calculated
 *   as: $sguid = sha1($string . $context)
 *   It can also be: next|translated|untranslated
 *
 * @param $lng
 *   The language of translations, like: 'fr', 'sq', etc.
 *
 * @return
 *   A nested structure containing the string, its
 *   translations, votes, etc.
 *
 * @example
 *   curl -k -i \
 *     'https://dev.l10n.org.xx/public/btr/translations/next?lng=sq'
 */
function _btr_translations_retrieve($sguid, $lng) {
  $strings = _btr_translations_get(array(
               'sguid' => $sguid,
               'lng' => $lng,
             ));
  return $strings;
}


/**
 * Filter strings and translations according to the given parameters.
 *
 * This provides the same functionality and has the same parameters
 * as the operation 'translations/search'. The only difference is that
 * the parameters are provided as a GET request (in the URL), whereas
 * the parameters of 'translations/search' are provided as a POST
 * request. Sometimes this may be more convenient.
 *
 * @param $params
 *   Parameters for filtering the strings etc.
 *
 * @return
 *   Array containing search results, along with the filters
 *   and the pager info (same as for the search case).
 *
 * @example
 *   curl -k -i -H 'Accept: application/json' \
 *     'https://dev.l10n.org.xx/public/btr/translations?lng=sq&words=file'
 */
function _btr_translations_index($params) {
  return _btr_translations_search($params);
}


/**
 * Search strings and translations using various filters.
 *
 * @param $params
 *   Associative array of the POST data, which contains
 *   the filter parameters. These parameters can be:
 *   - lng
 *       The language of translations.
 *   - limit
 *       The number of results to be returned (min: 5, max: 50).
 *   - words
 *       Words to be searched for.
 *   - mode
 *       Search mode. Can be one of:
 *       - natural-strings       Natural search on strings (default).
 *       - natural-translations  Natural search on translations.
 *       - boolean-strings       Boolean search on strings.
 *       - boolean-translations  Boolean search on translations.
 *   - page
 *       Page of results to be displayed.
 *   - project
 *       Limit search only to this project
 *   - origin
 *       Limit search only to the projects of this origin.
 *   - only_mine (boolean)
 *       Limit search only to the strings touched (translated or voted)
 *       by the current user.
 *   - translated_by
 *       Limit search by the author of translations
 *       (can be used only by admins).
 *   - voted_by
 *       Limit search by a voter (can be used only by admins).
 *   - date_filter
 *       Which date to filter (used only by admins). Can be one of:
 *       - strings       Filter Strings By Date
 *       - translations  Filter Translations By Date (default)
 *       - votes         Filter Votes By Date
 *   - from_date (YYYY-MM-DD)
 *       Takes the current date by default.
 *   - to_date (YYYY-MM-DD)
 *       Takes the current date by default.
 *
 * @return
 *   Array containing search results, along with the filters
 *   and the pager info. Each result is a nested structure
 *   containing the string, its translations, votes, etc.
 */
function _btr_translations_search($params) {
  // Get and check the parameter 'lng'.
  $lng = $params['lng'];
  $arr_langs = array_keys(btr_get_languages());
  if (!in_array($lng, $arr_langs)) {
    return services_error('Language missing or not supported.', 406);
  }

  // The PagerDefault of Drupal7 queries gets the current page
  // from $_GET['page']. This is a trick to make it work.
  // See: https://api.drupal.org/api/drupal/includes%21pager.inc/function/pager_find_page/7
  $_GET['page'] = isset($params['page']) ? (int)trim($params['page']) : 0;

  // Build the filter and the query, and then get the strings.
  $filter = btr_build_search_filter($params);
  $query = btr_build_search_query($filter);
  $strings = ($query===NULL ? array() : btr_get_query_strings($query, $lng));

  // The PagerDefault of Drupal7 defines the pager variables
  // as global variables (these variables are later used by theme_pager).
  // See: https://api.drupal.org/api/drupal/includes!pager.inc/function/pager_default_initialize/7
  $pager = array(
    'number_of_items' => $GLOBALS['pager_total_items'][0],
    'items_per_page' => $GLOBALS['pager_limits'][0],
    'number_of_pages' => $GLOBALS['pager_total'][0],
    'current_page' => $GLOBALS['pager_page_array'][0],
  );

  return array(
    'filter' => $filter,
    'pager' => $pager,
    'strings' => $strings,
  );
}


/**
 * Get the sguid of a random string according to the target.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - target
 *       Can be one of: next|translated|untranslated
 *   - lng
 *       Code of the language (required for translated and untranslated)
 *   - last_sguid (optional)
 *       If provided, restricts the pool of selection the project(s)
 *       of the last reviewed sguid.
 *
 * @return
 *   Associative array containing:
 *   - sguid
 *       ID of a random string, or the target itself
 *       if it is different from next|translated|untranslated
 */
function _btr_translations_get_random_sguid($params) {
  $projects = NULL;
  if (isset($params['last_sguid'])) {
    $projects = btr_get_projects_of_sguid($params['last_sguid']);
  }
  $target = $params['target'];
  $lng = $params['lng'];
  return array(
    'sguid' => btr_get_random_sguid($target, $lng, $projects)
  );
}


/**
 * Get a string, along with its translations votes and other details.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - sguid
 *       The string (globally unique) id, calculated
 *       as: $sguid = sha1($string . $context)
 *       It can also be: next|translated|untranslated
 *   - lng
 *       The language of translations, like: 'fr', 'sq', etc.
 *
 * @return
 *   A nested structure containing the string, its
 *   translations, votes, etc.
 *
 * @example
 *   curl -k -i -H 'Content-type: application/json' \
 *     -X POST https://dev.l10n.org.xx/public/btr/translations/get
 *     -d '{"lng": "sq"}'
 */
function _btr_translations_get($params) {
  $lng = $params['lng'];
  $arr_langs = array_keys(btr_get_languages());
  if (!in_array($lng, $arr_langs)) {
    return services_error('Language missing or not supported.', 406);
  }

  $sguid = $params['sguid'];
  if (in_array($sguid, array('next', 'translated', 'untranslated'))) {
    $sguid = btr_get_random_sguid($sguid, $lng);
  }

  $strings = btr_get_strings(array($sguid), $lng);
  return $strings;
}

/**
 * Add a new translation to a source string.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - sguid
 *       The string ID for which a new translation should be added.
 *   - lng
 *       The language (code) of the new translation.
 *   - translation
 *       The new translation as a string. If the string has plural
 *       version(s) as well, they are concatenated with NULL bytes ("\0")
 *       between them.
 *
 * @return
 *   Associative array containing:
 *   - tguid
 *       ID of the new translation, or NULL if no translation was added.
 *   - messages
 *       Array of notification messages; each notification message
 *       is an array of a message and a type, where type can be one of
 *       'status', 'warning', 'error'.
 */
function _btr_translations_add($params) {
  // get parameters and validate them
  $sguid = $params['sguid'];
  $translation = $params['translation'];
  $lng = $params['lng'];
  $arr_langs = array_keys(btr_get_languages());
  if (!in_array($lng, $arr_langs)) {
    return services_error('Language missing or not supported.', 406);
  }

  list($tguid, $messages) = btr_add_translation($sguid, $lng, $translation);
  return array(
    'tguid' => $tguid,
    'messages' => $messages
  );
}


/**
 * Add a vote for the given translation.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - tguid
 *       ID of the translation
 *
 * @return
 *   Associative array containing:
 *   - vid
 *       ID of the new vote, or NULL
 *   - messages
 *       Array of notification messages; each notification message
 *       is an array of a message and a type, where type can be one of
 *       'status', 'warning', 'error'.
 */
function _btr_translations_vote($params) {
  $tguid = $params['tguid'];
  list($vid, $messages) = btr_add_vote($tguid);
  return array(
    'vid' => $vid,
    'messages' => $messages
  );
}

/**
 * Delete a translation.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - tguid
 *       ID of the translation
 *
 * @return
 *   Associative array containing:
 *   - messages
 *       Array of notification messages; each notification message
 *       is an array of a message and a type, where type can be one of
 *       'status', 'warning', 'error'.
 */
function _btr_translations_del($params) {
  $tguid = $params['tguid'];
  $messages = btr_del_translation($tguid);
  return array(
    'messages' => $messages
  );
}

/**
 * Delete a vote from the given translation.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - tguid
 *       ID of the translation
 *
 * @return
 *   Associative array containing:
 *   - messages
 *       Array of notification messages; each notification message
 *       is an array of a message and a type, where type can be one of
 *       'status', 'warning', 'error'.
 */
function _btr_translations_del_vote($params) {
  $tguid = $params['tguid'];
  $messages = btr_del_vote($tguid);
  return array(
    'messages' => $messages
  );
}

/**
 * Submit multiple actions at once.
 *
 * @param $params
 *   Array of the POST data, which contains an item for each action.
 *   Each action is an associated array that contains the items:
 *   - action
 *       The action to be done (add, vote, del, del_vote)
 *   - params
 *       Associative array of the needed parameters for this action.
 *
 * @return
 *   Associative array containing:
 *   - messages
 *       Array of notification messages; each notification message
 *       is an array of a message and a type, where type can be one of
 *       'status', 'warning', 'error'.
 */
function _btr_translations_submit($params) {
  $messages = array();
  $nr_votes = $nr_suggestions = $nr_deletions = 0;
  foreach ($params as $item) {
    switch ($item['action']) {
    case 'add':
      $result = _btr_translations_add($item['params']);
      if ($result['tguid'] != NULL)  $nr_suggestions++;
      $messages += $result['messages'];
      break;

    case 'vote':
      $result = _btr_translations_vote($item['params']);
      if ($result['vid'] != NULL)  $nr_votes++;
      $messages += $result['messages'];
      break;

    case 'del':
      $result = _btr_translations_del($item['params']);
      if (sizeof($result['messages'])==0) {
	$nr_deletions++;
      }
      else {
	$messages += $result['messages'];
      }
      break;

    case 'del_vote':
      $result = _btr_translations_del_vote($item['params']);
      $messages += $result['messages'];
      break;

    default:
      $msg = t('Action !action is not supported!',
	       array('!action' => $item['action']));
      $messages[] = array($msg, 'error');
      break;
    }
  }

  if ($nr_suggestions > 0) {
    $msg = format_plural($nr_suggestions, '1 suggestion saved', '@count suggestions saved');
    $messages[] = array($msg, 'status');
  }
  if ($nr_votes > 0) {
    $msg = format_plural($nr_votes, '1 vote saved', '@count votes saved');
    $messages[] = array($msg, 'status');
  }
  if ($nr_deletions > 0) {
    $msg = format_plural($nr_deletions, '1 translation deleted', '@count translations deleted');
    $messages[] = array($msg, 'status');
  }

  return array(
    'messages' => $messages
  );
}

