<?php

/**
 * Return the url of the mobile application for the given project.
 */
function btr_get_app_url($lng, $origin, $project) {
  list($_, $lng) = explode('_', $project);
  $query = 'SELECT app_url FROM {btr_translation_projects}
            WHERE lng = :lng AND origin = :origin AND project = :project';
  $params = array(':lng' => $lng, ':origin' => $origin, ':project' => $project);
  $app_url = db_query($query, $params)->fetchField();
  return $app_url;
}

/**
 * Return the base_url of a client site,
 * or the base_url of the server
 * if the url of that site is not defined.
 */
function btr_get_base_url($lng) {
  $sites = btr_get_sites();
  if ( isset($sites[$lng]['base_url']) ) {
    $base_url = $sites[$lng]['base_url'];
  }
  else {
    $base_url = $GLOBALS['base_url'];
  }

  return $base_url;
}

/**
 * Return an array of sites for each language
 * and their metadata (like base_url etc.)
 */
function btr_get_sites() {
  return array(
    'fr' => array(
      //'base_url' => 'https://example.org',
    ),
    'sq' => array(
      'base_url' => 'https://example.org',
    ),
  );
}
