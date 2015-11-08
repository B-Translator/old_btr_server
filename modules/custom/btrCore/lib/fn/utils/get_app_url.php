<?php
/**
 * @file
 * Function: utils_get_app_url()
 */

namespace BTranslator;

/**
 * Return the url of the mobile application for the given project.
 */
function utils_get_app_url($lng, $origin, $project) {
  list($_, $lng) = explode('_', $project);
  $query = 'SELECT app_url FROM {translation_projects}
            WHERE lng = :lng AND origin = :origin AND project = :project';
  $params = array(':lng' => $lng, ':origin' => $origin, ':project' => $project);
  $app_url = \db_query($query, $params)->fetchField();
  return $app_url;
}
