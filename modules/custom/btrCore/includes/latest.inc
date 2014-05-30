<?php
/**
 * @file
 * RSS feed from B-Translator.
 */

function btrCore_latest($lng =NULL, $origin =NULL, $project =NULL) {

  if (empty($lng))  $lng = 'fr';

  // Get the domain of the feed in the form of 'origin/project'
  // (or just 'origin').
  $domain = '';
  if ( ! empty($origin) ) {
    $domain = $origin;
    if ( ! empty($project) ) {
      $domain .= '/' . $project;
    }
  }

  // Get the data from cache, if possible.
  $cid = "btrCore_latest:$lng:$domain";
  $cache = cache_get($cid, 'cache_btrCore');
  if (!empty($cache) && isset($cache->data) && !empty($cache->data)) {
    $latest = $cache->data;
  }
  else {
    // Get the latest translation from the database.
    $latest = _btrCore_get_latest_translations($lng, $origin, $project);
    // Cache them for 2 hours.
    cache_set($cid, $latest, 'cache_btrCore', strtotime('+2 hours'));
  }

  // Output latest translations in JSON format and exit.
  print drupal_json_encode($latest);
  exit();
}


/**
 * Get and return an array of the latest translation suggestions,
 * submitted between the last midnight and the midnight before.
 * If $origin and $project are given, then they will be used
 * to filter only the translations that belong to them.
 * The fields that are returned are:
 *   origin, project, sguid, string, lng, translation, tguid, time, name, umail
 */
function _btrCore_get_latest_translations($lng, $origin =NULL, $project =NULL) {

  $get_latest_translations = "
    SELECT p.origin, p.project,
           s.sguid, s.string,
           t.lng, t.translation, t.tguid, t.time,
           u.name, u.umail
    FROM {btr_translations} t
    LEFT JOIN {btr_strings} s ON (s.sguid = t.sguid)
    LEFT JOIN {btr_users} u ON (u.umail = t.umail AND u.ulng = t.ulng)
    LEFT JOIN {btr_locations} l ON (l.sguid = s.sguid)
    LEFT JOIN {btr_templates} tpl ON (tpl.potid = l.potid)
    LEFT JOIN {btr_projects} p ON (p.pguid = tpl.pguid)
    WHERE t.umail != 'admin@example.com' AND t.lng = :lng AND t.time > :from_date
    ";

  $args = array(
    ':lng' => $lng,
    ':from_date' => date('Y-m-d', strtotime("-1 day")),
  );

  if ( ! empty($origin) ) {
    // filter by origin
    $get_latest_translations .= " AND p.origin = :origin";
    $args[':origin'] = $origin;

    if ( ! empty($project) ) {
      // filter also by project
      $get_latest_translations .= " AND p.project = :project";
      $args[':project'] = $project;
    }
  }

  // display the latest first
  $get_latest_translations .= "\n    ORDER BY t.time DESC";

  // run the query and get the translations
  $translations = btr_query($get_latest_translations, $args)->fetchAll();

  return $translations;
}
