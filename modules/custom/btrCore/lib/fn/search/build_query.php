<?php
/**
 * @file
 * Function: search_build_query()
 */

namespace BTranslator;
use \btr;

/**
 * Build the query that selects the strings that match the given filter.
 *
 * This query should return only the id-s of the matching strings and
 * the matching scores, ordered by the score in decreasing order.
 *
 * It should be something like this:
 *
 *    SELECT s.sguid,
 *           MAX(MATCH (t.translation) AGAINST (:words)) AS score
 *    FROM {btr_strings} s
 *    LEFT JOIN {btr_translations} t ON (s.sguid = t.sguid)
 *    LEFT JOIN . . . . .
 *    . . . . . . . . . .
 *    WHERE (t.lng = :lng)
 *      AND (MATCH (t.translation) AGAINST (:words IN BOOLEAN MODE))
 *    . . . . . . . . . .
 *    GROUP BY s.sguid
 *    ORDER BY score DESC
 *    LIMIT :limit;
 *
 * Tables that are joined and the select conditions are based on the
 * values of the filter.
 *
 * @param $filter
 *   Filter conditions that should be matched.
 *   It is an associated array with these keys:
 *      lng, limit, mode, words, project, origin, only_mine, translated_by,
 *      voted_by, date_filter, from_date, to_date, list_mode
 *
 * @return
 *   A query object that corresponds to the filter.
 *   NULL if there is nothing to select.
 */
function search_build_query($filter) {
  // Store the value of the language.
  _lng($filter['lng']);

  $query = btr::db_select('btr_strings', 's')
    ->extend('PagerDefault')->limit($filter['limit']);
  $query->addField('s', 'sguid');
  $query->groupBy('s.sguid');

  _filter_by_content($query, $filter['mode'], $filter['words']);
  _filter_by_project($query, $filter['project'], $filter['origin']);
  _filter_by_author($query, $filter['lng'], $filter['only_mine'], $filter['translated_by'], $filter['voted_by']);
  _filter_by_date($query, $filter['date_filter'], $filter['from_date'], $filter['to_date']);
  _filter_by_list_mode($query, $filter['list_mode']);

  //if nothing has been selected yet, then return NULL
  if (sizeof($query->conditions()) == 1) return NULL;

  //btr::log(_get_query_string($query), '$query');  //debug
  return $query;
}

/**
 * Return the query as a string (for debug).
 */
function _get_query_string(\SelectQueryInterface $query) {
  $string = (string) $query;
  $arguments = $query->arguments();

  if (!empty($arguments) && is_array($arguments)) {
    foreach ($arguments as $placeholder => &$value) {
      if (is_string($value)) {
        $value = "'$value'";
      }
    }
    $arguments += ['{' => '', '}' => ''];

    $string = strtr($string, $arguments);
  }

  return $string;
}

/**
 * Keep and return the value of language (instead of using a global variable).
 */
function _lng($lang = NULL) {
  static $lng = NULL;
  if ($lang !== NULL) {
    $lng = $lang;
  }
  return $lng;
}

/**
 * Apply to the query conditions related to the content
 * (of strings and translations). Depending on the search_mode,
 * we look either for strings/translations similar to the given phase,
 * or for strings/translations matching the given words,
 * The first parameter, $query, is an object, so it is
 * passed by reference.
 */
function _filter_by_content($query, $search_mode, $search_words) {

  //if there are no words to be searched for, no condition can be added
  if (trim($search_words) == '') {
    $query->addExpression('1', 'score');
    return;
  }

  //get the match condition and the score field
  //according to the search mode
  list($mode, $content) = explode('-', $search_mode);
  $in_boolean_mode = ($mode=='boolean' ? ' IN BOOLEAN MODE' : '');
  if ($content=='strings') {
    $query->addExpression('MATCH (s.string) AGAINST (:words)', 'score');
    $query->where(
      'MATCH (s.string) AGAINST (:words' . $in_boolean_mode . ')',
      array(':words' => $search_words)
    );
  }
  else {   // ($content=='translations')
    _join_table($query, 'translations');
    $query->addExpression('MAX(MATCH (t.translation) AGAINST (:words))', 'score');
    $query->where(
      'MATCH (t.translation) AGAINST (:words' . $in_boolean_mode . ')',
      array(':words' => $search_words)
    );
  }

  //order results by the field score
  $query->orderBy('score', 'DESC');
}

/**
 * Apply to the query conditions related to projects and origin.
 * The first parameter, $query, is an object, so it is passed
 * by reference.
 */
function _filter_by_project($query, $project, $origin) {

  if ($project == '' and $origin == '')  return;

  _join_table($query, 'projects');

  if ($project != '') {
    $query->condition('p.project', $project);
  }
  if ($origin != '') {
    $query->condition('p.origin', $origin);
  }
}

/**
 * Apply to the query conditions related to authors.
 * The first parameter, $query, is an object, so it is passed
 * by reference.
 */
