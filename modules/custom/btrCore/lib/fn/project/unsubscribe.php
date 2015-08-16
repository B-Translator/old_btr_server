<?php
/**
 * @file
 * Definition of function project_unsubscribe()
 */

namespace BTranslator;

/**
 * Unsubscribe a user from the given project.
 *
 * @param $origin
 *   The origin of the project.
 *
 * @param $project
 *   The name of the project.
 *
 * @param $uid
 *   (Optional) ID of the user.
 */
function project_unsubscribe($origin, $project, $uid = NULL) {
  if ($uid===NULL)  $uid = $GLOBALS['user']->uid;
  $account = user_load($uid);

  $new_projects = array();
  $projects = $account->field_preferred_projects[LANGUAGE_NONE];
  foreach($projects as $p) {
    if ($p['value'] == "$origin/$project") continue;
    $new_projects[]['value'] = $p['value'];
  }

  user_save($account, ['field_preferred_projects' => [LANGUAGE_NONE => $new_projects]]);
}
