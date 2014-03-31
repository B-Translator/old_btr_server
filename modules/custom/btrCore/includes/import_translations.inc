<?php
/**
 * Importing translations from PO files.
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
 * @param $pofile
 *   A PO file with translations, or an archive of PO files
 *   (accepted extensions: .tar, .gz, .tgz, .bz2, .xz, .7z, .zip).
 *
 * @param $lng
 *   Language of translations.
 *
 * @return
 *   Array of notification messages; each notification message
 *   is an array of a message and a type, where type can be one of
 *   'status', 'warning', 'error'.
 */
function btr_import_translations($pofile, $lng) {
  // Check access permissions.
  if (!user_access('btranslator-suggest')) {
    $msg = t('You do not have enough rights for making suggestions!');
    return array(array($msg, 'error'));
  }

  // Make sure that the current user can make
  // translations for the given language.
  $user = user_load($GLOBALS['user']->uid);
  if ($lng != $user->translation_lng) {
    $msg = t('You cannot give translations for the language !lng', array('!lng' => $lng));
    return array(array($msg, 'error'));
  }

  // Parse the given PO file.
  $data_path = drupal_get_path('module', 'btrCore') . '/data';
  include_once($data_path . '/gettext/POParser.php');
  $parser = new POParser;
  $entries = $parser->parse($pofile);

  // Process each gettext entry.
  foreach ($entries as $entry) {
    // Get the string sguid.
    $sguid = _btr_import_get_sguid($entry);
    if ($sguid === NULL)  continue;

    // Get the translation.
    $translation = is_array($entry['msgstr']) ? implode("\0", $entry['msgstr']) : $entry['msgstr'];
    if (trim($translation) === '')  continue;

    // Add the translation for this string.
    _btr_import_add_translation($sguid, $lng, $translation);
  }

  return array();
}

/**
 * Returns the sguid of the string.
 *
 * If such a string does not exist, insert it into the DB.  However,
 * if the msgid is empty (the header entry), don't add a string for
 * it. The same for some other entries like 'translator-credits' etc.
 * In such cases return NULL.
 */
function _btr_import_get_sguid($entry) {
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

  // Make sure that such a string is stored in the DB.
  if (!btr_get_string($sguid)) {
    $query = "
      INSERT INTO btr_strings
	 (string, context, sguid, uid, time, count)
      VALUES
	 (:string, :context, :sguid, :uid, :time, :count)";
    $params = array(
      ':string' => $string,
      ':context' => $context,
      ':sguid' => $sguid,
      ':uid' => $GLOBALS['user']->uid,
      ':time' => REQUEST_TIME,
      ':count' => 1,
    );
    btr_query($query, $params);
  }

  return $sguid;
}

/**
 * Add the given translation to the string, if it does not exist.
 * If it exists, just add a vote for the translation and set the
 * author, if the translation has no author.
 */
function _btr_import_add_translation($sguid, $lng, $translation) {
  $tguid = sha1($translation . $lng . $sguid);

  // Check whether this translation exists.
  $query = 'SELECT * FROM {btr_translations} WHERE tguid = :tguid';
  $args = array(':tguid' => $tguid);
  $result = btr_query($query, $args)->fetch();

  if (!$result) {
    // Add the translation for this string.
    btr_add_translation($sguid, $lng, $translation);
  }
  else {
    // Add a vote for the translation.
    btr_add_vote($tguid);
    // Update the author of the translations.
    if ($result->umail == 'admin@example.com') {
      $query = 'UPDATE {btr_translations}
                  SET umail = :umail
                  WHERE tguid = :tguid';
      $args = array(
		    ':umail' => $GLOBALS['user']->init,
        ':tguid' => $tguid,
      );
      btr_query($query, $args);
    }
  }
}