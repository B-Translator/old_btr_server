<?php
/**
 * @file
 * Function: report_statistics()
 */

namespace BTranslator;
use \btr;

/**
 * Return an array of the statistics (number of votes
 * and translations) for the last week, month and year.
 *
 * @param $lng
 *   Language of translations.
 *
 * @return
 *   Array of general stats for the last week, month and year.
 */
function report_statistics($lng) {

  $cache = cache_get("report_statistics:$lng", 'cache_btr');
  // Return cache if possible.
  if (!empty($cache) && isset($cache->data) && !empty($cache->data)) {
    return $cache->data;
  }

  $sql_count_translations =
    "SELECT count(*) as cnt FROM {btr_translations}
     WHERE ulng = :lng AND time >= :from_date
     AND umail NOT IN ('admin@example.com', 'admin@btranslator.org', '')";

  $sql_count_votes =
    "SELECT count(*) as cnt FROM {btr_votes}
     WHERE ulng = :lng AND time >= :from_date";

  $stats = array();

  foreach (array('week', 'month', 'year') as $period) {
    $from_date = date('Y-m-d', strtotime("-1 $period"));
    $args = array(':lng' => $lng, ':from_date' => $from_date);
    $nr_votes = btr::db_query($sql_count_votes, $args)->fetchField();
    $nr_translations = btr::db_query($sql_count_translations, $args)->fetchField();

    $stats[$period] = array(
      'period' => $period,
      'from_date' => $from_date,
      'nr_votes' => $nr_votes,
      'nr_translations' => $nr_translations,
    );
  }

  // Cache for 12 hours.
  cache_set("report_statistics:$lng", $stats, 'cache_btr', time() + 12*60*60);

  return $stats;
}
