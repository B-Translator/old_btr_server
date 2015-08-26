<?php
/**
 * @file
 * Function: schedule_project_import()
 */

namespace BTranslator;
use \btr;
use \stdClass, \Exception;

/**
 * Create a custom project or update an existing one by importing PO/POT files.
 *
 * This is useful for creating custom translation projects. The PO/POT
 * files that are uploaded will be used for importing strings and
 * translations. If there are no POT files, then the PO files will be
 * used both for importing strings and for importing translations. If
 * there are POT files and PO files, their names have to match (except
 * for the extension).
 *
 * If there are several PO/POT files, upload them as an archive (tar,
 * tgz, bz2, 7z, zip).
 *
 * If you want to create a vocabulary, use 'vocabulary' as the origin
 * of the project, and add the suffix '_lng' to the project name. Also
 * use 'msgctxt "project_name"' as the context of each string in the
 * PO/POT file.
 *
 * @param $origin
 *   The origin of the project that will be imported.
 *
 * @param $project
 *   The name of the project that will be imported.
 *
 * @param $uploaded_file
 *   The file that is uploaded.
 *
 * @return
 *   Array of notification messages; each notification message
 *   is an array of a message and a type, where type can be one of
 *   'status', 'warning', 'error'.
 */
function schedule_project_import($origin, $project, $uploaded_file) {
  // Check access permissions.
  if (!user_access('btranslator-import')) {
    $msg = t('You do not have enough rights for importing projects!');
    return array(array($msg, 'error'));
  }

  // Check that the given project does not belong to another user.
  $uid = btr::db_query(
    'SELECT uid FROM {btr_projects} WHERE pguid = :pguid',
    array(
      ':pguid' => sha1($origin . $project),
    ))
    ->fetchField();
  if ($uid && ($uid != $GLOBALS['user']->uid)) {
    $msg = t("There is already a project '!project' created by another user! Please choose another project name.", array('!project' => "$origin/$project"));
    return array(array($msg, 'error'));
  }

  // Check the extension of the uploaded file.
  $extensions = 'pot po tar gz tgz bz2 xz 7z zip';
  $regex = '/\.(' . preg_replace('/ +/', '|', preg_quote($extensions)) . ')$/i';
  if (!preg_match($regex, $uploaded_file['name'])) {
    $msg = t('Only files with the following extensions are allowed: %files-allowed.',
           array('%files-allowed' => $extensions));
    return array(array($msg, 'error'));
  }

  // Move the uploaded file to 'private://' (/var/www/uploads/).
  $file_uri = 'private://' . $uploaded_file['name'];
  if (!drupal_move_uploaded_file($uploaded_file['tmp_name'], $file_uri)) {
    return array(array(t('Failed to move uploaded file.'), 'error'));
  }

  // Save the file data to the DB.
  $file = new stdClass();
  $file->uid = $GLOBALS['user']->uid;
  $file->status = FILE_STATUS_PERMANENT;
  $file->filename = trim(drupal_basename($uploaded_file['name']), '.');
  $file->uri = $file_uri;
  $file->filemime = file_get_mimetype($file->filename);
  $file->filesize = $uploaded_file['size'];
  try {
    $file = file_save($file);
    $messages = array();
  }
  catch (Exception $e) {
    return array(array($e->getMessage(), 'error'));
  }

  // Schedule the import.
  btr::queue('import_project', array(array(
        'uid' => $GLOBALS['user']->uid,
        'fid' => $file->fid,
        'origin' => $origin,
        'project' => $project,
      )));

  // Return a notification message.
  $msg = t("Import of the project '!project' is scheduled. You will be notified by email when it is done.",
         array('!project' => $origin . '/' . $project));
  return array(array($msg, 'status'));
}
