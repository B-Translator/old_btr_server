<?php

/**
 * Return a sguid from the strings that should be voted.
 * This string is selected according to the preferencies
 * of the given user. If no uid is given as parameter,
 * then the current user is assumed.
 */
function btr_sguid_get_next($uid =NULL) {

  // get the string-order preference for the user
  if ($uid == NULL)  { $uid = $GLOBALS['user']->uid; }
  $string_order = btr_ui_get_string_order(user_load($uid));

  // select the string according to the string-order preference
  switch ($string_order) {
    default:
    case 'random':
      $sguid = btr_sguid_get_random($uid);
      break;

    case 'sequential':
      $sguid = btr_sguid_get_sequential($uid);
      break;
  }

  return $sguid;
}

/**
 * Return a sequential sguid from the preferred projects of the user.
 */
function btr_sguid_get_sequential($uid =NULL) {

  // get the sequential data
  if ($uid == NULL)  { $uid = $GLOBALS['user']->uid; }
  $account = user_load($uid);
  $sequential = btr_ui_get_data_sequential($account);

  // if sequential data are not set, then just return a random sguid
  if ($sequential == NULL) {
    drupal_set_message(t(
        "It seems that there is something wrong with your preferences. Please <a href='@edit-profile'>check your profile</a>.",
        array('@edit-profile' => "/user/$uid/edit-profile")),
      'warning');
    return btr_sguid_get_random($uid);
  }

  $lid = $sequential->lid;
  $idx = $sequential->idx;
  $proj = $sequential->projects[$idx];

  // get the id of the next string location
  $lid++;
  if ($lid > $proj->lmax) {
    $idx++;
    if ($idx >= sizeof($sequential->projects)) {
      drupal_set_message(t(
          "You have reached the end of the preferred project. Please <a href='@edit-profile'>visit your profile</a> and modify them.",
        array('@edit-profile' => '/user/$uid/edit-profile')),
      'status');
      return btr_sguid_get_random($uid);
    }
    $proj = $sequential->projects[$idx];
    $lid = $proj->lmin;
  }

  // save the new index of the object $sequential
  $sequential->lid = $lid;
  $sequential->idx = $idx;
  //dpm($sequential);  //debug
  $edit['field_data_sequential']['und'][0]['value'] = serialize($sequential);
  $edit['skip_presave'] = TRUE;
  user_save($account, $edit);

  // get and return the sguid
  $query = 'SELECT sguid FROM {btr_locations} WHERE lid=:lid';
  $args = array(':lid' => $lid);
  $sguid = $GLOBALS['btr_db']->query($query, $args)->fetchField();
  return $sguid;
}

/**
 * Return a random sguid from the given user.
 * This random string is selected from the list
 * of the preferred projects of the user.
 */
function btr_sguid_get_random($uid =NULL) {
  $db = $GLOBALS['btr_db'];

  // get the list of preferred projects of the user
  if ($uid == NULL)  { $uid = $GLOBALS['user']->uid; }
  $projects = btr_ui_get_preferred_projects(user_load($uid));

  // build the WHERE condition for selecting projects
  list($where, $args) = _btr_projects_to_where_condition($projects);
  if ($where == '')  $where = '(1=1)';

  // Get the total number of strings from which we can choose.
  $sql_count = "
    SELECT COUNT(*) AS number_of_strings
    FROM (SELECT pguid FROM {btr_projects} WHERE $where) p
    LEFT JOIN {btr_templates} tpl ON (tpl.pguid = p.pguid)
    LEFT JOIN {btr_locations} l ON (l.potid = tpl.potid)
    LEFT JOIN {btr_strings} s ON (s.sguid = l.sguid)
  ";
  $nr_strings = $db->query($sql_count, $args)->fetchField();

  // Get a random row number.
  $random_row_number = rand(0, $nr_strings - 1);

  // Get the sguid of the random row.
  $sql_get_sguid = "
    SELECT s.sguid
    FROM (SELECT pguid FROM {btr_projects} WHERE $where) p
    LEFT JOIN {btr_templates} tpl ON (tpl.pguid = p.pguid)
    LEFT JOIN {btr_locations} l ON (l.potid = tpl.potid)
    LEFT JOIN {btr_strings} s ON (s.sguid = l.sguid)
    LIMIT $random_row_number, 1
  ";
  //dpm($sql_get_sguid, 'sql_get_sguid');  dpm($args, 'sql_get_sguid_args');  //debug
  $sguid = $db->query($sql_get_sguid, $args)->fetchField();

  return $sguid;
}

/**
 * Return a random untranslated sguid from the preferred projects
 * of the given user.
 */
