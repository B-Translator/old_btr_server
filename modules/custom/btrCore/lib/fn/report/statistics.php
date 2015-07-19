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
 * @param $origin
 *     (Optional) Origin of the project.
 *
 * @param $project
 *     (Optional) Name of the project.
 *
 * @return
 *   Array of general stats for the last week, month and year.
 */
function report_statistics($lng, $origin = NULL, $project = NULL) {

  // validate parameters
  if (!in_array($lng, btr::languages_get())) {
    $lng = 'fr';
  }

  // Return cache if possible.
  $cid = "report_statistics:$lng";
  if ($origin != NULL)  $cid .= ":$origin";
  if ($project != NULL) $cid .= ":$project";
  $cache = cache_get($cid, 'cache_btrCore');
  if (!empty($cache) && isset($cache->data) && !empty($cache->data)) {
    return $cache->data;
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

  $sql_count_translations =
    "SELECT count(*) as cnt FROM {$btr_translations}
     WHERE ulng = :lng AND time >= :from_date
     AND umail NOT IN ('admin@example.com', 'admin@btranslator.org', '')";

  $sql_count_votes =
    "SELECT count(*) as cnt FROM {$btr_votes}
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
  cache_set($cid, $stats, 'cache_btrCore', time() + 12*60*60);

  return $stats;
}
