<?php
/**
 * @file
 * Function: schedule_project_export()
 */

namespace BTranslator;
use \btr;

/**
 * Schedule a project for export. When the request
 * is completed, the user will be notified by email.
 *
 * @param $origin
 *   The origin of the project.
 *
 * @param $project
 *   The name of the project.
 *
 * @param $lng
 *   Translation to be exported.
 *
 * @param $export_mode
 *   The export mode that should be used. It can be one of:
 *   (original | most_voted | preferred).
 *     - The mode 'original' exports the translations of the
 *       original files that were imported.
 *     - The mode 'most_voted' exports the translations with the
 *       highest number of votes.
 *     - The mode 'preferred' gives precedence to the translations
 *       voted by a user or a list of users, despite the number of
 *       votes.
 *
 * @param preferred_voters
 *   Comma separated list of usernames. Used only when export_mode
 *   is 'preferred'.
 */
function schedule_project_export($origin, $project, $lng,
  $export_mode = NULL, $preferred_voters = NULL)
{
  // Make sure that the given origin and project do exist.
  if (!btr::project_exists($origin, $project)) {
    $msg = t("The project '!project' does not exist.",
           ['!project' => "$origin/$project"]);
    btr::messages($msg, 'error');
    return;
  }

  // Check the export_mode.
  if (empty($params['export_mode'])) {
    $params['export_mode'] = 'most_voted';
  }
  if (!in_array($export_mode, array('most_voted', 'preferred', 'original'))) {
    $msg = t("Unknown export mode '!export_mode'.",
             ['!export_mode' => $export_mode]);
    btr::messages($msg, 'error');
    return;
  }

  // Get and check the list of preferred voters.
  if ($export_mode == 'preferred') {
    list($arr_emails, $error_messages) = btr::utils_get_emails($preferred_voters);
    if (!empty($error_messages)) {
      btr::mesages($error_messages);
      return;
    }
    if (empty($arr_emails)) {
      $account = user_load($GLOBALS['user']->uid);
      $arr_emails = [$account->init];
    }
  }

  // Schedule the project export.
  $queue_params = [
    'origin' => $origin,
    'project' => $project,
    'lng' => $lng,
    'uid' => $GLOBALS['user']->uid,
    'export_mode' => $export_mode,
    'preferred_voters' => $arr_emails,
  ];
  btr::queue('export_project', [$queue_params]);

  // Schedule a notification to each admin of the project.
  $notify_admin = variable_get('btr_export_notify_admin', TRUE);
  if ($notify_admin) {
    $queue_params['type'] = 'notify-admin-on-export-request';
    $admins = btr::project_users('admin', $origin, $project, $lng);
    foreach ($admins as $uid => $user) {
      $queue_params['recipient'] = $user->email;
      $queue_params['username'] = $user->name;
      btr::queue('notifications', [$queue_params]);
    }
  }

  // Return a notification message.
  $msg = t("Export of '!project' is scheduled. You will be notified by email when it is done.",
         ['!project' => "$origin/$project"]);
  btr::messages($msg);
}
