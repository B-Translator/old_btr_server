<?php
/**
 * @file
 * The callback function for the menu 'exports'.
 */

/**
 * The callback function for the menu 'exports'.
 * The URL is of the form 'exports/filename.tgz'
 * where the filename is passed as a parameter to the function.
 */
function btrCore_get_exported_file($filename =NULL) {

  $filename = check_plain($filename);
  if (empty($filename)) {
    drupal_set_message(t("Export file '!filename' does not exist!",
			 array('!filename' => $filename)), 'error');
    drupal_goto("translations");
    return;
  }

  // Get the full path of the export file.
  $export_path = variable_get('btr_export_path', '/var/www/exports');
  $export_file = $export_path . '/' . $filename;
  if (!file_exists($export_file)) {
    drupal_set_message(t("Export file '!filename' does not exist!",
			 array('!filename' => $filename)), 'error');
    drupal_goto("translations");
    return;
  }

  // Send the headers.
  $content_type = ( substr($filename, -4) == '.tgz'
                  ? 'application/x-compressed'
                  : 'application/octet-stream' );
  header('Content-Type: ' . $content_type);
  header('Content-Disposition: attachment; filename="' . $filename . '"');
  header('Content-Transfer-Encoding: binary');
  header("Content-Length: " . filesize($export_file));

  // Open the file in a binary mode and dump it to the browser.
  $fp = fopen($export_file, 'rb');
  fpassthru($fp);

  // Stop execution.
  exit(0);
}
