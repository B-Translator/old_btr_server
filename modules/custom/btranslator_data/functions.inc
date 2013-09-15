<?php
/**
 * @file
 * Functions called from the user interface.
 */

function btr_get_string_from_id($sguid) {
  $sql = 'SELECT string FROM {btr_strings} WHERE sguid = :sguid';
  $string = $GLOBALS['btr_db']->query($sql, array(':sguid' => $sguid))->fetchField();
  return $string;
}

function btr_get_search_results($filter, $lng) {
  //get a query for selecting strings that match the filter
  $query = btr_build_search_query($filter);
  if (!$query) {
    drupal_set_message(t('Filter is empty. Put something on the filter options.'));
  }
  //dpq($query);  //debug

  //get the strings that match the filter and the corresponding translations
  $strings = btr_get_strings($query, $lng);

  return $strings;
}

function btr_get_strings_from_ids($arr_sguid, $lng, $alternative_langs = array()) {
  $query = $GLOBALS['btr_db']->select('btr_strings', 's')
    ->fields('s', array('sguid'))
    ->condition('s.sguid', $arr_sguid, 'IN');
  return btr_get_strings($filter_query, $lng, $alternative_langs);
}


/**
 * Get the details of strings, translations and votes and return them
 * as an associative array, in a suitable format for being displayed.
 *
 * @param $filter_query
 *   A db_select query object that returns the strings that should be
 *   displayed, in the descending orders of matching scores.
 * @param $lng
 *   Language code of the translations.
 * @param $alternative_langs
 *   Array of alternative (auxiliary) language codes. These languages
 *   are an alternative to English, in case that the translator is not
 *   quite familiar with English or needs some help from another language.
 * @return
 *   An array of strings, translations and votes, where each string
 *   is an associative array, with translations and votes as nested
 *   associative arrays.
 */
function btr_get_strings($filter_query, $lng, $alternative_langs = array()) {

  $db = $GLOBALS['btr_db'];

  //get the IDs of the strings that are returned by the filter query
  $assoc_arr_sguid = $filter_query->execute()->fetchAllAssoc('sguid');
  if (empty($assoc_arr_sguid))  return array();
  $arr_sguid = array_keys($assoc_arr_sguid);

  //get string details
  $get_strings = "
      SELECT sguid, string
      FROM {btr_strings}
      WHERE sguid IN (:arr_sguid)
  ";
  $args = array(':arr_sguid' => $arr_sguid);
  $result = $db->query($get_strings, $args);
  $arr_strings = $result->fetchAllAssoc('sguid');

  //get translations
  $get_translations = "
      SELECT s.sguid, t.tguid, t.lng, t.translation,
             t.time, u.name AS author, u.umail, u.ulng, u.uid, t.count
      FROM {btr_strings} s
      LEFT OUTER JOIN {btr_translations} t ON (s.sguid = t.sguid)
      LEFT OUTER JOIN {btr_users} u ON (u.umail = t.umail AND u.ulng = t.ulng)
      WHERE (t.lng = :lng) AND s.sguid IN (:arr_sguid)
      ORDER BY t.count DESC
  ";
  $args = array(':lng' => $lng, ':arr_sguid' => $arr_sguid);
  $result = $db->query($get_translations, $args);
  $arr_translations = $result->fetchAllAssoc('tguid');

  //get votes
  $arr_tguid = array_keys($arr_translations);
  if (empty($arr_tguid)) {
    $arr_votes = array();
  }
  else {
    $get_votes = "
        SELECT t.tguid, v.vid, u.name, u.umail, u.ulng, u.uid, v.time
        FROM {btr_translations} t
        LEFT OUTER JOIN {btr_votes} v ON (v.tguid = t.tguid)
        LEFT OUTER JOIN {btr_users} u ON (u.umail = v.umail AND u.ulng = v.ulng)
        WHERE t.tguid IN (:arr_tguid)
        ORDER BY v.time DESC
    ";
    $args = array(':arr_tguid' => $arr_tguid);
    $result = $db->query($get_votes, $args);
    $arr_votes = $result->fetchAllAssoc('vid');
  }

  //get alternatives (from other languages)
  //they are the best translations (max count) from the alternative languages
  if (empty($alternative_langs)) {
    $arr_alternatives = array();
  }
  else {
    $get_alternatives = "
        SELECT DISTINCT t.sguid, t.tguid, t.lng, t.translation, t.count
        FROM (SELECT sguid, lng, MAX(count) AS max_count
	      FROM {btr_translations}
	      WHERE lng IN (:arr_lng) AND sguid IN (:arr_sguid)
	      GROUP BY sguid, lng
	      ) AS m
        INNER JOIN {btr_translations} AS t
	      ON m.sguid = t.sguid AND m.lng = t.lng AND m.max_count = t.count
        GROUP BY t.sguid, t.lng, t.count
    ";
    $args = array(':arr_lng' => $alternative_langs, ':arr_sguid' => $arr_sguid);
    $result = $db->query($get_alternatives, $args);
    $arr_alternatives = $result->fetchAllAssoc('tguid');
  }
  //dpm($arr_alternatives, '$arr_alternatives');  //debug

  // Put alternatives as nested array under strings.
  foreach ($arr_alternatives as $tguid => $alternative) {
    $sguid = $alternative->sguid;
    $lng = $alternative->lng;
    $arr_strings[$sguid]->alternatives[$lng] = $alternative->translation;
  }

  // Put votes as nested arrays inside translations.
  // Votes are already ordered by time (desc).
  foreach ($arr_votes as $vid => $vote) {
    $tguid = $vote->tguid;
    $name = $vote->name;
    $arr_translations[$tguid]->votes[$name] = $vote;
  }

  // Put translations as nested arrays inside strings.
  // Translations are already ordered by count (desc).
  // Make sure that each translation has an array of votes
  // (even though it may be empty).
  foreach ($arr_translations as $tguid => $translation) {
    if (!isset($translation->votes))  $translation->votes = array();
    $sguid = $translation->sguid;
    $arr_strings[$sguid]->translations[$tguid] = $translation;
  }

  // Put strings in the same order as $arr_sguid.
  // Make sure as well that each string has an array of translations
  // (even though it may be empty).
  foreach ($arr_sguid as $sguid) {
    $string = $arr_strings[$sguid];
    if (!isset($string->translations)) $string->translations = array();
    if (!isset($string->alternatives)) $string->alternatives = array();
    $strings[$sguid] = $string;
  }

  return $strings;
}


