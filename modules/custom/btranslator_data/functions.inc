<?php
/**
 * @file
 * Functions called from the user interface.
 */

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
function btr_user_delete($ulng, $uid) {
  $args = array(':ulng' => $ulng, ':uid' => $uid);
  $update_user = "
    UPDATE {btr_users}
    SET status = 0
    WHERE uid = :uid AND :ulng = ulng
  ";
  $GLOBALS['btr_db']->query($update_user, $args);
}


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
