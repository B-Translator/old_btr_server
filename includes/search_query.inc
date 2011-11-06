<?php

/**
 * Build a query for selecting strings and translations,
 * based on the settings of the given filter.
 *
 * @param $filter
 *   Filter conditions that should be matched.
 * @return
 *   A query object that corresponds to the filter.
 */
function l10n_suggestions_build_query($filter) {

  //extract filter parameters as variables:
  /*
     $lng, $mode, $words, $limit
     $project, $package, $release
     $only_mine, $translated_by, $voted_by
     $date_filter, $from_date, $to_date
  */
  extract($filter);

  //start building the select query
  /*
      It should be something like this:

      SELECT p.pid, p.phrase, hex(p.hash) AS p_hash,
             t.tid, t.lng, t.translation, hex(t.hash) AS t_hash,
             t.time_entered, t.uid_entered, u.name AS username, t.vcount
      FROM {l10n_suggestions_phrases} p
      LEFT JOIN {l10n_suggestions_translations} t ON (p.pid = t.pid)
      LEFT JOIN {users} u ON u.uid = t.uid_entered
      WHERE . . . . .
      ORDER BY p.pid ASC, t.vcount DESC
  */
  $query = db_select('l10n_suggestions_phrases', 'p')
    ->extend('PagerDefault')->limit($limit);
  $query->leftJoin('l10n_suggestions_translations', 't', 'p.pid = t.pid');
  $query->leftJoin('users', 'u', 'u.uid = t.uid_entered');
  $query->fields('p', array('pid', 'phrase'))
    ->addExpression('HEX(p.hash)', 'p_hash');
  $query->fields('t', array('tid', 'lng', 'translation', 'time_entered', 'uid_entered', 'vcount'))
    ->addExpression('HEX(t.hash)', 't_hash');
  $query->addField('u', 'name', 'username');
  $query->orderBy('p.pid', 'ASC')->orderBy('t.vcount', 'DESC');

  _l10n_suggestions_filter_by_content($query, $mode, $words);
  _l10n_suggestions_filter_by_project($query, $project, $package, $release);
  _l10n_suggestions_filter_by_author($query, $only_mine, $translated_by, $voted_by);
  _l10n_suggestions_filter_by_date($query, $date_filter, $from_date, $to_date);

  //depending on the requirements of the above filters,
  //we may need to join with the table of votes or locations;
  //in such a case we also need to group by translations
  if ($query->hasTag('join-with-votes')) {
    $query->leftJoin('l10n_suggestions_votes', 'v', 'v.tid = t.tid');
  }
  if ($query->hasTag('join-with-locations')) {
    $query->leftJoin('l10n_suggestions_locations', 'l', 'p.pid = l.pid');
  }
  if ($query->hasAnyTag('join-with-votes', 'join-with-locations')) {
    $query->groupBy('t.tid');
  }

  //if nothing has been selected yet, then return false
  //dpm($query->conditions(), 'query_conditions');  //debug
  if (sizeof($query->conditions()) == 1) return false;

  //filter translations by the given language
  $query->condition('t.lng', $lng);

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
function _l10n_suggestions_filter_by_content($query, $search_mode, $search_words) {

  switch ($search_mode) {
    case 'natural-strings':
      $match = 'MATCH (p.phrase) AGAINST (:words)';
      break;
    case 'natural-translations':
      $match = 'MATCH (t.translation) AGAINST (:words)';
      break;
    case 'boolean-strings':
      $match = 'MATCH (p.phrase) AGAINST (:words IN BOOLEAN MODE)';
      break;
    case 'boolean-translations':
      $match = 'MATCH (t.translation) AGAINST (:words IN BOOLEAN MODE)';
      break;
  }

  //perform a full-text search against the given words
  if (trim($search_words) != '') {
    $query->addExpression($match, 'score');
    $query->where($match, array(':words' => $search_words));
  }
}

/**
 * Apply to the query conditions related to authors.
 * The first parameter, $query, is an object, so it is passed
 * by reference.
 */
function _l10n_suggestions_filter_by_project($query, $project, $package, $release) {
  //filter by project
  if ($project != '') {
    if (!$query->hasTag('join-with-locations'))  $query->addTag('join-with-locations');
    $query->condition('l.projectname', '?/' . db_like($project) . '%', 'LIKE');
  }
}

/**
 * Apply to the query conditions related to authors.
 * The first parameter, $query, is an object, so it is passed
 * by reference.
 */
function _l10n_suggestions_filter_by_author($query, $only_mine, $translated_by, $voted_by) {

  if ($only_mine) {
    global $user;

    if (!$query->hasTag('join-with-votes'))  $query->addTag('join-with-votes');
    $query->condition(db_or()
      ->condition('t.uid_entered', $user->uid)
      ->condition('v.uid', $user->uid)
    );
    //done, ignore $translated_by and $voted_by
    return;
  }

  //get the uid $translated_by and $voted_by
  $get_uid = 'SELECT uid FROM {users} WHERE name = :name';
  $t_uid = ($translated_by == '') ? '' :
    db_query($get_uid, array(':name'=>$translated_by))->execute()->fetchField();
  $v_uid = ($voted_by == '') ? '' :
    db_query($get_uid, array(':name'=>$voted_by))->execute()->fetchField();

  //if it is the same user, then search for strings
  //translated OR voted by this user
  if ($t_uid==$v_uid and $t_uid!='') {
    if (!$query->hasTag('join-with-votes'))  $query->addTag('join-with-votes');
    $query->condition(db_or()
      ->condition('t.uid_entered', $t_uid)
      ->condition('v.uid', $t_uid)
    );
    return;
  }

  //if the users are different, then search for strings
  //translated by $t_uid AND voted by $v_uid
  if ($t_uid != '') {
    $query->condition('t.uid_entered', $t_uid);
  }
  if ($v_uid != '') {
    if (!$query->hasTag('join-with-votes'))  $query->addTag('join-with-votes');
    $query->condition('v.uid', $v_uid);
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
function _l10n_suggestions_filter_by_date($query, $date_filter, $from_date, $to_date) {

  //convert $from_date and $to_date to the string format YYYY-MM-DD
  $from_date_str = date('Y-m-d', mktime(1, 0, 0, $from_date['month'], $from_date['day'], $from_date['year']));
  $to_date_str = date('Y-m-d', mktime(1, 0, 0, $to_date['month'], $to_date['day'], $to_date['year']));

  //get the current date in the standard string format 'YYYY-MM-DD'
  $today_str = date('Y-m-d');

  //if the date of votes has to be checked, then the table of votes must be joined
  if ( ($date_filter == 'votes')
    && !($from_date_str == $today_str && $to_date_str == $today_str)) {
    if (!$query->hasTag('join-with-votes'))  $query->addTag('join-with-votes');
  }

  //get the alias (name) of the date field that has to be checked
  $field =
    ($date_filter=='strings') ? 'p.registration_time' :
    ($date_filter=='votes')   ? 'v.vtime' :
    't.time_entered';

  //add to query the propper date condition;
  //if none of the dates are given, no condition is added
  if ($from_date_str != $today_str and $to_date_str != $today_str) {
    $query->condition($field, array($from_date_str, $to_date_str), 'BETWEEN');
  }
  else if ($from_date_str == $today_str and $to_date_str != $today_str) {
    $query->condition($field, $to_date_str, '<=');
  }
  else if ($from_date_str != $today_str and $to_date_str == $today_str) {
    $query->condition($field, $from_date_str, '>=');
  }
  else {
    //do nothing
  }

}

?>