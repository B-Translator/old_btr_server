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
 *     The name/id of the report.
 *
 * @param $params
 *     Parameters of the report, comming from the
 *     GET request. They depend on the kind of report.
 *
 * @return
 *     The data of the requested report.
 *
 * @example
 *     Open in browser:
 *        https://dev.l10n.org.xx/public/btr/report/statistics?lng=sq
 *        https://dev.l10n.org.xx/public/btr/report/topcontrib?lng=sq&period=week
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
 *     Parameters of the report, comming from the POST request.
 *     It contains these fields (variables):
 *       - lng: language of translations
 *
 * @return
 *     Array of general stats for week, month and year.
 *
 * @example
 *     curl -k -i -H "Content-type: application/json"  \
 *          -X POST https://dev.l10n.org.xx/public/btr/report/statistics.json	\
 *          -d '{"lng": "sq"}'
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
 *     Parameters of the report, comming from the POST request.
 *     It contains these fields (variables):
 *       - lng: language of translations
 *       - period: period of report (last day|week|month|year)
 *       - size: number of results (top contributers), between 5 and 20
 *
 * @return
 *     Array of users, where each user is an object with these attributes:
 *         uid, name, umail, score, translations, votes
 *
 * @example
 *     curl -k -i -H "Content-type: application/json"  \
 *          -X POST https://dev.l10n.org.xx/public/btr/report/topcontrib.json	\
 *          -d '{"lng": "sq", "period": "week", "size": 10}'
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
 * Return a string, along with its translations,
 * votes and other details.
 *
 * @param $sguid
 *     The string (globally unique) id, calculated
 *     as: $sguid = sha1($string . $context)
 *     It can also be: next|translated|untranslated
 *
 * @param $lng
 *     The language of translations, like: 'fr', 'sq', etc.
 *
 * @return
 *     A nested structure containing the string, its
 *     translations, votes, etc.
 *
 * @example
 *     Open in browser:
 *       https://dev.l10n.org.xx/public/btr/translations/next?lng=sq
 */
function _btr_translations_retrieve($sguid, $lng) {
  $arr_langs = array_keys(btr_get_languages());
  if (!in_array($lng, $arr_langs)) {
    return services_error('Language missing or not supported.', 406);
  }

  switch ($sguid) {
    case 'next':
      $sguid = btr_sguid_get_next();
      break;
    case 'translated':
      $sguid = btr_sguid_get_translated($lng);
      break;
    case 'untranslated':
      $sguid = btr_sguid_get_untranslated($lng);
      break;
  }

  $strings = btr_get_strings(array($sguid), $lng);
  return $strings;
}

/**
 * Filter strings and translations according to the given parameters.
 *
 * @param $params
 *     Parameters for filtering the strings etc.
 *
 * @example
 */
function _btr_translations_index($params) {
  return $params;
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
function _btr_translations_add_translation($params) {
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
function _btr_translations_add_vote($params) {
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
function _btr_translations_del_translation($params) {
  $tguid = $params['tguid'];
  $messages = btr_del_translation($tguid);
  return array(
    'messages' => $messages
  );
}
