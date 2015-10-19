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
 */
function vocabulary_import($name, $lng, $file, $uid = NULL) {
  // Check access permissions.
  $uid = btr::user_check($uid);
  $account = user_load($uid);
  if (!user_access('btranslator-suggest', $account) and !user_access('btranslator-admin', $account)) {
    $msg = t('No rights for contributing suggestions!');
    btr::messages($msg, 'error');
    return;
  }
  // Check that the language matches the translation language of the user.
  if (($lng != $account->translation_lng) and !user_access('btranslator-admin', $account)) {
    $msg = t('No rights for contributing to language <strong>!lng</strong>.', ['!lng' => $lng]);
    btr::messages($msg, 'error');
    return;
  }

  // Process each line of the file.
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
      btr::translation_add($sguid, $lng, $translation, $uid=1, $notify=FALSE);
    }
  }
}
