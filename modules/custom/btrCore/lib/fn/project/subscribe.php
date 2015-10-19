<?php
/**
 * @file
 * Definition of function project_subscribe()
 */

namespace BTranslator;

/**
 * Subscribe a user to the given project.
 *
 * @param $origin
 *   The origin of the project.
 *
 * @param $project
 *   The name of the project.
 *
 * @param $uid
 *   ID of the user.
 */
function project_subscribe($origin, $project, $uid = NULL) {
  if ($uid===NULL)  $uid = $GLOBALS['user']->uid;

  // Don't subscribe anonymous and admin users.
  if ($uid == 0 or $uid == 1)  return;

  $account = user_load($uid);
  $projects = $account->field_projects[LANGUAGE_NONE];
  $new_projects = array();
  foreach($projects as $p) {
    if ($p['value'] == "$origin/$project") continue;
    $new_projects[]['value'] = $p['value'];
  }
  $new_projects[]['value'] = "$origin/$project";

  user_save($account, ['field_projects' => [LANGUAGE_NONE => $new_projects]]);
}
