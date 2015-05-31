<?php
/**
 * @file
 * Function: cron_import_project()
 */

namespace BTranslator;
use \btr;

/**
 * The callback function called from cron_queue 'import_project'.
 */
function cron_import_project($params) {

  // Make sure that imports do not run in parallel,
  // so that the server is not overloaded.
  if (!lock_acquire('import_project', 3000)) {
    // If we cannot get the lock, just stop the execution, do not return,
    // because after the callback function returns, the cron_queue will
    // remove the item from the queue, no matter whether it is processed or not.
    exit();
  }

  // Allow the import script to run until completion.
  set_time_limit(0);

  // Get the parameters.
  $account = user_load($params->uid);
  $file = file_load($params->fid);
  $origin = $params->origin;
  $project = $params->project;
  $lng = $account->translation_lng;

  // Create a temporary directory.
  $tmpdir = '/tmp/' . sha1_file($file->uri);
  mkdir($tmpdir, 0700);

  // Copy the file there and extract it (if it is an archive).
  file_unmanaged_copy($file->uri, $tmpdir);
  exec("cd $tmpdir ; dtrx -q -n $file->filename 2>/dev/null");

  // Create the project.
  btr::project_add($origin, $project, $tmpdir, $account->uid);

  // If there are any PO files, import translations from them.
  btr::project_import($origin, $project, $lng, $tmpdir, $account->uid);

  // Get the base_url of the site.
  module_load_include('inc', 'btrCore', 'includes/sites');
  $base_url = btr::utils_get_base_url($lng);

  // Notify the user that the project import is done.
  $params = array(
    'type' => 'notify-that-project-import-is-done',
    'uid' => $account->uid,
    'username' => $account->name,
    'recipient' => $account->name .' <' . $account->mail . '>',
    'project' => $origin . '/' . $project,
    'search_url' => $base_url . url('translations/search', array(
                    'query' => array(
                      'lng' => $lng,
                      'origin' => $origin,
                      'project' => $project,
                      'limit' => 50,
                    )
                  )),
  );
  btr::queue('notifications', array($params));

  // Cleanup, remove the temp dir and delete the file.
  exec("rm -rf $tmpdir/");
  file_delete($file, TRUE);

  // This import is done, allow any other imports to run.
  lock_release('import_project');
}
