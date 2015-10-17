<?php
/**
 * Description of the command 'btr-vote-import'.
 */
function _btr_vote_import_drush_command() {
  return array(
    'description' => "Bulk import of translations and votes from PO files.",
    'arguments' => array(
      'lng'     => 'The language of translation (de, fr, sq, en_GB, etc.)',
      'path' => 'The directory of the PO files (absolute path or relative to DRUPAL_ROOT).',
    ),
    'options' => array(
      'user'  => 'The username of the user who has made the translations.',
    ),
    'examples' => array(
      "drush btr-vote --user=user1 fr \$(pwd)/kturtle_fr/" => 'Vote as user1 all the given French translations.',
    ),
    'aliases' => array('btr-vote'),
  );
}

/**
 * Help text for the command 'btr-vote-import'.
 */
function _btr_vote_import_drush_help() {
  return dt('Bulk import of translations and votes from PO files.

The option --user is required because it declares the author of
translations.

It is like a bulk translation and voting service. For any translation
in the PO files, it will be added as a suggestion if such a
translation does not exist, or it will just be voted if such a
translation already exists. In case that the translation already
exists but its author is not known, then the given user will be
recorded as the author of the translation.

This can be useful if translators prefer to work off-line with PO
files. They can export the PO files of a project, work on them with
desktop tools (like Lokalize) to translate or correct exported
translations, then import back the correct translations.
');
}

/**
 * Callback function for the command 'btr-vote-import'.
 */
function drush_btranslator_btr_vote_import($lng, $path) {
  global $user;
  if (!$user->uid) {
    drush_log(t('You must specify a user with the option --user.'), 'error');
    drupal_exit();
  }

  // Check that the given language exists.
  _btranslator_drush_check_params(NULL, NULL, $lng);

  // Check user permissions.
  _drush_btranslator_btr_vote_import_check_permissions($lng);

  // Check the path.
  $path = _drush_btranslator_btr_vote_import_check_path($path);

  // Import translations and votes.
  btr::vote_import($user->uid, $lng, $path);
  foreach (btr::messages() as $msg)  drush_log($msg[0], $msg[1]);
}

/**
 * Check user permissions.
 */
function _drush_btranslator_btr_vote_import_check_permissions($lng) {
  global $user;

  // Check user access permissions.
  if (!user_access('btranslator-suggest')) {
    drush_log(t('User "!user" has no rights for contributing translations!', ['!user' => $user->name]), 'error');
    drupal_exit();
  }
  if (!user_access('btranslator-vote')) {
    drush_log(t('User "!user" has no rights for submiting votes!', ['!user' => $user->name]), 'error');
    drupal_exit();
  }

  // Get and check the parameter 'lng'.
  if (!in_array($lng, btr::languages_get())) {
    drush_log(t('Language "!lng" is not supported.', array('!lng' => $lng)), 'error');
    drupal_exit();
  }

  // Make sure that this user can make translations for the given language.
  if ($lng != $user->translation_lng) {
    drush_log(t('User "!user" cannot submit translations for the language "!lng"',
        ['!user' => $user->name, '!lng' => $lng]
      ), 'error');
    drupal_exit();
  }
}

/**
 * Check the path.
 */
function _drush_btranslator_btr_vote_import_check_path($path) {
  // Check that there is such a file.
  if (!file_exists($path)) {
    drush_log(t('File "!file" does not exist.', ['!file' => $path]), 'error');
    drupal_exit();
  }

  if (is_dir($path))  return $path;

  // Check the extension of the file.
  $extensions = 'po tar gz tgz bz2 xz 7z zip';
  $regex = '/\.(' . preg_replace('/ +/', '|', preg_quote($extensions)) . ')$/i';
  if (!preg_match($regex, $path)) {
    $msg = t('Only files with the following extensions are allowed: !files-allowed.',
           ['!files-allowed' => $extensions]);
    drush_log($msg, 'error');
    drupal_exit();
  }

  // Extract the file in a temporary directory.
  $file = $path;
  $filename = basename($file);
  $tmpdir = '/tmp/' . sha1_file($file);
  mkdir($tmpdir, 0700);
  exec("cp $file $tmpdir/");
  exec("cd $tmpdir ; dtrx -q -n $filename 2>/dev/null");

  // Return the directory where the files are extracted.
  return $tmpdir;
}
