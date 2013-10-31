<?php
/**
 * @file
 * Build the query that selects the strings that match the given filter.
 */

/**
 * Build the query that selects the strings that match
 * the given filter. This query should return only the id-s
 * of the matching strings and the matching scores, ordered by
 * the score in decreasing order.
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
 * Tables that are joined and the select conditions are based
 * on the values of the filter.
 *
 * @param $filter
 *   Filter conditions that should be matched.
 *   It is an associated array with these keys:
 *      lng, limit, mode, words, project, origin, only_mine,
 *      translated_by, voted_by, date_filter, from_date, to_date
 * @return
 *   A query object that corresponds to the filter.
 */
function btr_build_search_query($filter) {

  $query = $GLOBALS['btr_db']->select('btr_strings', 's')
    ->extend('PagerDefault')->limit($filter['limit']);
  $query->addField('s', 'sguid');
  $query->groupBy('s.sguid');

  _btr_filter_by_content($query, $filter['mode'], $filter['words']);
  _btr_filter_by_project($query, $filter['project'], $filter['origin']);
  _btr_filter_by_author($query, $filter['lng'], $filter['only_mine'], $filter['translated_by'], $filter['voted_by']);
  _btr_filter_by_date($query, $filter['date_filter'], $filter['from_date'], $filter['to_date']);

  //if nothing has been selected yet, then return FALSE
  //dpm($query->conditions(), 'query_conditions');  //debug
  if (sizeof($query->conditions()) == 1) return FALSE;

  //if translations are joined, then filter by the language as well
  if ($query->hasTag('join-translations')) {
    $query->condition('t.lng', $filter['lng']);
  }

  dpq($query);  //debug
  return $query;
}

/**
 * Apply to the query conditions related to the content
 * (of strings and translations). Depending on the search_mode,
 * we look either for strings/translations similar to the given phase,
 * or for strings/translations matching the given words,
 * The first parameter, $query, is an object, so it is
 * passed by reference.
 */
function _btr_filter_by_content($query, $search_mode, $search_words) {

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
    _btr_join_table($query, 'translations');
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
function _btr_filter_by_project($query, $project, $origin) {

  if ($project == '' and $origin == '')  return;

  _btr_join_table($query, 'projects');

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
function _btr_filter_by_author($query, $lng, $only_mine, $translated_by, $voted_by) {

  if ($only_mine) {
    _btr_join_table($query, 'votes');

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
  $db = $GLOBALS['btr_db'];
  $get_umail = 'SELECT umail FROM {btr_users} WHERE name = :name AND ulng = :ulng';
  $args = array();
  $args[':ulng'] = $lng;
  $args[':name'] = $translated_by;
  $t_umail = ($translated_by == '') ? '' : $db->query($get_umail, $args)->fetchField();
  $args[':name'] = $voted_by;
  $v_umail = ($voted_by == '') ? '' : $db->query($get_umail, $args)->fetchField();

  //if it is the same user, then search for strings
  //translated OR voted by this user
  if ($t_umail==$v_umail and $t_umail!='') {
    _btr_join_table($query, 'votes');
    $query ->condition(db_or()
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
    _btr_join_table($query, 'translations');
    $query->condition('t.umail', $t_umail)->condition('t.ulng', $lng);
  }
  if ($v_umail != '') {
    _btr_join_table($query, 'votes');
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
 * $from_date and $to_date are associative arrays of the format
 * array('year' => int, 'month' => int, 'day' => int)
 */
function _btr_filter_by_date($query, $date_filter, $from_date, $to_date) {

  //convert $from_date and $to_date to the string format YYYY-MM-DD
  $from_date_str = date('Y-m-d', mktime(1, 0, 0, $from_date['month'], $from_date['day'], $from_date['year']));
  $to_date_str = date('Y-m-d', mktime(1, 0, 0, $to_date['month'], $to_date['day'], $to_date['year']));

  //get the current date in the standard string format 'YYYY-MM-DD'
  $today_str = date('Y-m-d');

  //if both dates are equal to today, there is no condition to be added
  if ($from_date_str == $today_str && $to_date_str == $today_str)  return;

  //if the date of translations or votes has to be checked,
  //then the corresponding tables must be joined
  if ($date_filter == 'translations') {
    _btr_join_table($query, 'translations');
  }
  elseif ($date_filter == 'votes') {
    _btr_join_table($query, 'votes');
  }

  //get the alias (name) of the date field that has to be checked
  if      ($date_filter=='strings')  $field = 's.time';
  elseif  ($date_filter=='votes')    $field = 'v.time';
  else                               $field = 't.time';

  //add to query the propper date condition;
  //if none of the dates are given, no condition is added
  if ($from_date_str != $today_str and $to_date_str != $today_str) {
    $query->condition($field, array($from_date_str, $to_date_str), 'BETWEEN');
    $query->orderBy($field, 'DESC');
  }
  elseif ($from_date_str == $today_str and $to_date_str != $today_str) {
    $query->condition($field, $to_date_str, '<=');
    $query->orderBy($field, 'DESC');
  }
  elseif ($from_date_str != $today_str and $to_date_str == $today_str) {
    $query->condition($field, $from_date_str, '>=');
    $query->orderBy($field, 'DESC');
  }
  else {
    //do nothing
  }

}

/**
 * Add a join for the given table to the $query.
 * Make sure that the join is added only once (by using tags).
 * $table can be one of: translations, votes, locations
 */
function _btr_join_table($query, $table) {
  $tag = "join-$table";
  if ($query->hasTag($tag))  return;
  $query->addTag($tag);

  switch ($table) {
    case 'translations':
      $query->leftJoin("btr_translations", 't', 's.sguid = t.sguid');
      break;
    case 'votes':
      _btr_join_table($query, 'translations');
      $query->leftJoin("btr_votes", 'v', 'v.tguid = t.tguid');
      break;
    case 'locations':
      $query->leftJoin("btr_locations", 'l', 's.sguid = l.sguid');
      break;
    case 'templates':
      $query->leftJoin("btr_templates", 'tpl', 'tpl.potid = l.potid');
      break;
    case 'projects':
      _btr_join_table($query, 'locations');
      _btr_join_table($query, 'templates');
      $query->leftJoin("btr_projects", 'p', 'p.pguid = tpl.pguid');
      break;
    default:
      debug("Error: _btr_join_table(): table '$table' is unknown.");
      break;
  }
}
