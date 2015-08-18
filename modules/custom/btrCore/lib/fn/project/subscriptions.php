<?php
/**
 * @file
 * Definition of function project_subscriptions()
 */

namespace BTranslator;

/**
 * Return the list of projects to which the user is subscribed.
 *
 * @param $uid
 *   (Optional) ID of the user.
 */
function project_subscriptions($uid = NULL) {
  if ($uid===NULL)  $uid = $GLOBALS['user']->uid;
  $account = user_load($uid);

  $subscribed_projects = array();
  $projects = $account->field_projects[LANGUAGE_NONE];
  foreach($projects as $p) {
    $subscribed_projects[] = $p['value'];
  }

  return $subscribed_projects;
}
