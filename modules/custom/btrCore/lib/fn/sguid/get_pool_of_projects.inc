<?php

/**
 * Get projects from which the next string for review will be selected.
 *
 * This is normally the projects of the user, but if user has not any projects,
 * then the projects of the site (defined by site admin) will be used. However,
 * if the $scope_projects has been provided, it will be used to restrict (limit)
 * this list of projects.
 *
 * @param $uid
 *   The user whose preferencies will be used.
 *   If no $uid is given, then the current user is assumed.
 *
 * @param $scope
 *   Array of projects to restrict the selection.
 *
 * @return
 *   Array of projects that will be used for selecting a string.
 */
function get_pool_of_projects($uid =NULL, $scope =NULL) {
  if ($uid == NULL)  { $uid = $GLOBALS['user']->uid; }
  $user = user_load($uid);

  // get the projects from the site config
  $site_projects = array();
  $projects_txt = variable_get('btr_preferred_projects', '');
  $lines = preg_split('#\r\n|\r|\n#', $projects_txt);
  foreach ($lines as $line) {
    $line = trim($line);
    if ($line != '') {
      $site_projects[] = $line;
    }
  }

  $arr_projects = array();
  if (isset($user->subscribed_projects)) {
    // get the projects of the user
    $arr_projects = $user->subscribed_projects;
  }
  else {
    // get the site projects
    $arr_projects = $site_projects;
  }

  // Use $scope to restrict the list of projects.
  if ( ! empty($scope)) {
    $arr_projects = array_intersect($arr_projects, $scope);
    if (empty($arr_projects)) {
      $arr_projects = $scope;
    }
  }

  if (empty($arr_projects)) {
    $arr_projects = $site_projects;
  }

  return $arr_projects;
}
