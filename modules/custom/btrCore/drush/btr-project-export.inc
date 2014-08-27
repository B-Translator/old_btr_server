<?php
/**
 * Description of the command 'btr-project-export'.
 */
function _btr_project_export_drush_command() {
  return array(
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
}

/**
 * Help text for the command 'btr-project-export'.
 */
function _btr_project_export_drush_help() {
  return dt("Export PO files of a project from the DB.");
}

/**
 * Callback function for the command 'btr-project-export'.
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