/**
 * Return a string (and its translations) for the given $sguid and $lng.
 * return array($string, $translations)
 */
function btr_get_string_and_translations($sguid, $lng) {
  $db = $GLOBALS['btr_db'];
  $query = $db->select('btr_strings', 's')
    ->fields('s', array('sguid'))
    ->where('s.sguid = :sguid', array(':sguid' => $sguid));
  $strings = btr_get_strings($query, $lng);

  $string = $strings[$sguid]->string;
  $translations = array();
  foreach ($strings[$sguid]->translations as $tguid => $obj_translation) {
    $translations[] = $obj_translation->translation;
  }

  return array($string, $translations);
}


/* ============= user functions ============== */

/**
 * It is called when a new user account is created.
 */
function btr_user_insert($umail, $ulng, $uid, $name, $status) {

  $db = $GLOBALS['btr_db'];

  $args = array(
    ':umail' => $umail,
    ':ulng' => $ulng,
  );
  $select_user = "
    SELECT * FROM {btr_users}
    WHERE umail = :umail AND ulng = :ulng
  ";
  $result = $db->query($select_user, $args);

  $args[':uid'] = $uid;
  $args[':name'] = $name;

  if ($result->rowCount() > 0) {
    btr_user_update($ulng, $uid, $name, $status);
    $update_user = "
      UPDATE {btr_users}
      SET uid = :uid, name = :name, status = 1
      WHERE umail = :umail AND ulng = :ulng
    ";
    $db->query($update_user, $args);
  }
  else {
    $insert_user = "
      INSERT INTO {btr_users} (umail, ulng, uid, name, status)
      VALUES (:umail, :ulng, :uid, :name, 1)
    ";
    $db->query($insert_user, $args);
  }
}


/**
 * It is called after a user account has been updated.
 */
