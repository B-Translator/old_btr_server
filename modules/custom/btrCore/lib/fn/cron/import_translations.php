<?php
/**
 * @file
 * Function: cron_import_translations()
 */

namespace BTranslator;
use \btr;

/**
 * The callback function called from cron_queue 'import_translations'.
 */
function cron_import_translations($params) {

  // Make sure that imports do not run in parallel,
  // so that the server is not overloaded.
  if (!lock_acquire('import_translations', 3000)) {
    // If we cannot get the lock, just stop the execution, do not return,
    // because after the callback function returns, the cron_queue will
    // remove the item from the queue, no matter whether it is processed or not.
    exit();
  }

  // Allow the import script to run until completion.
  set_time_limit(0);

  // Get the parameters.
  $lng = $params->lng;
  $account = user_load($params->uid);
  $file = file_load($params->fid);

  // Create a temporary directory.
  $tmpdir = '/tmp/' . sha1_file($file->uri);
  mkdir($tmpdir, 0700);

  // Copy the file there and extract it (if it is an archive).
  file_unmanaged_copy($file->uri, $tmpdir);
  exec("cd $tmpdir ; dtrx -q -n $file->filename 2>/dev/null");

  // Import the PO files.
  btr::vote_import($account->uid, $lng, $tmpdir);
  $txt_messages = btr::messages_cat(btr::messages());

  // Get the url of the client site.
  module_load_include('inc', 'btrCore', 'includes/sites');
  $client_url = btr::utils_get_client_url($lng);

  // Notify the user that the export is done.
  $params = array(
    'type' => 'notify-that-import-is-done',
    'uid' => $account->uid,
    'username' => $account->name,
    'recipient' => $account->name .' <' . $account->mail . '>',
    'filename' => $file->filename,
    'search_url' => $client_url . url('translations/search', array(
                    'query' => array(
                      'lng' => $lng,
                      'translated_by' => $account->name,
                      'voted_by' => $account->name,
                      'date_filter' => 'votes',
                      'from_date' => date('Y-m-d H:i:s', REQUEST_TIME - 1),
                      'to_date' => date('Y-m-d H:i:s', REQUEST_TIME + 1),
                      'limit' => 50,
                    )
                  )),
    'messages' => $txt_messages,
  );
  btr::queue('notifications', array($params));

  // Cleanup, remove the temp dir and delete the file.
  exec("rm -rf $tmpdir/");
  file_delete($file, TRUE);

  // This import is done, allow any other imports to run.
  lock_release('import_translations');
}
