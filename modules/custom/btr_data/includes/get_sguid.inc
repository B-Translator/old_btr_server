<?php

/**
 * Return a sguid from the strings that should be voted.
 * This string is selected according to the preferencies
 * of the given user. If no uid is given as parameter,
 * then the current user is assumed.
 */
function btr_sguid_get_next($lng, $uid =NULL) {

  // get the string-order preference for the user
  if ($uid == NULL)  { $uid = $GLOBALS['user']->uid; }
  $account = user_load($uid);
  $string_order = $account->string_order;

  // select the string according to the string-order preference
  switch ($string_order) {
    default:
    case 'random':
      $sguid = btr_sguid_get_random($lng, $uid);
      break;

    case 'sequential':
      $sguid = btr_sguid_get_sequential($lng, $uid);
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
  $sequential = $account->data_sequential;

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
          "You have reached the end of the preferred projects. Please <a href='@edit-profile'>visit your profile</a> and modify them.",
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
  //$edit['field_data_sequential']['und'][0]['value'] = serialize($sequential);
  $edit['data_sequential'] = $sequential;
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

  // get the list of projects that will be searched
  $projects = _btr_get_pool_of_projects($uid);

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
function btr_sguid_get_untranslated($lng, $uid =NULL) {
  $db = $GLOBALS['btr_db'];

  // get the list of projects that will be searched
  // and the translation language of the user
  $projects = _btr_get_pool_of_projects($uid);

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
function btr_sguid_get_translated($lng, $uid =NULL) {
  $db = $GLOBALS['btr_db'];

  // get the list of projects that will be searched
  // and the translation language of the user
  $projects = _btr_get_pool_of_projects($uid);

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


/**
 * Return an array of projects from which the next string
 * for the user will be selected. This is normally the
 * preferred projects of the user, but if user has not
 * defined any preferred projects, then the preferred projects
 * of the site (defined by site admin) will be used.
 * However, if the checkbox same_project has been checked,
 * it will further constrain the list of projects to match
 * those of the last string visited.
 */
function _btr_get_pool_of_projects($uid =NULL) {
  if ($uid == NULL)  { $uid = $GLOBALS['user']->uid; }
  $user = user_load($uid);

  $arr_projects = array();
  if (isset($user->preferred_projects)) {
    // get the preferred projects of the user
    $arr_projects = $user->preferred_projects;
  }
  else {
    // get the preferred projects from the site config
    $preferred_projects_txt = variable_get('btr_preferred_projects', '');
    $lines = preg_split('#\r\n|\r|\n#', $preferred_projects_txt);
    foreach ($lines as $line) {
      $line = trim($line);
      if ($line != '') {
        $arr_projects[] = $line;
      }
    }
  }

  // if checkbox same_project is checked, constrain the list
  // of projects by the projects of the last string
  if (isset($_SESSION['same_project']) && $_SESSION['same_project']) {
    $last_projects = _btr_get_projects_of_sguid($_SESSION['sguid']);
    if (!empty($last_projects)) {
      $arr_projects = array_intersect($arr_projects, $last_projects);
      if (empty($arr_projects)) {
	$arr_projects = $last_projects;
      }
    }
  }

  return $arr_projects;
}

/**
 * Return an array of the projects that contain the given string.
 * Each item of the array is of the form 'origin/project'.
 */
function _btr_get_projects_of_sguid($sguid) {
  if (empty($sguid))  return array();

  $args = array(':sguid' => $sguid);
  $get_projects = "
      SELECT p.origin, p.project
      FROM {btr_locations} l
      LEFT JOIN {btr_templates} tpl ON (tpl.potid = l.potid)
      LEFT JOIN {btr_projects} p ON (p.pguid = tpl.pguid)
      WHERE l.sguid = :sguid
  ";
  $db = $GLOBALS['btr_db'];
  $result = $db->query($get_projects, $args)->fetchAll();
  $projects = array();
  foreach ($result as $proj) {
    $projects[] = $proj->origin . '/' . $proj->project;
  }

  return $projects;
}
