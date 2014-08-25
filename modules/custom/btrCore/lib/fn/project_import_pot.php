<?php
namespace BTranslator;

/**
 * @file
 * Functions for importing translation projects.
 */

/**
 * Import a new project from POT files.
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
 *
 * @param $uid
 *   ID of the user that has requested the import.
 */
function project_import_pot($origin, $project, $path, $uid = 0) {
  // Switch to the given user.
  global $user;
  $original_user = $user;
  $old_state = drupal_save_session();
  drupal_save_session(FALSE);
  $user = user_load($uid);

  // Erase the project if it exists.
  include_once(dirname(__FILE__) . '/project_erase.php');
  project_erase($origin, $project, $purge = TRUE);
  // \btr::project_erase($origin, $project, $purge = TRUE);

  // Create a project.
  $pguid = sha1($origin . $project);
  btr_insert('btr_projects')
    ->fields(array(
        'pguid' => $pguid,
        'origin' => $origin,
        'project' => $project,
        'uid' => $GLOBALS['user']->uid,
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();

  // Get a list of all template (POT) files on the given directory.
  $files = file_scan_directory($path, '/.*\.pot$/');
  if (empty($files)) {
    // If there are no POT files, get a list of PO files instead.
    $files = file_scan_directory($path, '/.*\.po$/');
  }

  // Process each POT file.
  foreach ($files as $file) {
    // Get the filename relative to the path, and the name of the template.
    $filename = preg_replace("#^$path/#", '', $file->uri);
    $tplname = preg_replace('#\.pot?$#', '', $filename);

    // Process the POT file.
    _process_pot_file($pguid, $tplname, $file->uri, $filename);
  }

  // Switch back to the original user.
  $user = $original_user;
  drupal_save_session($old_state);
}

/**
 * Create a new template, parse the POT file, insert the locations
 * and insert the strings.
 */
function _process_pot_file($pguid, $tplname, $file, $filename) {
  // Create a new template.
  $potid = btr_insert('btr_templates')
    ->fields(array(
        'tplname' => $tplname,
        'filename' => $filename,
        'pguid' => $pguid,
        'uid' => $GLOBALS['user']->uid,
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();

  // Parse the POT file.
  module_load_include('php', 'btrCore', 'lib/gettext/POParser');
  $parser = new \BTranslator\POParser;
  $entries = $parser->parse($file);

  // Process each gettext entry.
  foreach ($entries as $entry) {
    // Create a new string, or increment its count.
    $sguid = _add_string($entry);
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
function _add_string($entry) {
  // Get the string.
  $string = $entry['msgid'];
  if (isset($entry['msgid_plural'])) {
    $string .= "\0" . $entry['msgid_plural'];
  }

  // Don't add the header entry as a translatable string.
  // Don't add strings like 'translator-credits' etc. as translatable strings.
  if ($string == '')  return NULL;
  if (preg_match('/.*translator.*credit.*/', $string))  return NULL;

  // Get the context.
  $context = isset($entry['msgctxt']) ? $entry['msgctxt'] : '';

  // Get the $sguid of this string.
  $sguid = sha1($string . $context);

  // Increment the count of the string.
  $count = btr_update('btr_strings')
    ->expression('count', 'count + :one', array(':one' => 1))
    ->condition('sguid', $sguid)
    ->execute();

  // If no record was affected, it means that such a string
  // does not exist, so insert a new string.
  if (!$count) {
    btr_insert('btr_strings')
      ->fields(array(
          'string' => $string,
          'context' => _cut($context, 1000),
          'sguid' => sha1($string . $context),
          'uid' => $GLOBALS['user']->uid,
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
  $entry += array(
    'translator-comments' => NULL,
    'extracted-comments' => NULL,
    'references' => array(),
    'flags' => array(),
    'previous-msgctxt' => NULL,
    'previous-msgid' => NULL,
    'previous-msgid_plural' => NULL,
  );
  btr_insert('btr_locations')
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
