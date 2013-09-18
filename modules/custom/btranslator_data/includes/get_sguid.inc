<?php

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

