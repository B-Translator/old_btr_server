<?php
/**
 * @file
 * Functions for project snapshots.
 */

namespace BTranslator;
use \btr;

/**
 * Make a snapshot of the given origin/project/lng.
 *
 * Exports the latest most_voted translations of the project, makes diffs with
 * the last snapshot, then saves the diffs and the new snapshot.
 *
 * @param $origin
 *   The origin of the project.
 *
 * @param $project
 *   The name of the project.
 *
 * @param $lng
 *   The language of translation files.
 *
 * @param $comment
 *   A comment for the new snapshot.
 *
 * @param $export_mode
 *   Can be 'most_voted' (default), or 'preferred', or 'original'.
 *
 * @param $preferred_voters
 *   Array of email addresses of users whose translations are preferred.
 */
function project_snapshot($origin, $project, $lng, $comment = NULL,
  $export_mode = 'most_voted', $preferred_voters = NULL)
{
  // Export the latest most voted translations
  // and make the diffs with the last snapshot.
  $export_file = tempnam('/tmp', 'export_file_') . '.tgz';
  $file_diff = tempnam('/tmp', 'file_diff_') . '.diff';
  $file_ediff = tempnam('/tmp', 'file_ediff_') . '.ediff';
  btr::project_diff($origin, $project, $lng,
    $file_diff, $file_ediff, $export_file,
    $export_mode, $preferred_voters);

  // If not empty, save the diffs and the new snapshot.
  if (filesize($file_diff) != 0 or filesize($file_ediff) != 0) {
    btr::project_diff_add($origin, $project, $lng, $file_diff, $file_ediff, $comment);
    btr::project_snapshot_save($origin, $project, $lng, $export_file);
  }

  // Cleanup.
  exec("rm $export_file $file_diff $file_ediff");
}

/**
 * Get the snapshot and save it on the given file.  If there is no
 * snapshot, get the original version of the imported files instead.
 *
 * @param $origin
 *   The origin of the project.
 *
 * @param $project
 *   The name of the project.
 *
 * @param $lng
 *   The language of the translation files.
 *
 * @param $file
 *   The file where to output the snapshot (format tgz).
 */
function project_snapshot_get($origin, $project, $lng, $file) {
  // Get the content of the snapshot (which is a tgz file).
  $snapshot = btr_query(
    'SELECT snapshot FROM {btr_snapshots}
     WHERE pguid = :pguid AND lng = :lng',
    array(
      ':pguid' => sha1($origin . $project),
      ':lng' => $lng,
    ))
    ->fetchField();

  if ($snapshot) {
    // Save it to the given file.
    file_put_contents($file, $snapshot);
  }
  else {
    // Export the original version of the imported files.
    $tmpdir = exec('mktemp -d');
    btr::project_export($origin, $project, $lng, $tmpdir,
      $GLOBALS['user']->uid, $quiet = TRUE, $export_mode = 'original');
    exec("tar -cz -f $file -C $tmpdir .");
    exec("rm -rf $tmpdir");
  }
}

/**
 * Update the snapshot of the given project/lng with the content of the file.
 *
 * @param $origin
 *   The origin of the project.
 *
 * @param $project
 *   The name of the project.
 *
 * @param $lng
 *   The language of the translation files.
 *
 * @param $file
 *   The file that has the snapshot (format tgz).
 */
function project_snapshot_save($origin, $project, $lng, $file) {
  // Remove the old one first, if it exists.
  btr_delete('btr_snapshots')
    ->condition('pguid', sha1($origin . $project))
    ->condition('lng', $lng)
    ->execute();

  // Save the new snapshot.
  btr_insert('btr_snapshots')
    ->fields(array(
        'pguid' => sha1($origin . $project),
        'lng' => $lng,
        'snapshot' => file_get_contents($file),
        'uid' => $GLOBALS['user']->uid,
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();
}

