<?php
/**
 * @file
 * Functions for creating translation projects.
 */

namespace BTranslator;
use \btr;

module_load_include('php', 'btrCore', 'lib/gettext/POParser');

/**
 * Create a new project from POT files.
 *
 * If such a project already exists, it is erased first.
 *
 * @param $origin
 *   The origin of the project.
 *
 * @param $project
 *   The name of the project.
 *
 * @param $path
 *   The directory where the template (POT) files are located.
 *   It can also be the full path to a single POT/PO file.
 *
 * @param $uid
 *   ID of the user that has requested the import.
 */
function project_add($origin, $project, $path, $uid = NULL) {
  btr::messages("Adding project: $origin/$project: $path");

  // Erase the project if it exists.
  btr::project_del($origin, $project, $erase = TRUE, $purge = FALSE);

  // Make sure that the user is not NULL or 0 (anonymous).
  $uid = btr::user_check($uid);

  // Create a project.
  $pguid = sha1($origin . $project);
  btr::db_insert('btr_projects')
    ->fields(array(
        'pguid' => $pguid,
        'origin' => $origin,
        'project' => $project,
        'uid' => $uid,
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();

  // Import the given POT/PO files.
  _import_pot_files($origin, $project, $path, $uid);

  // Subscribe user to this project.
  btr::project_subscribe($origin, $project, $uid);
}

/**
 * Import the given POT/PO files.
 */
function _import_pot_files($origin, $project, $path, $uid) {
  $pguid = sha1($origin . $project);

  // If the given $path is a single file, just process that one and stop.
  if (is_file($path)) {
    $filename = basename($path);
    $tplname = $project;
    _process_pot_file($pguid, $tplname, $path, $filename, $uid);
    return;
  }

  // Otherwise, when $path is a directory, process each file in it.

  // Get a list of all template (POT) files on the given directory.
  $files = file_scan_directory($path, '/.*\.pot$/');
  if (empty($files)) {
    // If there are no POT files, get a list of PO files instead.
    $files = file_scan_directory($path, '/.*\.po$/');
  }

  // Process each POT file.
  foreach ($files as $file) {
    $filename = preg_replace("#^$path/#", '', $file->uri);
    $tplname = preg_replace('#\.pot?$#', '', $filename);
    _process_pot_file($pguid, $tplname, $file->uri, $filename, $uid);
  }
}

/**
 * Create a new template, parse the POT file, insert the locations
 * and insert the strings.
 */
function _process_pot_file($pguid, $tplname, $file, $filename, $uid) {
  btr::messages("Importing POT file: $filename");

  // Create a new template.
  $potid = btr::db_insert('btr_templates')
    ->fields(array(
        'tplname' => $tplname,
        'filename' => $filename,
        'pguid' => $pguid,
        'uid' => $uid,
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();

  // Parse the POT file.
  $parser = new POParser;
  $entries = $parser->parse($file);

  // Process each gettext entry.
  foreach ($entries as $entry) {
    // Create a new string, or increment its count.
    $sguid = _add_string($entry, $uid);
    if ($sguid == NULL) continue;

    // Insert a new location record.
    _insert_location($potid, $sguid, $entry);
  }
}

/**
 * Insert a new string in the DB for the msgid and msgctxt of the
 * given entry. If such a string already exists, then just increment
 * its count.
 *
 * If the msgid is empty (the header entry), don't add a string
 * for it. The same for some other entries like 'translator-credits' etc.
 *
 * Return the sguid of the string record, or NULL.
 */
function _add_string($entry, $uid) {
  // Get the string.
  $string = $entry['msgid'];
  if ($entry['msgid_plural'] !== NULL) {
    $string .= "\0" . $entry['msgid_plural'];
  }

  // Don't add the header entry as a translatable string.
  // Don't add strings like 'translator-credits' etc. as translatable strings.
  if ($string == '')  return NULL;
  if (preg_match('/.*translator.*credit.*/', $string))  return NULL;

  // Get the context.
  $context = $entry['msgctxt'];

  // Get the $sguid of this string.
  $sguid = sha1($string . $context);

  // Increment the count of the string.
  $count = btr::db_update('btr_strings')
    ->expression('count', 'count + :one', array(':one' => 1))
    ->condition('sguid', $sguid)
    ->execute();

  // The DB fields of the string and context are VARCHAR(1000),
  // check that they do not exceed this length.
  if (strlen($string) > 1000 or strlen($context) > 1000) {
    $msg = t("The string or its context is too long  to be stored in the DB (more than 1000 chars); skipped.")
      . "\n\nContext: " . $context . "\n\nString: " . $string;
    btr::messages($msg, 'warning');
    return NULL;
  }

  // If no record was affected, it means that such a string
  // does not exist, so insert a new string.
  if (!$count) {
    btr::db_insert('btr_strings')
      ->fields(array(
          'string' => $string,
          'context' => $context,
          'sguid' => sha1($string . $context),
          'uid' => $uid,
          'time' => date('Y-m-d H:i:s', REQUEST_TIME),
          'count' => 1,
        ))
      ->execute();
  }

  // TODO: If the entry has a previous-msgid, then deprecate the
  //       corresponding string.

  return $sguid;
}

/**
 * Insert a new record on the locations table
 */
function _insert_location($potid, $sguid, $entry) {
  btr::db_insert('btr_locations')
    ->fields(array(
        'sguid' => $sguid,
        'potid' => $potid,
        'translator_comments' => _cut($entry['translator-comments'], 1000),
        'extracted_comments' => _cut($entry['extracted-comments'], 1000),
        'line_references' => _cut(implode(' ', $entry['references']), 1000),
        'flags' => _cut(implode(' ', $entry['flags']), 1000),
        'previous_msgctxt' => _cut($entry['previous-msgctxt'], 1000),
        'previous_msgid' => _cut($entry['previous-msgid'], 1000),
        'previous_msgid_plural' => _cut($entry['previous-msgid_plural'], 1000),
      ))
    ->execute();
}

/**
 * Return only the first $length chars of the string.
 */
function _cut($str, $length) {
  $l = $length - 3;
  return (strlen($str) > $l + 3) ? substr($str, 0, $l) . '...' : $str;
}
