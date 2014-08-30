<?php
/**
 * @file
 * Functions for project diffs.
 */

namespace BTranslator;
use \btr;

/**
 * Export the latest most_voted translations of the project and make diffs
 * with the last snapshot.
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
 * @param $file_diff
 *   The file where to output the diff (made with diff).
 *
 * @param $file_ediff
 *   The file where to output the ediff (made with pology/poediff).
 *
 * @param $export_file
 *   The file where to output the latest export (in format tgz).
 */
function project_diff($origin, $project, $lng,
  $file_diff, $file_ediff, $export_file = NULL)
{
  // Export the latest most_voted translations of the project.
  $export_dir = exec('mktemp -d');
  btr::project_export($origin, $project, $lng, $export_dir, $GLOBALS['user']->uid, TRUE);

  // Archive exported files in format tgz.
  if ($export_file !== NULL) {
    exec("tar -cz -f $export_file -C $export_dir .");
  }

  // Get the last snapshot.
  $snapshot_file = tempnam('/tmp', 'snapshot_file_') . '.tgz';
  btr::project_snapshot_get($origin, $project, $lng, $snapshot_file);
  $snapshot_dir = exec('mktemp -d');
  exec("tar -xz -f $snapshot_file -C $snapshot_dir");

  // Make the diffs between the last snapshot and the latest export.
  exec("diff -rubB $snapshot_dir $export_dir > $file_diff");
  $pology = '/usr/local/lib/pology/bin/poediff';
  exec("$pology -n -o $file_ediff $snapshot_dir $export_dir");

  // Cleanup the export and snapshot dirs.
  exec("rm -rf $export_dir");
  exec("rm -rf $snapshot_dir");
  exec("rm $snapshot_file");
}

/**
 * Save in DB the diffs of a project.
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
 * @param $file_diff
 *   The diff file to be saved.
 *
 * @param $file_ediff
 *   The ediff file to be saved (made with pology/poediff).
 *
 * @param $comment
 *   User defined comment that labels the snapshot/diffs.
 */
function project_diff_add($origin, $project, $lng, $file_diff, $file_ediff, $comment = NULL)
{
  // Get the max number of diffs for this project/lng.
  $max_nr = btr_query(
    'SELECT MAX(nr) AS max_nr FROM {btr_diffs}
      WHERE pguid = :pguid AND lng = :lng',
    array(
      ':pguid' => sha1($origin . $project),
      ':lng' => $lng,
    ))
    ->fetchField();

  // Insert a new record of diffs for this project.
  btr_insert('btr_diffs')
    ->fields(array(
        'pguid' => sha1($origin . $project),
        'lng' => $lng,
        'nr' => $max_nr + 1,
        'diff' => file_get_contents($file_diff),
        'ediff' => file_get_contents($file_ediff),
        'comment' => $comment,
        'uid' => $GLOBALS['user']->uid,
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();
}

/**
 * Return a list of saved diffs for the given project/lng.
 *
 * @param $origin
 *   The origin of the project.
 *
 * @param $project
 *   The name of the project.
 *
 * @param $lng
 *   The language of the translation files.
 */
function project_diff_list($origin, $project, $lng) {
  $diff_list = btr_query(
    'SELECT nr, time, comment FROM {btr_diffs}
     WHERE pguid = :pguid AND lng = :lng
     ORDER BY time ASC',
    array(
      ':pguid' => sha1($origin . $project),
      ':lng' => $lng,
    ))
    ->fetchAll();

  return $diff_list;
}

/**
 * Get and return the content of the specified diff.
 */
function project_diff_get($origin, $project, $lng, $nr, $format = 'diff') {
  $diff_field = ($format=='ediff' ? 'ediff' : 'diff');
  $diff = btr_query(
    "SELECT $diff_field FROM {btr_diffs}
     WHERE pguid = :pguid AND lng = :lng AND nr = :nr
     ORDER BY time ASC",
    array(
      ':pguid' => sha1($origin . $project),
      ':lng' => $lng,
      ':nr' => $nr,
    ))
    ->fetchField();

  return $diff;
}