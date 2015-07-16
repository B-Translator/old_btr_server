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
 * @param $lng
 *     Language of contributions.
 *
 * @param $period
 *     Period of report: day | week | month | year.
 *
 * @param $size
 *     Number of top users to return.
 *
 * @return
 *     Array of users, where each user is an object
 *     with these attributes:
 *         uid, name, umail, score, translations, votes
 */
function report_topcontrib($period = 'week', $size = 5, $lng = 'fr') {

  // validate parameters
  if (!in_array($lng, btr::languages_get())) {
    $lng = 'fr';
  }
  if (!in_array($period, array('day', 'week', 'month', 'year'))) {
    $period = 'week';
  }
  $size = (int) $size;
  if ($size < 5) $size = 5;
  if ($size > 20) $size = 20;

  // Return cache if possible.
  $cache = cache_get("report_topcontrib:$lng:$period:$size", 'cache_btrCore');
  if (!empty($cache) && isset($cache->data) && !empty($cache->data)) {
    return $cache->data;
  }

  $from_date = date('Y-m-d', strtotime("-1 $period"));

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
  $topcontrib = btr::db_query_range($sql_get_topcontrib, 0, $size, $args)->fetchAll();

  // Cache for 12 hours.
  cache_set("report_topcontrib:$lng:$period:$size", $topcontrib, 'cache_btrCore', time() + 12*60*60);

  return $topcontrib;
}
