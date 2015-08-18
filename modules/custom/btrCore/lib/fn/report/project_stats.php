<?php
/**
 * @file
 * Function: report_project_stats()
 */

namespace BTranslator;
use \btr;

/**
 * Get project details and statistics.
 *
 * @param $origin
 *     Origin of the project.
 *
 * @param $project
 *     Name of the project.
 *
 * @param $lng
 *   Language of translations.
 *
 * @return
 *   Associative array of project details and stats:
 *     - strings : total number of strings
 *     - translated : nr of translated strings
 *     - untranslated : nr of untranslated strings
 *     - translations : total number of translations
 *     - votes : total number of votes
 *     - contributors : total nr of contributors
 *     - subscribers : nr of subscribed users
 */
function report_project_stats($origin, $project, $lng) {
  // Return cache if possible.
  $cid = "report_project_stats:$origin:$project:$lng";
  $cache = cache_get($cid, 'cache_btrCore');
  if (!empty($cache) && isset($cache->data) && !empty($cache->data)) {
    return $cache->data;
  }

  $stats = array();

  // Get the total number of strings.
  $sql = "
    SELECT COUNT(*)
    FROM {btr_projects} p
    INNER JOIN {btr_templates} tpl ON (tpl.pguid = p.pguid)
    INNER JOIN {btr_locations} l ON (l.potid = tpl.potid)
    WHERE p.origin = :origin AND p.project = :project
  ";
  $args = [':origin' => $origin, ':project' => $project];
  $stats['strings'] = btr::db_query($sql, $args)->fetchField();

  // Get the number of translated strings.
  $sql = "
    SELECT COUNT(DISTINCT(s.sguid))
    FROM {btr_projects} p
    INNER JOIN {btr_templates} tpl ON (tpl.pguid = p.pguid)
    INNER JOIN {btr_locations} l ON (l.potid = tpl.potid)
    INNER JOIN {btr_strings} s ON (s.sguid = l.sguid)
    INNER JOIN {btr_translations} t ON (t.sguid = s.sguid AND t.lng = :lng)
    WHERE p.origin = :origin AND p.project = :project
  ";
  $args[':lng'] = $lng;
  $stats['translated'] = btr::db_query($sql, $args)->fetchField();

  // Get the number of untranslated strings.
  $sql = "
    SELECT COUNT(*)
    FROM {btr_projects} p
    INNER JOIN {btr_templates} tpl ON (tpl.pguid = p.pguid)
    INNER JOIN {btr_locations} l ON (l.potid = tpl.potid)
    INNER JOIN {btr_strings} s ON (s.sguid = l.sguid)
    LEFT  JOIN {btr_translations} t ON (t.sguid = s.sguid AND t.lng = :lng)
    WHERE p.origin = :origin AND p.project = :project
      AND t.tguid is NULL
  ";
  $stats['untranslated'] = btr::db_query($sql, $args)->fetchField();

  // Get the total number of translations.
  $sql = "
    SELECT COUNT(t.tguid)
    FROM {btr_projects} p
    INNER JOIN {btr_templates} tpl ON (tpl.pguid = p.pguid)
    INNER JOIN {btr_locations} l ON (l.potid = tpl.potid)
    INNER JOIN {btr_strings} s ON (s.sguid = l.sguid)
    INNER JOIN {btr_translations} t ON (t.sguid = s.sguid AND t.lng = :lng)
    WHERE p.origin = :origin AND p.project = :project
  ";
  $stats['translations'] = btr::db_query($sql, $args)->fetchField();

  // Get the total number of votes.
  $sql = "
    SELECT COUNT(t.tguid)
    FROM {btr_projects} p
    INNER JOIN {btr_templates} tpl ON (tpl.pguid = p.pguid)
    INNER JOIN {btr_locations} l ON (l.potid = tpl.potid)
    INNER JOIN {btr_strings} s ON (s.sguid = l.sguid)
    INNER JOIN {btr_translations} t ON (t.sguid = s.sguid AND t.lng = :lng)
    INNER JOIN {btr_votes} v ON (v.tguid = t.tguid)
    WHERE p.origin = :origin AND p.project = :project
  ";
  $stats['votes'] = btr::db_query($sql, $args)->fetchField();

  // Get the total number of contributors.
  $sql = "
    SELECT COUNT(DISTINCT(v.umail))
    FROM {btr_projects} p
    INNER JOIN {btr_templates} tpl ON (tpl.pguid = p.pguid)
    INNER JOIN {btr_locations} l ON (l.potid = tpl.potid)
    INNER JOIN {btr_strings} s ON (s.sguid = l.sguid)
    INNER JOIN {btr_translations} t ON (t.sguid = s.sguid AND t.lng = :lng)
    INNER JOIN {btr_votes} v ON (v.tguid = t.tguid)
    WHERE p.origin = :origin AND p.project = :project
  ";
  $stats['contributors'] = btr::db_query($sql, $args)->fetchField();

  // Get the number of subscribed users.
  $sql = "
    SELECT COUNT(*)
    FROM {field_data_field_projects}
    WHERE field_projects_value = :project
      AND deleted = 0
  ";
  $args = [ ':project' => "$origin/$project" ];
  $stats['subscribers'] = \db_query($sql, $args)->fetchField();

  // Cache for 12 hours.
  cache_set($cid, $stats, 'cache_btrCore', time() + 12*60*60);

  return $stats;
}
