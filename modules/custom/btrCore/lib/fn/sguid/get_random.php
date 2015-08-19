<?php
/**
 * @file
 * Get a random sguid.
 */

namespace BTranslator;
use \btr;

include_once(dirname(__FILE__). '/get_pool_of_projects.inc');

/**
 * Return a random sguid for the given user.
 *
 * @param $uid
 *   Select according to the preferencies of this user.
 *   If no $uid is given, then the current user is assumed.
 *
 * @param $scope
 *   Array of projects to restrict selection.
 *
 * @return
 *   Randomly selected sguid.
 */
function sguid_get_random($uid =NULL, $scope =NULL) {
  // Get the list of projects that will be searched.
  $projects = get_pool_of_projects($uid, $scope);

  // Build the WHERE condition for selecting projects.
  list($where, $args) = btr::utils_projects_to_where_condition($projects);
  if ($where == '')  $where = '(1=1)';

  // Get the total number of strings from which we can choose.
  $sql_count = "
    SELECT COUNT(*) AS number_of_strings
    FROM (SELECT pguid FROM {btr_projects} WHERE $where) p
    LEFT JOIN {btr_templates} tpl ON (tpl.pguid = p.pguid)
    LEFT JOIN {btr_locations} l ON (l.potid = tpl.potid)
    LEFT JOIN {btr_strings} s ON (s.sguid = l.sguid)
  ";
  $nr_strings = btr::db_query($sql_count, $args)->fetchField();

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
  $sguid = btr::db_query($sql_get_sguid, $args)->fetchField();

  return $sguid;
}
