<?php

/**
 * Returns a sguid for targets: next|translated|untranslated.
 *
 * @param $lng
 *   Useful for 'translated' and 'untranslated' targets.
 *   If not provided, a default language will be used.
 *
 * @param $projects
 *   Array of scope projects, where each project is in the form
 *   'origin/project' or 'origin'. If provided, will be used
 *   to restrict the pool of selection (in addition to the preferred
 *   projects of the user).
 *
 * @return
 *   The sguid of a randomly selected string, according to the
 *   given parameters and to the preferencies of the user.
 */
function btr_get_random_sguid($target, $lng =NULL, $projects =NULL) {
  switch ($target) {
    default:
    case 'next':
      $sguid = btr_sguid_get_next($uid=NULL, $projects);
      break;
    case 'translated':
      $sguid = btr_sguid_get_translated($lng, $uid=NULL, $projects);
      break;
    case 'untranslated':
      $sguid = btr_sguid_get_untranslated($lng, $uid=NULL, $projects);
      break;
  }
  return $sguid;
}

/**
 * Return a sguid from the strings that should be reviewed.
 *
 * @param $uid
 *   Select according to the preferencies of this user.
 *   If no $uid is given, then the current user is assumed.
 *
 * @param $projects
 *   Array of projects to restrict selection.
 *
 * @return
 *   The sguid of another string.
 */
function btr_sguid_get_next($uid =NULL, $projects =NULL) {

  // get the string-order preference for the user
  if ($uid == NULL)  { $uid = $GLOBALS['user']->uid; }
  $account = user_load($uid);
  $string_order = $account->string_order;

  // select the string according to the string-order preference
  switch ($string_order) {
    default:
    case 'random':
      $sguid = btr_sguid_get_random($uid, $projects);
      break;

    case 'sequential':
      $sguid = btr_sguid_get_sequential($uid);
      break;
  }

  return $sguid;
}

/**
 * Return a sequential sguid from the preferred projects of the user.
 *
 * @param $uid
 *   The user whose preferencies will be used.
 *   If no $uid is given, then the current user is assumed.
 *
 * @return
 *   The sguid of the next string in the PO file(s).
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
 * Return a random sguid for the given user.
 *
 * @param $uid
 *   Select according to the preferencies of this user.
 *   If no $uid is given, then the current user is assumed.
 *
 * @param $target_projects
 *   Array of projects to restrict selection.
 *
 * @return
 *   Randomly selected sguid.
 */
function btr_sguid_get_random($uid =NULL, $target_projects =NULL) {
  $db = $GLOBALS['btr_db'];

  // Get the list of projects that will be searched.
  $projects = _btr_get_pool_of_projects($uid, $target_projects);

  // Build the WHERE condition for selecting projects.
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
  $sguid = $db->query($sql_get_sguid, $args)->fetchField();

  return $sguid;
}

/**
 * Get an untranslated sguid from the preferred projects of the given user.
 *
 * @param $lng
 *   Language of translations.
 *
 * @param $uid
 *   Select according to the preferencies of this user.
 *   If no $uid is given, then the current user is assumed.
 *
 * @param $target_projects
 *   Array of projects to restrict selection.
 *
 * @return
 *   The sguid of a randomly selected untranslated string.
 */
function btr_sguid_get_untranslated($lng, $uid =NULL, $target_projects =NULL) {
  $db = $GLOBALS['btr_db'];

  // Get the list of projects that will be searched.
  $projects = _btr_get_pool_of_projects($uid, $target_projects);

  // Build the WHERE condition for selecting projects.
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
  $sguid = $db->query($sql_get_sguid, $args)->fetchField();

  return $sguid;
}


/**
 * Get a translated sguid from the preferred projects of the given user.
 *
 * @param $lng
 *   Language of translations.
 *
 * @param $uid
 *   Select according to the preferencies of this user.
 *   If no $uid is given, then the current user is assumed.
 *
 * @param $target_projects
 *   Array of projects to restrict selection.
 *
 * @return
 *   The sguid of a randomly selected untranslated string.
 */
function btr_sguid_get_translated($lng, $uid =NULL, $target_projects =NULL) {
  $db = $GLOBALS['btr_db'];

  // Get the list of projects that will be searched.
  $projects = _btr_get_pool_of_projects($uid, $target_projects);

  // Build the WHERE condition for selecting projects.
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
  $sguid = $db->query($sql_get_sguid, $args)->fetchField();

  return $sguid;
}


/**
 * Get projects from which the next string for review will be selected.
 *
 * This is normally the preferred projects of the user, but if user
 * has not defined any preferred projects, then the preferred projects
 * of the site (defined by site admin) will be used. However, if the
 * $scope_projects has been provided, it will be used to restrict (limit)
 * this list of projects.
 *
 * @param $uid
 *   The user whose preferencies will be used.
 *   If no $uid is given, then the current user is assumed.
 *
 * @param $target_projects
 *   Array of projects to restrict the selection.
 *
 * @return
 *   Array of projects that will be used for selecting a string.
 */
function _btr_get_pool_of_projects($uid =NULL, $target_projects =NULL) {
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

  // Use $target_projects to restrict the list of projects.
  if ($target_projects != NULL) {
    $arr_projects = array_intersect($arr_projects, $target_projects);
    if (empty($arr_projects)) {
      $arr_projects = $target_projects;
    }
  }

  return $arr_projects;
}

/**
 * Return an array of the projects that contain the given string.
 *
 * Each item of the array is of the form 'origin/project'.
 */
function btr_get_projects_of_sguid($sguid) {
  if (empty($sguid))  return NULL;

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
  if (empty($projects))  $projects = NULL;

  return $projects;
}
