<?php
/**
 * @file
 * Importing translations from PO files.
 */

namespace BTranslator;
use \btr;

/**
 * Import translations and votes from PO files.
 *
 * It is like a bulk translation and voting service. For any
 * translation in the PO files, it will be added as a suggestion if
 * such a translation does not exist, or it will just be voted if such
 * a translation already exists. In case that the translation already
 * exists but its author is not known, then you (the user who makes
 * the import) will be recorded as the author of the translation.
 *
 * This can be useful for translators if they prefer to work off-line
 * with PO files. They can export the PO files of a project, work on
 * them with desktop tools (like Lokalize) to translate or correct
 * exported translations, and then import back to B-Translator the
 * translated/corrected PO files.
 *
 * @param $uid
 *   ID of the user that has uploaded the file.
 *
 * @param $lng
 *   Language of translations.
 *
 * @param $path
 *   A directory with PO files to be used for import.
 *
 * @return
 *   Array of notification messages; each notification message
 *   is an array of a message and a type, where type can be one of
 *   'status', 'warning', 'error'.
 */
function vote_import($uid, $lng, $path) {
  // Check access permissions.
  $account = user_load($uid);
  if (!user_access('btranslator-suggest', $account)) {
    $msg = t('No rights for contributing suggestions!');
    return [[$msg, 'error']];
  }
  if (!user_access('btranslator-vote', $account)) {
    $msg = t('No rights for submitting votes!');
    return [[$msg, 'error']];
  }
  // Check that the language matches the translation language of the user.
  if (!user_access('btranslator-admin', $account) and ($lng != $account->translation_lng)) {
    $msg = t('No rights for contributing to language <strong>!lng</strong>.', ['!lng' => $lng]);
    return [[$msg, 'error']];
  }

  // Get the mail of the user.
  $account = user_load($uid);
  $umail = $account->init;

  // Get a list of all PO files on the path.
  $files = file_scan_directory($path, '/.*\.po$/');

  // Import the PO files.
  $messages = array();
  module_load_include('php', 'btrCore', 'lib/gettext/POParser');
  foreach ($files as $file) {
    // Parse the PO file.
    $parser = new POParser;
    $entries = $parser->parse($file->uri);

    // Process each gettext entry.
    foreach ($entries as $entry) {
      // Get the string sguid.
      list($sguid, $msgs) = _get_sguid($entry, $uid);
      if ($sguid === NULL) {
        $messages = array_merge($messages, $msgs);
        continue;
      }

      // Get the translation.
      $translation = is_array($entry['msgstr']) ? implode("\0", $entry['msgstr']) : $entry['msgstr'];
      if (trim($translation) === '')  continue;

      // Add the translation for this string.
      $msgs = _add_translation($sguid, $lng, $translation, $uid);
      $messages = array_merge($messages, $msgs);
    }
  }

  // Return any messages that were generated during the import.
  return $messages;
}

/**
 * Returns the sguid of the string and an array of messages.
 *
 * If such a string does not exist, insert it into the DB.  However,
 * if the msgid is empty (the header entry), don't add a string for
 * it. The same for some other entries like 'translator-credits' etc.
 * In such cases return NULL.
 */
function _get_sguid($entry, $uid) {
  $messages = array();

  // Get the string.
  $string = $entry['msgid'];
  if (isset($entry['msgid_plural'])) {
    $string .= "\0" . $entry['msgid_plural'];
  }

  // Don't add the header entry as a translatable string.
  // Don't add strings like 'translator-credits' etc. as translatable strings.
  if ($string == '') {
    return array(NULL, array());
  }
  if (preg_match('/.*translator.*credit.*/', $string)) {
    return array(NULL, array());
  }

  // Get the context.
  $context = isset($entry['msgctxt']) ? $entry['msgctxt'] : '';

  // The DB fields of the string and context are VARCHAR(1000),
  // check that they do not exceed this length.
  if (strlen($string) > 1000 or strlen($context) > 1000) {
    $msg = t(" !context\n !string\n The string or its context is too long to be stored in the DB (more than 1000 chars); skipped.\n",
           array('!context' => $context, '!string' => $string));
    return array(NULL, array(array($msg, 'warning')));
  }

  // Get the $sguid of this string.
  $sguid = sha1($string . $context);

  // Make sure that such a string is stored in the DB.
  if (btr::string_get($sguid) === FALSE) {
    btr::db_insert('btr_strings')
      ->fields(array(
          'string' => $string,
          'context' => $context,
          'sguid' => $sguid,
          'uid' => $uid,
          'time' => date('Y-m-d H:i:s', REQUEST_TIME),
          'count' => 1,
        ))
      ->execute();
  }

  return array($sguid, array());
}

/**
 * Add the given translation to the string, if it does not exist.
 * If it exists, just add a vote for the translation and set the
 * author, if the translation has no author.
 */
function _add_translation($sguid, $lng, $translation, $uid) {
  // The DB field of the translation is VARCHAR(1000),
  // check that translation does not exceed this length.
  if (strlen($translation) > 1000) {
    print $translation . "\n";
    print "***Warning*** Translation is too long  to be stored in the DB (more than 1000 chars); skipped.\n";
    return array();
  }

  $tguid = sha1($translation . $lng . $sguid);
  $messages = array();

  // Check whether this translation exists.
  $query = 'SELECT * FROM {btr_translations} WHERE tguid = :tguid';
  $args = array(':tguid' => $tguid);
  $result = btr::db_query($query, $args)->fetch();

  if (!$result) {
    // Add the translation for this string.
    list($_, $msgs) = btr::translation_add($sguid, $lng, $translation, $uid);
    $messages = array_merge($messages, $msgs);
  }
  else {
    // Add a vote for the translation.
    list($_, $msgs) = btr::vote_add($tguid, $uid);
    $messages = array_merge($messages, $msgs);

    // Update the author of the translations.
    $account = user_load($uid);
    if (empty($result->umail) or $result->umail == 'admin@example.com') {
      btr::db_update('btr_translations')
        ->fields(array(
            'umail' => $account->init,
            'time' => date('Y-m-d H:i:s', REQUEST_TIME),
          ))
        ->condition('tguid', $tguid)
        ->execute();
    }
  }

  return $messages;
}
