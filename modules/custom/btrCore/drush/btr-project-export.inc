<?php
/**
 * Description of the command 'btr-project-export'.
 */
function _btr_project_export_drush_command() {
  return array(
    'description' => "Export the PO files of a project from the DB.",
    'arguments' => array(
      'origin' => 'The origin of the project (ubuntu, GNOME, KDE, etc.)',
      'project' => 'The name of the project that is being exported.',
      'lng' => 'The language of translation (de, fr, sq, en_GB, etc.)',
      'path' => 'The directory where the PO files will be exported.',
    ),
    'options' => array(
      'export-mode' => "'most_voted' (default) or 'preferred' or 'original'",
      'preferred-voters' => 'Comma separated list of the preferred users.',
      'user' => 'The username of the user who is requesting the export.',
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
  return "Export the PO files of a project from the DB.

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
";
}

/**
 * Callback function for the command 'btr-project-export'.
 */
function drush_btranslator_btr_project_export($origin, $project, $lng, $path) {
  // Check parameters $origin, $project, $lng.
  _btranslator_drush_check_params($origin, $project, $lng);

  // Check the export_mode.
  $export_mode = drush_get_option('export-mode', 'most_voted');
  if (!in_array($export_mode, ['most_voted', 'preferred', 'original'])) {
    drush_log(t("Unknown export mode '!export_mode'.",
        ['!export_mode' => $export_mode]), 'error');
    drupal_exit();
  }

  // Get the preferred users.
  if ($export_mode == 'preferred') {
    $preferred_voters = drush_get_option('preferred-voters', NULL);
    list($arr_emails, $error_messages) = btr::utils_get_emails($preferred_voters);
    if (!empty($error_messages)) {
      foreach ($error_messages as $msg)  drush_log($msg[0], $msg[1]);
      drupal_exit();
    }
  }

  // Export the project.
  btr::project_export($origin, $project, $lng, $path, $export_mode, $arr_emails);
  foreach (btr::messages() as $msg)  drush_log($msg[0], $msg[1]);
}
