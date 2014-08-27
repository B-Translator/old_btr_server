<?php
/**
 * @file
 * Drush commands for importing/exporting *.po files.
 */

/**
 * Implementation of hook_drush_command().
 *
 * @return
 *   An associative array describing commands.
 */
function btranslator_drush_command() {
  $items = array();

  // The command 'btr-project-list'
  $items['btr-project-list'] = array(
    'description' => "List imported projects, filtered by origin/project.

Options origin and project can contain '%' (for LIKE matches).
If --project='-' then only a list of 'origin' is outputed.
",
    'arguments' => array(
    ),
    'options' => array(
      'origin' => 'The pattern for matching the origin.',
      'project' => 'The pattern for matching the project.',
    ),
    'examples' => array(
      "drush btrp-ls --origin=KDE --project=k%" => 'List KDE projects that start with k.',
      "drush btrp-ls --project=-" => 'Get a list of all origins.'
    ),
    'aliases' => array('btrp-ls'),
    //'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

  // The command 'btr-project-import-templates'
  $items['btr-project-import-templates'] = array(
    'description' => "Import the POT files of a project into the B-Translator DB.
",
    'arguments' => array(
      'origin' => 'The origin of the project (ubuntu, GNOME, KDE, etc.)',
      'project' => 'The name of the project that is being imported.',
      'path' => 'The directory of the POT files of the project (absolute path or relative to DRUPAL_ROOT).',
    ),
    'options' => array(
      'user'  => 'The username of the user that is importing templates.',
    ),
    'examples' => array(
      "drush btrp-impot KDE kturtle \\      \n      \$(pwd)/kturtle/" => 'Import kturtle into the DB.',
    ),
    'aliases' => array('btrp-impot'),
    //'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

  // The command 'btr-project-import-translations'
  $items['btr-project-import-translations'] = array(
    'description' => "Import the translation (PO) files of a project/language into the DB.
",
    'arguments' => array(
      'origin'  => 'The origin of the project (ubuntu, GNOME, KDE, etc.)',
      'project' => 'The name of the project.',
      'lng'     => 'The language of translation (de, fr, sq, en_GB, etc.)',
      'path' => 'The directory of the PO files of the project (absolute path or relative to DRUPAL_ROOT).',
    ),
    'options' => array(
      'user'  => 'The username of the user that is importing translations.',
    ),
    'examples' => array(
      "drush btrp-impo \\\n   KDE kturtle fr \$(pwd)/kturtle_fr/" => 'Import the French translation of kturtle into the DB.',
    ),
    'aliases' => array('btrp-impo'),
  );

  // The command 'btr-project-import-votes'
  $items['btr-project-import-votes'] = array(
    'description' => "Bulk import of translations and votes from PO files.
",
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
    'aliases' => array('btrp-vote'),
  );

  // The command 'btr-project-del'
  $items['btr-project-del'] = array(
    'description' => "Delete everything related to the given origin and project
(but not the strings, translations, etc.)

If no project is given, then all the projects of the given origin
will be deleted. If the origin is NULL, then all the projects
of the given name (from any origin) will be deleted.
",
    'arguments' => array(
    ),
    'options' => array(
      'origin' => 'The origin of the project to be deleted.',
      'project' => 'The name of the project to be deleted.',
      'purge' => 'If true, then snapshots and diffs are deleted as well.',
    ),
    'examples' => array(
      "drush btrp-erase --origin=KDE --project=kturtle" => 'Erase KDE/kturtle from the DB.',
    ),
    'aliases' => array('btrp-erase'),
    //'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

  // The command 'btr-project-export'.
  $items['btr-project-export'] = array(
    'description' => "Export the PO files of a project from the DB.

The export mode 'most_voted' (which is the default one) exports the
most voted translations and suggestions.

The export mode 'preferred' gives priority to translations that are
voted by a certain user or a group of users. It requires an additional
option (preferred_voters) to specify the user (or a list of users)
whose translations are preferred. If a string has no translation that
is voted by any of the preferred users, then the most voted
translation is exported.

The export mode 'original' exports the translations of the original
file that was imported (useful for making an initial snapshot of the
project).
",
    'arguments' => array(
      'origin' => 'The origin of the project (ubuntu, GNOME, KDE, etc.)',
      'project' => 'The name of the project that is being exported.',
      'lng' => 'The language of translation (de, fr, sq, en_GB, etc.)',
      'path' => 'The directory where the PO files will be exported.',
    ),
    'options' => array(
      'user' => 'The username of the user who has requested the export.',
      'quiet' => 'Don\'t print progress output.',
      'export_mode' => "'most_voted' (default) or 'preferred' or 'original'",
      'preferred_users' => 'Comma separated list of emails of the preferred_users.',
      'preferred_users_list' => 'File with the emails of the preferred users, one per line.'
    ),
    'examples' => array(
      "drush btrp-export KDE kdeedu sq $(pwd)/kdeedu/" => 'Export KDE/kdeedu/sq into kdeedu/.',
    ),
    'aliases' => array('btrp-export'),
  );

  // The 'po-export' command
  $items['po-export'] = array(
    'description' => "Export the PO file of a translation from the DB.
",
    'arguments' => array(
      'origin'  => 'The origin of the project (ubuntu, GNOME, KDE, etc.)',
      'project' => 'The name of the project that is being exported.',
      'lng'     => 'The language of translation (de, fr, sq, en_GB, etc.)',
      'file.po' => 'File to save the exported translation (absolute path or relative to DRUPAL_ROOT). If missing, write to stdout.',
    ),
    'options' => array(
    ),
    'examples' => array(
      "drush -l l10n-sq.org expo \\\n  KDE kturtle sq ../kturtle_sq.po" => 'Export KDE/kturtle Albanian into kturtle_sq.po.',
    ),
    'aliases' => array('expo'),
  );

  // These will appear in the list of topics when `drush topic` is executed.
  // To view this topic, run `drush --include=/full/path/to/examples topic`
  $items['btranslator-exposition'] = array(
    'description' => dt('Importing and exporting PO files from B-Translator.'),
    'hidden' => TRUE,
    'topic' => TRUE,
    'callback' => 'drush_print_file',
    'callback arguments' => array(dirname(__FILE__) . '/btranslator-topic.txt'),
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function btranslator_drush_help($section) {
  switch ($section) {
    case 'drush:btr-project-list':
      return dt("List imported projects, filtered by origin/project.");
    case 'drush:btr-project-import-templates':
      return dt("Import the POT files of a project into the B-Translator DB.");
    case 'drush:btr-project-import-translations':
      return dt("Import the PO files of a project/language into the DB.");
    case 'drush:btr-project-del':
      return dt("Erase a project from the DB.");
    case 'drush:btr-project-export':
      return dt("Export PO files of a project from the DB.");
    case 'meta:btranslator:title':
      return dt("B-Translator Commands");
    case 'meta:btranslator:summary':
      return dt("Handle the import/export of PO/POT files for B-Translator.");
  }
}

/**
 * Command callback for btr-project-list.
 */
function drush_btranslator_btr_project_list() {
  $origin = drush_get_option('origin');
  $project = drush_get_option('project');

  $project_list = btr::project_ls($origin, $project);

  foreach ($project_list as $project) {
    drush_print($project);
  }
}

/**
 * Command callback for btr-project-import-templates.
 */
function drush_btranslator_btr_project_import_templates($origin, $project, $path) {
  btr::project_import_pot($origin, $project, $path, $GLOBALS['user']->uid);
}

/**
 * Command callback for btr-project-import-translations.
 */
function drush_btranslator_btr_project_import_translations($origin, $project, $lng, $path) {
  try {
    $errors = btr::project_import_po($origin, $project, $lng, $path, $GLOBALS['user']->uid);
    foreach ($errors as $error)  drush_log($error, 'error');
  }
  catch (Exception $e) {
    $trace = $e->getTraceAsString();
    $trace = preg_replace('/^#0 .*/', '', $trace);
    $trace = str_replace(DRUPAL_ROOT.'/', '', $trace);
    drush_log($trace, 'error');
  }
}

/**
 * Command callback for btr-project-import-votes.
 */
function drush_btranslator_btr_project_import_votes($lng, $path) {
  btr::translations_import($GLOBALS['user']->uid, $lng, $path);
}

/**
 * Command callback for btr-project-del.
 */
function drush_btranslator_btr_project_del() {
  $origin = drush_get_option('origin');
  $project = drush_get_option('project');
  $purge = drush_get_option('purge');
  $purge = ($purge == 'false' ? FALSE : TRUE);

  btr::project_del($origin, $project, $purge);
}

/**
 * Command callback for po-export.
 */
function drush_btranslator_po_export($origin, $project, $lng, $file =NULL) {
  $path = drupal_get_path('module', 'btrCore') . '/data/export';
  $output = shell_exec("$path/po_export.php $origin $project $lng $file");
  print $output;
}

/**
 * Command callback for btr-project-export.
 */
function drush_btranslator_btr_project_export($origin, $project, $lng, $path) {
  $export_mode = drush_get_option('export_mode', 'most_voted');

  // Get the preferred users.
  if ($export_mode == 'preferred') {
    $preferred_users = drush_get_option('preferred_users', NULL);
    if ($preferred_users !== NULL) {
      $users = explode(',', $preferred_users);
    }
    else {
      $preferred_users_list = drush_get_option('preferred_users_list', NULL);
      if ($preferred_users_list !== NULL) {
        $users = file($preferred_users_list);
      }
    }
    $arr_users = array();
    if (is_array($users)) {
      foreach ($users as $user) {
        $user = trim($user);
        if ($user == '')  continue;
        $arr_users[] = $user;
      }
    }
  }

  // Export the project.
  btr::project_export($origin, $project, $lng, $path,
    $GLOBALS['user']->uid, FALSE, $export_mode, $arr_users);
}
