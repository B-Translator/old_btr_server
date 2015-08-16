<?php
/**
 * @file
 * Definition of the function project_sync().
 */

namespace BTranslator;
use \btr;

/**
 * Synchronize the translations of a given origin/project/lng with the upstream
 * project.
 *
 * Does not allow concurrent synchronizations because they may affect the
 * performance of the server.
 *
 * @param origin
 *   Origin of the project.
 *
 * @param project
 *   The name of the project.
 *
 * @param lng
 *   Translation to be exported.
 */
function project_sync($origin, $project, $lng) {
  // The output is plain text.
  header('Content-Type: text/plain');

  // Make sure that the given origin and project do exist.
  if (!btr::project_exists($origin, $project)) {
    print t("The project '!project' does not exist.",
      ['!project' => "$origin/$project"]);
    drupal_exit();
  }

  // Make sure that the current user is project administrator.
  if (!btr::user_is_project_admin($origin, $project, $lng)) {
    print t("Only a project admin can synchronize a project.");
    drupal_exit();
  }

  // Get the sync command.
  if ($lng=='sq' and $origin=='LibreOffice' and in_array($project, ['sw', 'cui']))
    {
      $sync_cmd ="/var/www/data/sync/sq-libo_ui.sh $project 2>&1";
    }
  else {
    print t("There is no script for synchronizing '!project'.",
      ['!project' => "$origin/$project/$lng"]);
    drupal_exit();
  }

  // Try to avoid concurrent synchronizations because they
  // may affect the performance of the server.
  if (!lock_acquire('sync_project')) {
    print t("Error: Server is currently busy. Please try to synchronize again later.");
    drupal_exit();
  }

  // Synchronize the project.
  print "command: $sync_cmd \n";
  print "Synchronizing '$origin/$project/$lng', please wait... \n\n";
  flush();
  set_time_limit(0);
  //passthru($sync_cmd);
  $handle = popen($sync_cmd, 'r');
  while (!feof($handle)) {
    print fgets($handle);
    flush();
    ob_flush();
  }
  pclose($handle);
  print "\nDONE\n\n";

  // Release lock and stop Drupal execution.
  lock_release('sync_project');
  drupal_exit();
}