function _filter_by_author($query, $lng, $only_mine, $translated_by, $voted_by) {

  if ($only_mine) {
    _join_table($query, 'votes');

    global $user;
    $umail = $user->init;  // initial mail used for registration
    $query->condition(db_or()
      ->condition(db_and()
        ->condition('t.umail', $umail)
        ->condition('t.ulng', $lng)
      )
      ->condition(db_and()
        ->condition('v.umail', $umail)
        ->condition('v.ulng', $lng)
      )
    );
    //done, ignore $translated_by and $voted_by
    return;
  }

  //get the umail for $translated_by and $voted_by
  $get_umail = 'SELECT umail FROM {btr_users} WHERE name = :name AND ulng = :ulng';
  $args = array();
  if ($translated_by == '') $t_umail = '';
  else {
    $account = user_load_by_name($translated_by);
    $args[':ulng'] = $account->translation_lng;
    $args[':name'] = $translated_by;
    $t_umail = btr::db_query($get_umail, $args)->fetchField();
  }
  if ($voted_by == '') $v_umail = '';
  else {
    $account = user_load_by_name($voted_by);
    $args[':ulng'] = $account->translation_lng;
    $args[':name'] = $voted_by;
    $v_umail = btr::db_query($get_umail, $args)->fetchField();
  }

  //if it is the same user, then search for strings
  //translated OR voted by this user
  if ($t_umail==$v_umail and $t_umail!='') {
    _join_table($query, 'votes');
    $query->condition(db_or()
      ->condition(db_and()
        ->condition('t.umail', $t_umail)
        ->condition('t.ulng', $lng)
      )
      ->condition(db_and()
        ->condition('v.umail', $v_umail)
        ->condition('v.ulng', $lng)
      )
    );
    return;
  }

  //if the users are different, then search for strings
  //translated by $t_umail AND voted by $v_umail
  if ($t_umail != '') {
    _join_table($query, 'translations');
    $query->condition('t.umail', $t_umail)->condition('t.ulng', $lng);
  }
  if ($v_umail != '') {
    _join_table($query, 'votes');
    $query->condition('v.umail', $v_umail)->condition('v.ulng', $lng);
  }
}

/**
 * Apply to the query conditions related to translation or voting dates.
 *
 * The first parameter, $query, is an object, so it is passed
 * by reference.
 *
 * $date_filter has one of the values ('strings', 'translations', 'votes')
 */
function _filter_by_date($query, $date_filter, $from_date, $to_date) {
  // If both dates are empty, there is no condition to be added.
  if ($from_date == '' and $to_date == '')  return;

  //if the date of translations or votes has to be checked,
  //then the corresponding tables must be joined
  if ($date_filter == 'translations') {
    _join_table($query, 'translations');
  }
  elseif ($date_filter == 'votes') {
    _join_table($query, 'votes');
  }

  //get the alias (name) of the date field that has to be checked
  if      ($date_filter=='strings')  $field = 's.time';
  elseif  ($date_filter=='votes')    $field = 'v.time';
  else                               $field = 't.time';

  //add to query the propper date condition;
  //if none of the dates are given, no condition is added
  if ($from_date != '' and $to_date != '') {
    $query->condition($field, array($from_date, $to_date), 'BETWEEN');
    $query->orderBy($field, 'DESC');
  }
  elseif ($from_date == '' and $to_date != '') {
    $query->condition($field, $to_date, '<=');
    $query->orderBy($field, 'DESC');
  }
  elseif ($from_date != '' and $to_date == '') {
    $query->condition($field, $from_date, '>=');
    $query->orderBy($field, 'DESC');
  }
  else {
    //do nothing
  }

}

/**
 * Apply to the query conditions related to filtering by translated/untranslated.
 *
 * The first parameter, $query, is an object, so it is passed
 * by reference.
 *
 * $list_mode has one of the values ('all', 'translated', 'untranslated')
 */
function _filter_by_list_mode($query, $list_mode) {
  // If 'all' strings should be listed, there is no condition to be added.
  if ($list_mode == 'all')  return;

  // Join the table of translations.
  _join_table($query, 'translations');

  // Add the condition for filtering the translated/untranslated strings.
  if ($list_mode == 'translated') {
    $query->isNotNull('t.sguid');
  }
  else {
    $query->isNull('t.sguid');
  }
}

/**
 * Add a join for the given table to the $query.
 * Make sure that the join is added only once (by using tags).
 * $table can be one of: translations, votes, locations
 */
function _join_table($query, $table) {
  $tag = "join-$table";
  if ($query->hasTag($tag))  return;
  $query->addTag($tag);

  switch ($table) {
    case 'translations':
      $query->leftJoin("btr_translations", 't', 's.sguid = t.sguid AND t.lng = :lng', [':lng' => _lng()]);
      break;
    case 'votes':
      _join_table($query, 'translations');
      $query->leftJoin("btr_votes", 'v', 'v.tguid = t.tguid');
      break;
    case 'locations':
      $query->leftJoin("btr_locations", 'l', 's.sguid = l.sguid');
      break;
    case 'templates':
      $query->leftJoin("btr_templates", 'tpl', 'tpl.potid = l.potid');
      break;
    case 'projects':
      _join_table($query, 'locations');
      _join_table($query, 'templates');
      $query->leftJoin("btr_projects", 'p', 'p.pguid = tpl.pguid');
      break;
    default:
      debug("Error: _join_table(): table '$table' is unknown.");
      break;
  }
}
