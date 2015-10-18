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
function report_statistics($lng = NULL, $origin = NULL, $project = NULL) {

  // validate parameters
  if (!in_array($lng, btr::languages_get())) {
    $lng = 'all';
  }

  // Return cache if possible.
  $cid = "report_statistics:$lng";
  if ($origin != NULL)  $cid .= ":$origin";
  if ($project != NULL) $cid .= ":$project";
  $cache = cache_get($cid, 'cache_btrCore');
  if (!empty($cache) && isset($cache->data) && !empty($cache->data)) {
    return $cache->data;
  }

  // Get the query condition and the arguments.
  $condition = 'time >= :from_date';
  $args = array();
  if ($lng != 'all') {
    $condition .= ' AND ulng = :ulng';
    $args[':ulng'] = $lng;
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

  // Get the count queries.
  $sql_count_translations =
     "SELECT count(*) as cnt FROM {$btr_translations}
      WHERE $condition
      AND umail != ''";
  $sql_count_votes =
     "SELECT count(*) as cnt FROM {$btr_votes}
      WHERE $condition";

  // Get the stats.
  $stats = array();
  foreach (array('week', 'month', 'year') as $period) {
    $from_date = date('Y-m-d', strtotime("-1 $period"));
    $args[':from_date'] = $from_date;
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
