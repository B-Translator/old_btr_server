<?php
/**
 * @file
 * Functions for importing translation files of a project.
 */

namespace BTranslator;
use \btr;

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
 *   It can also be the full path to a single PO file.
 *
 * @param $uid
 *   ID of the user that has requested the import.
 *
 * @param $quiet
 *   Don't print progress output (default FALSE).
 */
function project_import($origin, $project, $lng, $path, $uid = 1, $quiet = FALSE) {
  // Define the constant QUIET inside the namespace.
  define('BTranslator\QUIET', $quiet);

  // Print progress output.
  QUIET || print "project_import: $origin/$project/$lng: $path\n";

  // Switch to the given user.
  global $user;
  $original_user = $user;
  $old_state = drupal_save_session();
  drupal_save_session(FALSE);
  $user = user_load($uid);

  // Check that the project exists.
  $pguid = btr::db_query(
    'SELECT pguid FROM {btr_projects} WHERE pguid = :pguid',
    array(':pguid' => sha1($origin . $project))
  )->fetchField();
  if (!$pguid) {
    QUIET || print "***Error*** The project '$origin/$project' does not exist.\n";
    return;
  }

  // Import the given PO files.
  _import_po_files($origin, $project, $lng, $path);

  // Add user as admin of the project.
  _add_project_admin($origin, $project, $lng, $user->init);

  // Subscribe user to this project.
  btr::project_subscribe($origin, $project, $user->uid);

  // Make initial snapshots after importing PO files.
  _make_snapshots($origin, $project, $lng, $path);

  // Switch back to the original user.
  $user = $original_user;
  drupal_save_session($old_state);
}

/**
 * Import the given PO files.
 */
function _import_po_files($origin, $project, $lng, $path) {
  // If the given $path is a single file, just process that one and stop.
  if (is_file($path)) {
    $filename = basename($path);
    $tplname = $project;
    _process_po_file($origin, $project, $tplname, $lng, $path, $filename);

    // Done.
    return;
  }

  // Otherwise, when $path is a directory, process each file in it.

  // Get a list of all PO files on the given directory.
  $files = file_scan_directory($path, '/.*\.po$/');

  // Process each PO file.
  foreach ($files as $file) {
    $filename = preg_replace("#^$path/#", '', $file->uri);
    $tplname = preg_replace('#\.po?$#', '', $filename);
    _process_po_file($origin, $project, $tplname, $lng, $file->uri, $filename);
  }
}

/**
 * Create a new template, parse the POT file, insert the locations
 * and insert the strings.
 */
