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
function report_topcontrib($period = 'week', $size = 5, $lng = NULL, $origin = NULL, $project = NULL) {

  // validate parameters
  if (!in_array($lng, btr::languages_get())) {
    $lng = 'all';
  }
  if (!in_array($period, array('day', 'week', 'month', 'year'))) {
    $period = 'week';
  }
  $size = (int) $size;
  if ($size < 5) $size = 5;
  if ($size > 100) $size = 100;

  // Return cache if possible.
  $cid = "report_topcontrib:$period:$size:$lng";
  if ($origin != NULL)  $cid .= ":$origin";
  if ($project != NULL) $cid .= ":$project";
  $cache = cache_get($cid, 'cache_btrCore');
  if (!empty($cache) && isset($cache->data) && !empty($cache->data)) {
    return $cache->data;
  }

  // Get the query condition and the arguments.
  $condition = 'time >= :from_date';
  $args[':from_date'] = date('Y-m-d', strtotime("-1 $period"));
  if ($lng != 'all') {
    $condition .= ' AND ulng = :lng';
    $args[':lng'] = $lng;
  }

  // Select translations and votes that will be used for the stats.
  if ($origin == NULL) {
    $btr_translations = 'btr_translations';
    $btr_votes = 'btr_votes';
  }
  else {
    include_once __DIR__ . '/_create_tmp_tables.inc';
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
         SELECT t.umail, t.lng as ulng,
                5 AS weight, 1 AS translation, 0 AS vote
         FROM {$btr_translations} t
         WHERE $condition
       )
       UNION ALL
       (
         SELECT v.umail, v.ulng,
                1 AS weight, 0 AS translation, 1 AS vote
         FROM {$btr_votes} v
         WHERE $condition
       )
    ) AS w
    LEFT JOIN {btr_users} u
           ON (u.ulng = w.ulng AND u.umail = w.umail)
    WHERE u.name != 'admin'
    GROUP BY w.umail
    ORDER BY score DESC
  ";
  $topcontrib = btr::db_query_range($sql_get_topcontrib, 0, $size, $args)->fetchAll();

  // Cache for 12 hours.
  cache_set($cid, $topcontrib, 'cache_btrCore', time() + 12*60*60);

  return $topcontrib;
}
