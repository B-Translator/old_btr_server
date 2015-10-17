<?php
/**
 * @file
 * Function: schedule_project_import()
 */

namespace BTranslator;
use \btr;
use \stdClass, \Exception;

/**
 * Create a project or update an existing one by importing the POT and PO files
 * of the project.
 *
 * @param $origin
 *   The origin of the project that will be imported.
 *
 * @param $project
 *   The name of the project that will be imported.
 *
 * @param $uploaded_file
 *   The file that is uploaded.
 *   - It can be an archive of type: tgz, bz2, 7z, zip.
 *   - The POT files should be in the subfolder 'pot/', directly in the root
 *     folder of the archive.
 *   - The PO files of a language should be in the subfolder named after the
 *     code of that language (for example: sq/, de/, fr/, etc.)
 *   - The path and name of each PO file should be the same as the corresponding
 *     POT file, except for the extension (.po instead of .pot).
 */
function schedule_project_import($origin, $project, $uploaded_file) {
  // Check that the given project does not belong to another user.
  $query = 'SELECT uid FROM {btr_projects} WHERE pguid = :pguid';
  $args = [':pguid' => sha1($origin . $project)];
  $uid = btr::db_query($query, $args)->fetchField();
  if ($uid && ($uid != $GLOBALS['user']->uid)) {
    $msg = t("There is already a project '!project' created by another user! Please choose another project name.", ['!project' => "$origin/$project"]);
    btr::messages($msg, 'error');
    return;
  }

  // Check the extension of the uploaded file.
  $extensions = 'tgz bz2 7z zip';
  $regex = '/\.(' . preg_replace('/ +/', '|', preg_quote($extensions)) . ')$/i';
  if (!preg_match($regex, $uploaded_file['name'])) {
    $msg = t('Only files with the following extensions are allowed: %files-allowed.',
           ['%files-allowed' => $extensions]);
    btr::messages($msg, 'error');
    return;
  }

  // Move the uploaded file to 'private://' (/var/www/uploads/).
  $file_uri = 'private://' . $uploaded_file['name'];
  if (!drupal_move_uploaded_file($uploaded_file['tmp_name'], $file_uri)) {
    btr::messages(t('Failed to move uploaded file.'), 'error');
    return;
  }

  // Delete the file from DB, if such a file has been saved previously.
  $query = 'SELECT fid FROM {file_managed} WHERE uri = :uri AND uid = :uid';
  $args = [':uri' => $file_uri, ':uid' => $uid];
  $fid = \db_query($query, $args)->fetchField();
  if ($fid) {
    \db_query('DELETE FROM {file_managed} WHERE uri = :uri AND uid = :uid', $args);
  }

  // Save the file data to the DB.
  $file = new stdClass();
  $file->uid = $uid;
  $file->status = FILE_STATUS_PERMANENT;
  $file->filename = trim(drupal_basename($uploaded_file['name']), '.');
  $file->uri = $file_uri;
  $file->filemime = file_get_mimetype($file->filename);
  $file->filesize = $uploaded_file['size'];
  try {
    $file = file_save($file);
  }
  catch (Exception $e) {
    btr::messages($e->getMessage(), 'error');
    return;
  }

  // Schedule the import.
  btr::queue('import_project', [[
        'uid' => $GLOBALS['user']->uid,
        'fid' => $file->fid,
        'origin' => $origin,
        'project' => $project,
      ]]);

  // Output a notification message.
  $msg = t("Import of the project '!project' is scheduled. You will be notified by email when it is done.",
         ['!project' => $origin . '/' . $project]);
  btr::messages($msg);
}