function _process_po_file($origin, $project, $tplname, $lng, $file, $filename) {
  // Print progress output.
  QUIET || print "import_po_file: $filename\n";

  // Get the template id.
  $potid = btr::db_query(
    'SELECT potid FROM {btr_templates}
       WHERE pguid = :pguid AND tplname = :tplname ',
    array(
      ':pguid' => sha1($origin . $project),
      ':tplname' => $tplname,
    ))
    ->fetchField();

  // Check that the template exists.
  if (!$potid) {
    QUIET ||  print "***Warning*** The template '$tplname' does not exist.\n";
    return;
  }

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
  if ($fid === NULL)  return;

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
 * Return the file id.
 */
function _add_file($file, $filename, $potid, $lng, $headers, $comments) {
  // Get the sha1 hash of the file.
  $hash = sha1_file($file);

  // Check whether the file already exists.
  $row = btr::db_query(
    'SELECT potid, lng FROM {btr_files} WHERE hash = :hash',
    array(':hash' => $hash)
  )->fetchAssoc();

  // If file already exists.
  if (isset($row['potid'])) {
    if ($row['potid']==$potid and $row['lng']==$lng) {
      QUIET || print "***Warning*** Already imported, skipping: $filename\n";
      return NULL;
    }
    else {
      // file already imported for some other template or language
      $row1 = btr::db_query(
        'SELECT p.origin, p.project, t.tplname
         FROM {btr_templates} t
         LEFT JOIN {btr_projects} p ON (t.pguid = p.pguid)
         WHERE t.potid = :potid',
        array(':potid' => $row['potid'])
      )->fetchAssoc();
      $msg = t("File '!filename' has already been imported for '!origin/!project' and language '!lng' as '!tplname'.",
             array(
               '!filename' => $filename,
               '!origin' => $row1['origin'],
               '!project' => $row1['project'],
               '!lng' => $row['lng'],
               '!tplname' => $row1['tplname'],
             ));
      QUIET || print "***Warning*** $msg\n";
    }
  }

  // The DB field of content is MEDIUMTEXT (16777216 bytes),
  // check that the file does not exceed this length.
  if (filesize($file) > 16777216) {
    print "***Warning*** File is too large to be stored in the DB (longer than MEDIUMTEXT); skipped.\n";
    return NULL;
  }

  // Insert the file.
  $fid = btr::db_insert('btr_files')
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

  return $fid;
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
  if ($sguid == btr::db_query($get_sguid)->fetchField()) {
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
  // The DB field of the translation is VARCHAR(1000),
  // check that translation does not exceed this length.
  if (strlen($translation) > 1000) {
    QUIET || print $translation . "\n";
    QUIET || print "***Warning*** Translation is too long  to be stored in the DB (more than 1000 chars); skipped.\n";
    return;
  }

  $tguid = sha1($translation . $lng . $sguid);

  // Check first that such a translation does not exist.
  $get_tguid = 'SELECT tguid FROM {btr_translations} WHERE tguid = :tguid';
  $args = array(':tguid' => $tguid);
  if (btr::db_query($get_tguid, $args)->fetchField())  return $tguid;

  // Insert a new translations.
  $account = user_load($GLOBALS['user']->uid);
  btr::db_insert('btr_translations')
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

/**
 * Add the current user (that imports the project) as admin of the project.
 */
function _add_project_admin($origin, $project, $ulng, $umail) {
  $pguid = sha1($origin . $project);

  // Delete it first, if he exists.
  btr::db_delete('btr_user_project_roles')
    ->condition('umail', $umail)
    ->condition('ulng', $ulng)
    ->condition('role', 'admin')
    ->execute();

  // Add as admin.
  btr::db_insert('btr_user_project_roles')
    ->fields([
        'umail' => $umail,
        'ulng' => $ulng,
        'pguid' => $pguid,
        'role' => 'admin',
      ])
    ->execute();
}


/**
 * Make initial snapshots after importing PO files.
 *
 * The first snapshot contains the original files that are imported.
 *
 * The second snapshot contains the export of the original files, and
 * it will produce and store the first diff. This initial diff
 * actually contains the differences that come as a result of
 * formating changes between the original format and the exported
 * format. It also contains the entries that are skipped during the
 * import.
 *
 * Another snapshot is done as well, with the most_voted translations.
 * The diff that will be generated (if any), will contain all the
 * previous suggestions (before the import).
 */
function _make_snapshots($origin, $project, $lng, $path) {
  // Store the imported files into the DB as an initial snapshot.
  $snapshot_file = tempnam('/tmp', 'snapshot_file_');
  if (is_file($path)) {
    $dir = dirname($path);
    $filename = basename($path);
    exec("tar -cz -f $snapshot_file -C $dir $filename");
  }
  else {
    exec("tar -cz -f $snapshot_file -C $path .");
  }
  btr::project_snapshot_save($origin, $project, $lng, $snapshot_file);
  unlink($snapshot_file);

  // Make a second snapshot, which will generate a diff
  // with the initial snapshot, and save it into the DB.
  $diff_comment = 'Import diff. Contains formating changes, any skiped entries, etc.';
  btr::project_snapshot($origin, $project, $lng, $diff_comment, $export_mode = 'original');

  // Make another snapshot, which will contain all the previous
  // suggestions (before the import), in a single diff.
  $diff_comment = 'Initial diff after import. Contains all the previous suggestions (before the last import).';
  btr::project_snapshot($origin, $project, $lng, $diff_comment, $export_mode = 'most_voted');
}
