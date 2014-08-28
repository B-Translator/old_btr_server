<?php
/**
 * @file
 * Functions for importing translation files of a project.
 */

namespace BTranslator;

module_load_include('php', 'btrCore', 'lib/gettext/POParser');

/**
 * Import translation (PO) files of a project.
 *
 * Templates of the project (POT files) must have been imported first.
 * If the corresponding template for a file does not exist, it will
 * not be imported and a warning will be given.
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
 * @param $path
 *   The directory where the translation (PO) files are located.
 *
 * @param $uid
 *   ID of the user that has requested the import.
 */
function project_import($origin, $project, $lng, $path, $uid = 0) {
  // Switch to the given user.
  global $user;
  $original_user = $user;
  $old_state = drupal_save_session();
  drupal_save_session(FALSE);
  $user = user_load($uid);

  // Calculate the project ID.
  $pguid = sha1($origin . $project);

  // Check that the project exists.
  $query = "SELECT pguid FROM {btr_projects} WHERE pguid = '$pguid'";
  if (!btr_query($query)->fetchField()) {
    $errors[] = t("The project '!origin/!project' does not exist.",
                array('!origin' => $origin, '!project' => $project));
    return $errors;
  }

  // Get a list of all PO files on the given directory.
  $files = file_scan_directory($path, '/.*\.po$/');

  // Process each PO file.
  $errors = array();
  foreach ($files as $file) {
    // Get the filename relative to the path, and the name of the template.
    $filename = preg_replace("#^$path/#", '', $file->uri);
    $tplname = preg_replace('#\.po?$#', '', $filename);

    // Get the template id.
    $query = 'SELECT potid FROM {btr_templates}
              WHERE pguid = :pguid AND tplname = :tplname ';
    $args = array(':pguid' => $pguid, ':tplname' => $tplname);
    $potid = btr_query($query, $args)->fetchField();

    // Check that the template exists.
    if (!$potid) {
      $errors[] = t("The template '!tplname' does not exist.",
                  array('!tplname' => $tplname));
      continue;
    }

    // Process this PO file.
    _process_po_file($potid, $tplname, $lng, $file->uri, $filename);
  }

  // Switch back to the original user.
  $user = $original_user;
  drupal_save_session($old_state);

  return $errors;
}

/**
 * Create a new template, parse the POT file, insert the locations
 * and insert the strings.
 */
function _process_po_file($potid, $tplname, $lng, $file, $filename) {
  // Parse the PO file.
  $parser = new POParser;
  $entries = $parser->parse($file);

  // Get headers and comments.
  $headers = $comments = NULL;
  if ($entries[0]['msgid'] == '') {
    $headers = $entries[0]['msgstr'];
    $comments = $entries[0]['translator-comments'];
  }

  // Add a file and get its id.
  $fid = _add_file($file, $filename, $potid, $lng, $headers, $comments);
  if ($fid === NULL)  continue;

  // Process each gettext entry.
  foreach ($entries as $entry) {
    // Get the string sguid.
    $sguid = _get_string_sguid($entry);
    if ($sguid === NULL)  continue;

    // Add the translation for this string.
    $translation = is_array($entry['msgstr']) ? implode("\0", $entry['msgstr']) : $entry['msgstr'];
    if (trim($translation) != '') {
      _add_translation($sguid, $lng, $translation);
    }
  }
}

/**
 * Insert a file in the DB, if it does not already exist.
 * Return the file id and a list of messages.
 */
function _add_file($file, $filename, $potid, $lng, $headers, $comments) {
  $messages = array();

  // Get the sha1 hash of the file.
  $hash = sha1_file($file);

  // Check whether the file already exists.
  $query = "SELECT potid, lng FROM {btr_files} WHERE hash = :hash";
  $row = btr_query($query, array(':hash' => $hash))->fetchAssoc();

  // If file already exists.
  if (isset($row['potid'])) {
    if ($row['potid']==$potid and $row['lng']==$lng) {
      $msg = t('Already imported, skipping: !filename',
             array('!filename' => $filename));
      $messages = array(array($msg, 'error'));
      return array(NULL, $messages);
    }
    else {
      // file already imported for some other template or language
      $sql = "SELECT p.origin, p.project, t.tplname
              FROM {btr_templates} t
              LEFT JOIN {btr_projects} p ON (t.pguid = p.pguid)
              WHERE t.potid = :potid";
      $row1 = btr_query($sql, array(':potid' => $row['potid']))->fetchAssoc();
      $msg = t("File '!filename' has already been imported for '!origin/!project' and language '!lng' as '!tplname'.",
             array(
               '!filename' => $filename,
               '!origin' => $row1['origin'],
               '!project' => $row1['project'],
               '!lng' => $row['lng'],
               '!tplname' => $row1['tplname'],
             ));
      $messages[] = array($msg, 'warning');
    }
  }

  // Insert the file.
  $fid = btr_insert('btr_files')
    ->fields(array(
        'filename' => $filename,
        'content' => file_get_contents($file),
        'hash' => $hash,
        'potid' => $potid,
        'lng' => $lng,
        'headers' => $headers,
        'comments' => $comments,
        'uid' => $GLOBALS['user']->uid,
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();

  return array($fid, $messages);
}

/**
 * Return the sguid of the string, if it already exists on the DB;
 * otherwise return NULL.
 */
function _get_string_sguid($entry) {
  // Get the string.
  $string = $entry['msgid'];
  if ($entry['msgid_plural'] !== NULL) {
    $string .= "\0" . $entry['msgid_plural'];
  }

  // Get the context.
  $context = $entry['msgctxt'];

  // Get the $sguid of this string.
  $sguid = sha1($string . $context);

  // Check that it exists.
  $get_sguid = "SELECT sguid FROM {btr_strings} WHERE sguid = '$sguid'";
  if ($sguid == btr_query($get_sguid)->fetchField()) {
    return $sguid;
  }
  else {
    return NULL;
  };
}

/**
 * Insert a translation into DB.
 */
function _add_translation($sguid, $lng, $translation) {
  $tguid = sha1($translation . $lng . $sguid);

  // Check first that such a translation does not exist.
  $get_tguid = 'SELECT tguid FROM {btr_translations} WHERE tguid = :tguid';
  $args = array(':tguid' => $tguid);
  if (btr_query($get_tguid, $args)->fetchField())  return $tguid;

  // Insert a new translations.
  $account = user_load($GLOBALS['user']->uid);
  btr_insert('btr_translations')
    ->fields(array(
        'sguid' => $sguid,
        'lng' => $lng,
        'translation' => $translation,
        'tguid' => $tguid,
        'count' => 0,
        'umail' => $account->init,
        'ulng' => $lng,
        'time' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
    ->execute();
}