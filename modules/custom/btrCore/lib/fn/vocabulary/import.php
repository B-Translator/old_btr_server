<?php
/**
 * @file
 * Import the terms and translations of a vocabulary from a text file.
 */

namespace BTranslator;
use \btr;

/**
 * Import the terms and translations of a vocabulary from a text file.
 *
 * @param $name
 *   The name of the vocabulary.
 *
 * @param $lng
 *   The language of the vocabulary.
 *
 * @param $file
 *   The text file with terms and translations (having the same format as export TXT1).
 *
 * @param $uid
 *   ID of the user that has requested the import.
 *
 * @return
 *   Array of messages, where each item is is an array of a message and a type,
 *   where type can be one of 'status', 'warning', 'error'.
 */
function vocabulary_import($name, $lng, $file, $uid = 1) {
  // Check access permissions.
  $account = user_load($uid);
  if (!user_access('btranslator-suggest', $account)) {
    $msg = t('No rights for contributing suggestions!');
    return [[$msg, 'error']];
  }
  // Check that the language matches the translation language of the user.
  if (!user_access('btranslator-admin', $account) and ($lng != $account->translation_lng)) {
    $msg = t('No rights for contributing to language <strong>!lng</strong>.', ['!lng' => $lng]);
    return [[$msg, 'error']];
  }

  // Process each line of the file.
  $messages = array();
  $lines = file($file, FILE_IGNORE_NEW_LINES);
  for ($i=0, $n = count($lines); $i < $n; $i++) {
    $line = $lines[$i];
    if (strpos($line, '<==>') === FALSE)  continue;

    // Get the string and translations from the line.
    list($string, $translations) = explode('<==>', $line, 2);
    $string = trim($string);
    $translations = trim($translations);
    $arr_translations = explode(' / ', $translations);

    // Add the string.
    $sguid = btr::vocabulary_string_add($name, $lng, $string, $uid, $notify=FALSE);

    // Add the translations.
    foreach ($arr_translations as $translation) {
      list($tguid, $arr_msg) = btr::translation_add($sguid, $lng, $translation, $uid=1, $notify=FALSE);
      $messages = array_merge($messages, $arr_msg);
    }
  }

  // Return any messages that are collected during the import.
  return $messages;
}
