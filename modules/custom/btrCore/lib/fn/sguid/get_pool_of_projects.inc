<?php

/**
 * Get projects from which the next string for review will be selected.
 *
 * This is normally the preferred projects of the user, but if user
 * has not defined any preferred projects, then the preferred projects
 * of the site (defined by site admin) will be used. However, if the
 * $scope_projects has been provided, it will be used to restrict (limit)
 * this list of projects.
 *
 * @param $uid
 *   The user whose preferencies will be used.
 *   If no $uid is given, then the current user is assumed.
 *
 * @param $target_projects
 *   Array of projects to restrict the selection.
 *
 * @return
 *   Array of projects that will be used for selecting a string.
 */
function get_pool_of_projects($uid =NULL, $target_projects =NULL) {
  if ($uid == NULL)  { $uid = $GLOBALS['user']->uid; }
  $user = user_load($uid);

  // get the preferred projects from the site config
  $site_preferred_projects = array();
  $preferred_projects_txt = variable_get('btr_preferred_projects', '');
  $lines = preg_split('#\r\n|\r|\n#', $preferred_projects_txt);
  foreach ($lines as $line) {
    $line = trim($line);
    if ($line != '') {
      $site_preferred_projects[] = $line;
    }
  }

  $arr_projects = array();
  if (isset($user->preferred_projects)) {
    // get the preferred projects of the user
    $arr_projects = $user->preferred_projects;
  }
  else {
    // get the site preferred projects
    $arr_projects = $site_preferred_projects;
  }

  // Use $target_projects to restrict the list of projects.
  if ( ! empty($target_projects)) {
    $arr_projects = array_intersect($arr_projects, $target_projects);
    if (empty($arr_projects)) {
      $arr_projects = $target_projects;
    }
  }

  if (empty($arr_projects)) {
    $arr_projects = $site_preferred_projects;
  }

  return $arr_projects;
}