function btr_sguid_get_untranslated($uid =NULL) {
  $db = $GLOBALS['btr_db'];

  // get the preferred projects and the translation language of the user
  if ($uid == NULL) {
    $uid = $GLOBALS['user']->uid;
  }
  $projects = btr_ui_get_preferred_projects(user_load($uid));
  $lng = variable_get('btr_translation_lng', 'fr');

  // build the WHERE condition for selecting projects
  list($where, $args) = _btr_projects_to_where_condition($projects);
  $args[':lng'] = $lng;
  if ($where == '')  $where = '(1=1)';

  // Get the total number of strings from which we can choose.
  $sql_count = "
    SELECT COUNT(*) AS number_of_strings
    FROM (SELECT pguid FROM {btr_projects} WHERE $where) p
    LEFT JOIN {btr_templates} tpl ON (tpl.pguid = p.pguid)
    LEFT JOIN {btr_locations} l ON (l.potid = tpl.potid)
    LEFT JOIN {btr_strings} s ON (s.sguid = l.sguid)
    LEFT JOIN {btr_translations} t ON (t.sguid = s.sguid AND t.lng = :lng)
    WHERE t.sguid IS NULL
  ";
  $nr_strings = $db->query($sql_count, $args)->fetchField();

  // Get the sguid of a random untranslated. 'count' keeps in how many projects
  // a string appears. Ordering by 'count' and getting a random string
  // from the top, we try to get an untranslated string that appears
  // in other projects as well.
  $random_row_number = rand(0, ceil($nr_strings/3));
  $sql_get_sguid = "
    SELECT s.sguid
    FROM (SELECT pguid FROM {btr_projects} WHERE $where) p
    LEFT JOIN {btr_templates} tpl ON (tpl.pguid = p.pguid)
    LEFT JOIN {btr_locations} l ON (l.potid = tpl.potid)
    LEFT JOIN {btr_strings} s ON (s.sguid = l.sguid)
    LEFT JOIN {btr_translations} t ON (t.sguid = s.sguid AND t.lng = :lng)
    WHERE t.sguid IS NULL
    ORDER BY s.count DESC
    LIMIT $random_row_number, 1
  ";
  //dpm($sql_get_sguid, 'sql_get_sguid');  dpm($args, 'sql_get_sguid_args');  //debug
  $sguid = $db->query($sql_get_sguid, $args)->fetchField();

  return $sguid;
}


/**
 * Return a random translated sguid from the preferred projects
 * of the given user.
 */
function btr_sguid_get_translated($uid =NULL) {
  $db = $GLOBALS['btr_db'];

  // get the preferred projects and the translation language of the user
  if ($uid == NULL) {
    $uid = $GLOBALS['user']->uid;
  }
  $projects = btr_ui_get_preferred_projects(user_load($uid));
  $lng = variable_get('btr_translation_lng', 'fr');

  // build the WHERE condition for selecting projects
  list($where, $args) = _btr_projects_to_where_condition($projects);
  $args[':lng'] = $lng;
  if ($where == '')  $where = '(1=1)';

  // Get the total number of strings from which we can choose.
  $sql_count = "
    SELECT COUNT(*) AS number_of_strings
    FROM ( SELECT DISTINCT s.sguid
	   FROM (SELECT pguid FROM {btr_projects} WHERE $where) p
	   LEFT JOIN {btr_templates} tpl ON (tpl.pguid = p.pguid)
	   LEFT JOIN {btr_locations} l ON (l.potid = tpl.potid)
	   LEFT JOIN {btr_strings} s ON (s.sguid = l.sguid)
	   LEFT JOIN {btr_translations} t ON (t.sguid = s.sguid AND t.lng = :lng)
	   WHERE t.sguid IS NOT NULL
         )  AS st
  ";
  $nr_strings = $db->query($sql_count, $args)->fetchField();

  // Get the sguid of a random translated string. We sort strings
  // by the number of translations they have, and try to select one
  // that has many translations and/or many votes.
  $random_row_number = rand(0, ceil($nr_strings/5));
  $sql_get_sguid = "
    SELECT sguid
    FROM ( SELECT s.sguid
	   FROM (SELECT pguid FROM {btr_projects} WHERE $where) p
	   LEFT JOIN {btr_templates} tpl ON (tpl.pguid = p.pguid)
	   LEFT JOIN {btr_locations} l ON (l.potid = tpl.potid)
	   LEFT JOIN {btr_strings} s ON (s.sguid = l.sguid)
	   LEFT JOIN {btr_translations} t ON (t.sguid = s.sguid AND t.lng = :lng)
	   WHERE t.sguid IS NOT NULL
           GROUP BY s.sguid
           ORDER BY (count(*) + sum(t.count)) DESC
         )  AS st
    LIMIT $random_row_number, 1
  ";
  //dpm($sql_get_sguid, 'sql_get_sguid');  dpm($args, 'sql_get_sguid_args');  //debug
  $sguid = $db->query($sql_get_sguid, $args)->fetchField();

  return $sguid;
}
