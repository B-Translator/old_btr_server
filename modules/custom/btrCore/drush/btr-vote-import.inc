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
      "drush btrp-vote --user=user1 fr \$(pwd)/kturtle_fr/" => 'Vote as user1 all the given French translations.',
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
  btr::vote_import($user->uid, $lng, $path);
}
