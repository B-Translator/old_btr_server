<?php

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