function btr_user_update($ulng, $uid, $name, $status) {
  $args = array(
    ':ulng' => $ulng
    ':uid' => $uid,
    ':name' => $name,
    ':status' => $status,
  );
  $update_user = "
    UPDATE {btr_users}
    SET name = :name, status = :status
    WHERE uid = :uid AND :ulng = ulng
  ";
  $GLOBALS['btr_db']->query($update_user, $args);
}

/**
 * It is called when a user is cancelled or deleted.
 */
function btr_user_disable($ulng, $uid) {
  $args = array(':ulng' => $ulng, ':uid' => $uid);
  $update_user = "
    UPDATE {btr_users}
    SET status = 0
    WHERE uid = :uid AND :ulng = ulng
  ";
  $GLOBALS['btr_db']->query($update_user, $args);
}

/**
 * It is used while cleaning fake (spam) users.
 */
function btr_user_delete($ulng, $uid) {
  $db = $GLOBALS['btr_db'];
  $db->delete('btr_users')
    ->condition('ulng', $ulng)
    ->condition('uid', $uid)
    ->execute();
}

/* ------------------------------------------------------- */


/**
 * For each project on the list, get the min and max location ids
 * and return them in the object $sequential.
 *
 * The data in this object makes it possible for a user to visit
 * the strings of his preferred projects sequentially (in the same
 * order that they appear on the PO file), rather than randomly.
 */
function btr_get_sequential_data($arr_projects) {
  list($where_condition, $args) = _btr_projects_to_where_condition($arr_projects);
  if ($where_condition == '') {
    $sequential = NULL;
  }
  else {
    $get_all_min_and_max_locations = "
      SELECT min(l.lid) AS lmin, max(l.lid) AS lmax
      FROM {btr_locations} l
      RIGHT JOIN {btr_templates} t ON (l.potid = t.potid)
      RIGHT JOIN {btr_projects} p ON (t.pguid = p.pguid)
      WHERE $where_condition
      GROUP BY p.project
    ";
    $result = $GLOBALS['btr_db']->query($get_all_min_and_max_locations, $args);
    $sequential->projects = $result->fetchAll();
    $sequential->idx = 0;
    $sequential->lid = $sequential->projects[0]->lmin;
  }
  return $sequential;
}


/**
 * Return an array of a WHERE condition for SQL queries, and arguments
 * that are used in it. These can be used in a db_query() for selecting
 * all the projects specified in the given parameter.
 *
 * The parameter is an array of project specifications, where each item is
 * in the form of either 'origin/project', or in the form of 'origin' (which
 * includes all the projects from this origin).
 */
function _btr_projects_to_where_condition($arr_projects) {

  $arr_conditions = array();
  $arguments = array();
  $arg_origin  = ':origin01';
  $arg_project = ':project01';

  foreach ($arr_projects as $proj) {
    $parts = preg_split('#/#', $proj, 2);
    if (sizeof($parts)==2) {
      list($origin, $project) = $parts;
      $arguments[$arg_origin] = $origin;
      $arguments[$arg_project] = $project;
      $arr_conditions[] = "(origin=$arg_origin AND project=$arg_project)";
      $arg_origin++;  $arg_project++;
    }
    else {
      $origin = $parts[0];
      $arguments[$arg_origin] = $origin;
      $arr_conditions[] = "(origin=$arg_origin)";
      $arg_origin++;
    }
  }
  $where_condition = implode(' OR ', $arr_conditions);

  return array($where_condition, $arguments);
}


/**
 * Return an array of the projects that contain the given string.
 * Each item of the array is of the form 'origin/project'.
 */
function btr_get_projects($sguid) {
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


/* ==================== get a sguid ======================== */

/**
 * Return a random sguid from the given list of projects.
 */
function btr_get_random_sguid($projects) {
  $db = $GLOBALS['btr_db'];

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
 * Return a random untranslated sguid from the given list of projects.
 */
function btr_get_untranslated_sguid($projects, $lng) {
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
 * Return a random translated sguid from the given list of projects.
 */
function btr_get_translated_sguid($projects, $lng) {
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
 * Get the sguid corresponding to the given location id (lid).
 */
function btr_get_sguid_from_lid($lid) {
  $query = 'SELECT sguid FROM {btr_locations} WHERE lid=:lid';
  $args = array(':lid' => $lid);
  $sguid = $GLOBALS['btr_db']->query($query, $args)->fetchField();
  return $sguid;
}