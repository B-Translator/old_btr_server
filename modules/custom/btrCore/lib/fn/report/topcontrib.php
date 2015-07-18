<?php
/**
 * @file
 * Function: report_topcontrib()
 */

namespace BTranslator;
use \btr;

/**
 * Return a list of top contributing users from the last period.
 *
 * @param $period
 *     Period of report: day | week | month | year.
 *
 * @param $size
 *     Number of top users to return.
 *
 * @param $lng
 *     Language of contributions.
 *
 * @param $origin
 *     (Optional) Origin of the project.
 *
 * @param $project
 *     (Optional) Name of the project.
 *
 * @return
 *     Array of users, where each user is an object
 *     with these attributes:
 *         uid, name, umail, score, translations, votes
 */
function report_topcontrib($period = 'week', $size = 5, $lng = 'fr', $origin = NULL, $project = NULL) {

  // validate parameters
  if (!in_array($lng, btr::languages_get())) {
    $lng = 'fr';
  }
  if (!in_array($period, array('day', 'week', 'month', 'year'))) {
    $period = 'week';
  }
  $size = (int) $size;
  if ($size < 5) $size = 5;
  if ($size > 100) $size = 100;

  // Return cache if possible.
  $cid = "report_topcontrib:$lng:$period:$size";
  if ($origin != NULL)  $cid .= ":$origin";
  if ($project != NULL) $cid .= ":$project";
  $cache = cache_get($cid, 'cache_btrCore');
  if (!empty($cache) && isset($cache->data) && !empty($cache->data)) {
    return $cache->data;
  }

  $from_date = date('Y-m-d', strtotime("-1 $period"));

  // Select translations and votes that will be used for the stats.
  if ($origin == NULL) {
    $btr_translations = 'btr_translations';
    $btr_votes = 'btr_votes';
  }
  else {
    _create_tmp_tables($lng, $origin, $project);
    $btr_translations = 'btr_tmp_translations';
    $btr_votes = 'btr_tmp_votes';
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
         FROM {$btr_translations} t
         WHERE ulng = :lng AND time > :from_date
           AND umail!='admin@example.com' AND umail!=''
       )
       UNION ALL
       (
         SELECT v.umail, 1 AS weight,
                0 AS translation, 1 AS vote
         FROM {$btr_votes} v
         WHERE ulng = :lng AND time > :from_date
           AND umail!='admin@example.com' AND umail!=''
       )
    ) AS w
    LEFT JOIN {btr_users} u
           ON (u.ulng = :lng AND u.umail = w.umail)
    GROUP BY w.umail
    ORDER BY score DESC
  ";
  $args = array(':lng' => $lng, ':from_date' => $from_date);
  $topcontrib = btr::db_query_range($sql_get_topcontrib, 0, $size, $args)->fetchAll();

  // Cache for 12 hours.
  cache_set($cid, $topcontrib, 'cache_btrCore', time() + 12*60*60);

  return $topcontrib;
}

/**
 * Create the temporary tables {btr_tpm_translations} and {btr_tmp_votes}
 * with the relevant translations and votes.
 */
function _create_tmp_tables($lng, $origin, $project) {
  // Create a temporary table of the relevant translations.
  $sql_get_translations = "CREATE TEMPORARY TABLE {btr_tmp_translations} AS
        SELECT t.*
        FROM {btr_projects} p
        JOIN {btr_templates} tpl ON (tpl.pguid = p.pguid)
        JOIN {btr_locations} l ON (l.potid = tpl.potid)
        JOIN {btr_strings} s ON (l.sguid = s.sguid)
        JOIN {btr_translations} t ON (t.sguid = s.sguid AND t.lng = :lng)
        WHERE p.origin = :origin";
  $args = [':lng' => $lng, 'origin' => $origin];
  if ($project != NULL) {
    $sql_get_translations .= " AND p.project = :project";
    $args[':project'] = $project;
  }
  btr::db_query($sql_get_translations, $args);

  // Create a temporary table of the relevant votes.
  $sql_get_votes = "CREATE TEMPORARY TABLE {btr_tmp_votes} AS
        SELECT v.*
        FROM {btr_tmp_translations} t
        JOIN {btr_votes} v ON (v.tguid = t.tguid)
    ";
  btr::db_query($sql_get_votes);
}
