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
    $latest = btr::translation_latest($lng, $origin, $project);
    // Cache them for 2 hours.
    cache_set($cid, $latest, 'cache_btrCore', strtotime('+2 hours'));
  }

  // Output latest translations in JSON format and exit.
  print drupal_json_encode($latest);
  exit();
}
