<?php
/**
 * @file
 * Functions called from the user interface.
 */

function btr_query($sql, $args) {
  return $GLOBALS['btr_db']->query($sql, $args);
}

function btr_get_string($sguid) {
  $sql = 'SELECT string FROM {btr_strings} WHERE sguid = :sguid';
  $args = array(':sguid' => $sguid);
  $string = $GLOBALS['btr_db']->query($sql, $args)->fetchField();
  return $string;
}

function btr_get_translation($tguid) {
  $sql = 'SELECT translation FROM {btr_translations} WHERE tguid = :tguid';
  $args = array(':tguid' => $tguid);
  $translation = $GLOBALS['btr_db']->query($sql, $args)->fetchField();
  return $translation;
}

function btr_get_search_results($filter, $lng) {
  //get a query for selecting strings that match the filter
  $query = btr_build_search_query($filter);
  if (!$query) {
    drupal_set_message(t('Filter is empty. Put something on the filter options.'));
  }
  //dpq($query);  //debug

  //get the strings that match the filter and the corresponding translations
  $strings = btr_get_query_strings($query, $lng);

  return $strings;
}

function btr_get_strings($arr_sguid, $lng, $alternative_langs = array()) {
  $query = $GLOBALS['btr_db']->select('btr_strings', 's')
    ->fields('s', array('sguid'))
    ->condition('s.sguid', $arr_sguid, 'IN');
  return btr_get_query_strings($filter_query, $lng, $alternative_langs);
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
function btr_get_query_strings($filter_query, $lng, $alternative_langs = array()) {

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
  $strings = btr_get_query_strings($query, $lng);

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

/* ----------------------------------------------------- */

/**
 * Add a new term to the vocabulary.
 * Return the sguid of the new term,
 * or NULL if such a term already exists.
 */
function btr_add_term($string) {
  $context = 'vocabulary';
  $sguid = sha1($string . $context);

  $db = $GLOBALS['btr_db'];

  // check whether this string already exists or not
  $query = "SELECT sguid FROM {btr_strings} WHERE sguid = :sguid";
  $args = array(':sguid' => $sguid);
  $field = $db->query($query, $args)->fetchField();
  if (!empty($field)) {
    drupal_set_message(t('This term already exists.'));
    return NULL;
  }

  // insert the new string
  $db->insert('btr_strings')
    ->fields(array(
        'string' => $string,
        'context' => $context,
        'sguid' => $sguid,
        'uid' => 1,
        'time' => date('Y-m-d H:m:s'),
        'count' => 1,
      ))
    ->execute();

  // get the template id
  $origin = 'misc';
  $project = 'vocabulary';
  $potname = 'vocabulary';
  $potid = $db->select('btr_templates', 't')
    ->fields('t', array('potid'))
    ->condition('pguid', sha1($origin . $project))
    ->condition('tplname', $potname)
    ->execute()
    ->fetchField();

  // insert a new location
  $db->insert('btr_locations')
    ->fields(array(
        'sguid' => $sguid,
        'potid' => $potid,
      ))
    ->execute();

  return $sguid;
}


/**
 * Delete the term with the given id.
 */
function btr_del_term($sguid) {
  $db = $GLOBALS['btr_db'];
  $db->delete('btr_strings')->condition('sguid', $sguid)->execute();
  $db->delete('btr_locations')->condition('sguid', $sguid)->execute();
  $db->delete('btr_translations')->condition('sguid', $sguid)->execute();
}

/* --------------- statistics -------------------- */

/**
 * Return a list of top contributing users
 * from the given date until now.
 * This is used for example on the block topcontrib.
 *
 * @param $lng
 *     Language of contributions (for example sq).
 * @param $from_date
 *     Starting date for calculations, in the format Y-m-d.
 * @param $size
 *     Number of top users to return.
 * @return
 *     Array of users, where each user is an object
 *     with these attributes:
 *         uid, name, umail, score, translations, votes
 */
function btr_stat_topcontrib($lng, $from_date, $size) {

  $cache = cache_get("btr_stat_topcontrib:$lng", 'cache_btr');
  // Return cache if possible.
  if (!empty($cache) && isset($cache->data) && !empty($cache->data)) {
    return $cache->data;
  }

  // Give weight 5 to a translation and weight 1 to a vote,
  // get the sum of all the weights grouped by user (umail),
  // order by this score, and get the top users.
  $sql_get_topcontrib = "
    SELECT u.uid, u.name, u.umail, sum(w.weight) AS score,
           sum(w.translation) AS translations, sum(w.vote) AS votes
    FROM (
       (
         SELECT t.umail, 5 AS weight,
                1 AS translation, 0 AS vote
         FROM {btr_translations} t
         WHERE ulng = :lng AND time > :from_date
           AND umail!='admin@example.com'
       )
       UNION ALL
       (
         SELECT v.umail, 1 AS weight,
                0 AS translation, 1 AS vote
         FROM {btr_votes} v
         WHERE ulng = :lng AND time > :from_date
           AND umail!='admin@example.com'
       )
    ) AS w
    LEFT JOIN {btr_users} u
           ON (u.ulng = :lng AND u.umail = w.umail)
    GROUP BY w.umail
    ORDER BY score DESC
  ";
  $args = array(':lng' => $lng, ':from_date' => $from_date);
  $db = $GLOBALS['btr_db'];
  $topcontrib = $db->queryRange($sql_get_topcontrib, 0, $size, $args)->fetchAll();

  // Cache for 12 hours.
  cache_set("btr_stat_topcontrib:$lng", $topcontrib, 'cache_btr', time() + 12*60*60);

  return $topcontrib;
}


/**
 * Return an array of the statistics (number of votes
 * and translations) for the last week, month and year.
 */
function btr_statistics($lng) {

  $cache = cache_get("btr_statistics:$lng", 'cache_btr');
  // Return cache if possible.
  if (!empty($cache) && isset($cache->data) && !empty($cache->data)) {
    return $cache->data;
  }

  $db = $GLOBALS['btr_db'];

  $sql_count_translations = "SELECT count(*) as cnt FROM {btr_translations}
                             WHERE ulng = :lng AND time >= :from_date
                               AND umail NOT IN ('admin@example.com', 'admin@btranslator.org', '')";
  $sql_count_votes = "SELECT count(*) as cnt FROM {btr_votes}
                      WHERE ulng = :lng AND time >= :from_date";

  $stats = array();

  foreach (array('week', 'month', 'year') as $period) {
    $from_date = date('Y-m-d', strtotime("-1 $period"));
    $args = array(':lng' => $lng, ':from_date' => $from_date);
    $nr_votes = $db->query($sql_count_votes, $args)->fetchField();
    $nr_translations = $db->query($sql_count_translations, $args)->fetchField();

    $stats[$period] = array(
      'period' => $period,
      'from_date' => $from_date,
      'nr_votes' => $nr_votes,
      'nr_translations' => $nr_translations,
    );
  }

  // Cache for 12 hours.
  cache_set("btr_statistics:$lng", $stats, 'cache_btr', time() + 12*60*60);

  return $stats;
}

/* ------------------ votes and translations ----------------- */

/**
 * Add a vote for the given translation from the given user.
 * Make sure that any previous vote is cleaned first
 * (don't allow multiple votes for the same translation).
 *
 * @param $tguid
 *   ID of the translation.
 * @param $umail
 *   The user email.
 * @param $ulng
 *   The language of the user.
 * @return
 *   The ID of the new vote, or NULL.
 */
function btr_add_vote($tguid, $umail, $ulng) {
  // Fetch the translation details from the DB.
  $db = $GLOBALS['btr_db'];
  $sql = 'SELECT * FROM {btr_translations} WHERE tguid = :tguid';
  $args = array(':tguid' => $tguid);
  $trans = $db->query($sql, $args)->fetchObject();

  // If there is no such translation, return NULL.
  if (empty($trans))  return NULL;

  // Clean any previous vote.
  $nr = _btr_clean_previous_votes($tguid, $umail, $trans->sguid, $trans->lng);

  // Add the vote.
  $vid = $db->insert('btr_votes')
    ->fields(array(
        'tguid' => $tguid,
        'umail' => $umail,
        'ulng' => $ulng,
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();

  // Update vote count of the translation.
  $sql = 'SELECT COUNT(*) FROM {btr_votes} WHERE tguid = :tguid';
  $count = $db->query($sql, $args)->fetchField();
  $db->update('btr_translations')
    ->fields(array('count' => $count))
    ->condition('tguid', $tguid)
    ->execute();

  return $vid;
}


/**
 * Clean any previous vote by this user for this translation.
 *
 * This depends on the voting mode option (set by the admin).
 * If the voting mode is 'single', then the user can select
 * only one translation for a given string (at most one vote
 * per string).
 * If the voting mode is 'multiple', then the user can approve
 * several translations for a string (at most one vote per
 * translation).
 *
 * @param $tguid
 *   ID of the translation.
 * @param $umail
 *   The mail of the user.
 * @param $sguid
 *   ID of the source string.
 * @param $lng
 *   Language code of the translation.
 * @return
 *   Number of previous votes that were deleted.
 *   (Normally should be 0, but can also be 1. If it is >1,
 *   something must be wrong.)
 */
function _btr_clean_previous_votes($tguid, $umail, $sguid, $lng) {

  $db = $GLOBALS['btr_db'];

  // Get the voting mode.
  $voting_mode = variable_get('btr_voting_mode', 'single');

  $arr_tguid = array();
  if ($voting_mode == 'multiple') {
    $arr_tguid = array($tguid);
  }
  else { // ($voting_mode == 'single')
    // Get the other sibling translations (translations of the same
    // string and the same language) which the user has voted.
    $sql = '
      SELECT DISTINCT t.tguid FROM {btr_translations} t
      LEFT JOIN {btr_votes} v ON (v.tguid = t.tguid)
      WHERE t.sguid = :sguid AND t.lng = :lng AND v.umail = :umail AND v.ulng = :ulng
    ';
    $params = array(':sguid' => $sguid, ':lng' => $lng, ':umail' => $umail, ':ulng' => $lng);
    $arr_tguid = $db->query($sql, $params)->fetchCol();
  }

  if (empty($arr_tguid))  return 0;

  // Insert to the trash table the votes that will be removed.
  $query = $db->select('btr_votes', 'v')
    ->fields('v', array('vid', 'tguid', 'umail', 'ulng', 'time', 'active'))
    ->condition('umail', $umail)
    ->condition('ulng', $lng)
    ->condition('tguid', $arr_tguid, 'IN');
  $query->addExpression('NOW()', 'd_time');
  $db->insert('btr_votes_trash')->from($query)->execute();

  // Remove any votes by the user for each translation in $arr_tguid.
  $num_deleted = $db->delete('btr_votes')
    ->condition('umail', $umail)
    ->condition('ulng', $lng)
    ->condition('tguid', $arr_tguid, 'IN')
    ->execute();

  // Decrement the vote count for each translation in $arr_tguid.
  $num_updated = $db->update('btr_translations')
    ->expression('count', 'count - 1')
    ->condition('tguid', $arr_tguid, 'IN')
    ->execute();

  return $num_deleted;
}


/**
 * Add a new translation to a source string.
 *
 * @param $sguid
 *   The string ID for which a new translation should be added.
 * @param $lng
 *   The language (code) of the new translation.
 * @param $translation
 *   The new translation as a string. If the string has plural
 *   version(s) as well, they are concatenated with NULL bytes ("\0")
 *   between them.
 * @param $umail
 *   The email of the author of the translation.
 * @param $single
 *   If false, then the user can add more then one translation
 *   for the same string.
 * @return
 *   Returns the ID of the new translation ($tguid),
 *   or FALSE if no translation was added.
 */
function btr_add_translation($sguid, $lng, $translation, $umail, $single =TRUE) {
  // Don't add empty translations.
  if (trim($translation) == '')  return NULL;

  $db = $GLOBALS['btr_db'];

  // Make spacing and newlines the same in translation as in the source.
  $string = btr_get_string($sguid);
  $matches = array();
  preg_match("/^(\s*).*\S(\s*)\$/s", $string, $matches);
  $translation = $matches[1] . trim($translation) . $matches[2];

  // Look for an existing translation, if any.
  $tguid = sha1($translation . $lng . $sguid);
  $existing = btr_get_translation($tguid);

  // If this translation already exists, there is nothing to be added.
  if (!empty($existing))  return NULL;

  // Insert the new suggestion.
  $db->insert('btr_translations')
    ->fields(array(
        'sguid' => $sguid,
        'lng' => $lng,
        'translation' => $translation,
        'tguid' => $tguid,
        'count' => 1,
        'umail' => $umail,
        'ulng' => $lng,
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();

  if ($single) {
    // If there is another translation for the same string, by the same user,
    // the new translation should replace the old one. This is useful when
    // the user wants to correct the translation, but it limits the user to
    // only one suggested translation per string. If $single is FALSE, then
    // this limitation does not apply.
    _btr_remove_old_translation($sguid, $lng, $umail, $tguid);
  }

  // Add also a vote for the new translation.
  $vid = btr_add_vote($tguid, $umail, $lng);

  // Notify previous voters of this string that a new translation has been
  // suggested. Maybe they would like to review it and change their vote.
  _btr_notify_voters_on_new_translation($sguid, $lng, $tguid, $string, $translation);

  return $tguid;
}


/**
 * If there is another translation for the same string, by the same user,
 * the new translation should replace the old one. This is useful when
 * the user wants to correct the translation, but it limits the user to
 * only one suggested translation per string.
 *
 * @param $sguid
 *   Id of the string being translated.
 * @param $lng
 *   Language of translation.
 * @param $umail
 *   Email that identifies the user who made the translation.
 * @param $tguid
 *   Id of the new translation.
 */
function _btr_remove_old_translation($sguid, $lng, $umail, $tguid) {
  $db = $GLOBALS['btr_db'];

  // Get the old translation (if any).
  $query = 'SELECT tguid, translation
            FROM {btr_translations}
            WHERE sguid = :sguid AND lng = :lng
              AND umail = :umail AND ulng = :ulng
              AND tguid != :tguid';
  $args = array(
    ':sguid' => $sguid,
    ':lng' => $lng,
    ':umail' => $umail,
    ':ulng' => $lng,
    ':tguid' => $tguid);
  $old_trans = $db->query($query, $args)->fetchObject();
  if (!$old_trans)  return;  // if there is no old translation, we are done

  // Copy to the trash table the old translation.
  $query = $db->select('btr_translations', 't')
    ->fields('t', array('sguid', 'lng', 'translation', 'tguid', 'count', 'umail', 'ulng', 'time', 'active'))
    ->condition('tguid', $old_trans->tguid);
  $query->addExpression(':d_umail', 'd_umail', array(':d_umail' => $umail));
  $query->addExpression(':d_ulng', 'd_ulng', array(':d_ulng' => $lng));
  $query->addExpression('NOW()', 'd_time');
  $db->insert('btr_translations_trash')->from($query)->execute();

  // Remove the old translation.
  $db->delete('btr_translations')
    ->condition('tguid', $old_trans->tguid)
    ->execute();

  // Get the votes of the old translation.
  $query = "SELECT v.tguid, v.time, u.umail, u.ulng, u.uid,
                   u.name AS user_name, u.status AS user_status
            FROM {btr_votes} v
            LEFT JOIN {btr_users} u ON (u.umail = v.umail AND u.ulng = v.ulng)
            WHERE v.tguid = :tguid AND v.umail != :umail";
  $args = array(':tguid' => $old_trans->tguid, ':umail' => $umail);
  $votes = $db->query($query, $args)->fetchAll();

  // Insert to the trash table the votes that will be deleted.
  $query = $db->select('btr_votes', 'v')
    ->fields('v', array('vid', 'tguid', 'umail', 'ulng', 'time', 'active'))
    ->condition('tguid', $old_trans->tguid);
  $query->addExpression('NOW()', 'd_time');
  $db->insert('btr_votes_trash')->from($query)->execute();

  // Delete the votes belonging to the old translation.
  $db->delete('btr_votes')->condition('tguid', $old_trans->tguid)->execute();

  // Associate these votes to the new translation.
  $notification_list = array();
  foreach ($votes as $vote) {
    // Associate the vote to the new translation.
    $db->insert('btr_votes')
      ->fields(array(
          'tguid' => $tguid,
          'umail' => $vote->umail,
          'ulng' => $vote->ulng,
          'time' => $vote->time,
        ))
      ->execute();

    if ($vote->user_status != 1)  continue;   // skip non-active voters

    // Add voter to the notification list.
    $notification_list[$uid] = array(
      'uid' => $uid,
      'name' => $vote->user_name,
      'umail' => $vote->umail,
    );
  }

  _btr_notify_voters_on_translation_change($notification_list, $sguid, $old_trans->translation, $tguid);
}

/**
 * Notify the voters of a translation that the author has changed
 * the translation and their votes count now for the new translation.
 */
function _btr_notify_voters_on_translation_change($voters, $sguid, $old_translation, $tguid) {

  if (empty($voters))  return;

  $string = btr_get_string($sguid);
  $new_translation = btr_get_translation($tguid);

  $notifications = array();
  foreach ($voters as $uid => $voter) {
    $notification = array(
      'type' => 'notify-voter-on-translation-change',
      'uid' => $voter['uid'],
      'username' => $voter['name'],
      'recipient' => $voter['name'] . ' <' . $voter['umail'] . '>',
      'sguid' => $sguid,
      'string' => $string,
      'old_translation' => $old_translation,
      'new_translation' => $new_translation,
    );
    $notifications[] = $notification;
  }

  btr_queue_notifications($notifications);
}

/**
 * Notify the previous voters of a string that a new translation has been
 * submitted. Maybe they would like to review it and change their vote.
 */
function _btr_notify_voters_on_new_translation($sguid, $lng, $tguid, $string, $translation) {

  $db = $GLOBALS['btr_db'];
  $query = "SELECT u.umail, u.ulng, u.uid, u.name, u.status, t.translation
            FROM {btr_translations} t
            LEFT JOIN {btr_votes} v ON (v.tguid = t.tguid)
            LEFT JOIN {btr_users} u ON (u.umail = v.umail AND u.ulng = v.ulng)
            WHERE t.sguid = :sguid AND t.lng = :lng AND t.tguid != :tguid";
  $args = array(':sguid' => $sguid, ':lng' => $lng, ':tguid' => $tguid);
  $voters = $db->query($query, $args)->fetchAll();

  if (empty($voters))  return;

  $notifications = array();
  foreach ($voters as $voter) {
    $notification = array(
      'type' => 'notify-voter-on-new-translation',
      'uid' => $voter->uid,
      'username' => $voter->name,
      'recipient' => $voter->name . ' <' . $voter->umail . '>',
      'sguid' => $sguid,
      'string' => $string,
      'voted_translation' => $voter->translation,
      'new_translation' => $translation,
    );
    $notifications[] = $notification;
  }

  btr_queue_notifications($notifications);
}


/**
 * Delete the translation with the given id and any related votes.
 *
 * Parameters $umail and $ulng identify the user that is making
 * the deletion.
 */
function btr_del_translation($tguid, $umail, $ulng) {
  $db = $GLOBALS['btr_db'];

  // Before deleting, get the author and voters (for notifications).
  list($author, $voters) = _btr_get_author_and_voters($tguid);

  // Copy to the trash table the translation that will be deleted.
  $query = $db->select('btr_translations', 't')
    ->fields('t', array('sguid', 'lng', 'translation', 'tguid', 'count', 'umail', 'ulng', 'time', 'active'))
    ->condition('tguid', $tguid);
  $query->addExpression(':d_umail', 'd_umail', array(':d_umail' => $umail));
  $query->addExpression(':d_ulng', 'd_ulng', array(':d_ulng' => $ulng));
  $query->addExpression('NOW()', 'd_time');
  $db->insert('btr_translations_trash')->from($query)->execute();

  // Copy to the trash table the votes that will be deleted.
  $query = $db->select('btr_votes', 'v')
    ->fields('v', array('vid', 'tguid', 'umail', 'ulng', 'time', 'active'))
    ->condition('tguid', $tguid);
  $query->addExpression('NOW()', 'd_time');
  $db->insert('btr_votes_trash')->from($query)->execute();

  // Delete the translation and any votes related to it.
  $db->delete('btr_translations')->condition('tguid', $tguid)->execute();
  $db->delete('btr_votes')->condition('tguid', $tguid)->execute();

  // Notify the author of a translation and its voters
  // that it has been deleted.
  _btr_notify_voters_on_translation_del($tguid, $author, $voters);
}

/**
 * Before deleting a translation, get the author and voters (for notifications).
 */
function _btr_get_author_and_voters($tguid) {
  $get_author =
    "SELECT u.uid, u.name, u.umail
     FROM {btr_translations} t
     LEFT JOIN {btr_users} u
         ON (u.umail = t.umail AND u.ulng = t.ulng)
     WHERE t.tguid = :tguid";

  $get_voters =
    "SELECT u.uid, u.name, u.umail
     FROM {btr_votes} v
     LEFT JOIN {btr_users} u
         ON (u.umail = v.umail AND u.ulng = v.ulng)
     WHERE v.tguid = :tguid";

  $args = array(':tguid' => $tguid);

  $author = $db->query($get_author, $args)->execute()->fetchObject();
  $voters = $db->query($get_voters, $args)->execute()->fetchAll();

  return array($author, $voters);
}


/**
 * Notify the author of a translation and its voters
 * that it has been deleted.
 */
function _btr_notify_voters_on_translation_del($tguid, $author, $voters) {
  // get the sguid, string and translation
  $sql = 'SELECT sguid FROM {btr_translations} WHERE tguid = :tguid';
  $args = array(':tguid' => $tguid);
  $sguid = $GLOBALS['btr_db']->query($sql, $args)->fetchField();
  $string = btr_get_string($sguid);
  $translation = btr_get_translation($tguid);

  $notifications = array();

  // Notify the author of the translation about the deletion.
  $notification = array(
    'type' => 'notify-author-on-translation-deletion',
    'uid' => $author->uid,
    'username' => $author->name,
    'recipient' => $author->name . ' <' . $author->umail . '>',
    'sguid' => $sguid,
    'string' => $string,
    'translation' => $translation,
  );
  $notifications[] = $notification;

  // Notify the voters of the translation as well.
  foreach ($voters as $voter) {
    if ($voter->name == $author->name)  continue;  // don't send a second message to the author
    $notification = array(
      'type' => 'notify-voter-on-translation-deletion',
      'uid' => $voter->uid,
      'username' => $voter->name,
      'recipient' => $voter->name . ' <' . $voter->umail . '>',
      'sguid' => $sguid,
      'string' => $string,
      'translation' => $translation,
    );
    $notifications[] = $notification;
  }

  btr_queue_notifications($notifications);
}

/**
 * Queue notifications for sending by email.
 *
 * @param $notifications
 *   Array of notification items. Each item is an associative array
 *   containing at least 'type' and 'recipient' (email), and optionally
 *   other parameters that can be used on the notification template
 *   (depending on the type of the notification).
 */
function btr_queue_notifications($notifications) {
  $queue = DrupalQueue::get('notifications');
  $queue->createQueue();  // There is no harm in trying to recreate existing.
  foreach ($notifications as $item) {
    $queue->createItem((object)$item);
  }
}