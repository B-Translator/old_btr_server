<?php
/**
 * Implements hook_menu().
 */
function l10n_feedback_menu() {

  $items['admin/config/system/btranslator'] = array(
    'title'            => 'B-Translator',
    'page callback'    => 'drupal_get_form',
    'page arguments'   => array('l10n_feedback_config'),
    'access arguments' => array('btranslator-admin'),
    'description'      => 'B-Translator configuration settings.',
    'file'             => 'l10n_feedback.admin.inc',
  );

  $items['translations'] = array(
    'type'            => MENU_NORMAL_ITEM,
    'title'           => 'Translations',
    'description'     => 'Vote the best translation for a string, or suggest a better translation.',
    'page callback'   => 'l10n_feedback_vote',
    'file'            => 'includes/translations/vote.inc',
    'access callback' => TRUE,
  );

  $items['translations/vote'] = array(
    'type'            => MENU_DEFAULT_LOCAL_TASK,
    'title'           => 'Vote',
    'weight'          => 1,
  );

  $items['translations/search'] = array(
    'type'            => MENU_LOCAL_TASK,
    'title'           => 'Search',
    'description'     => 'Search strings and translations using various filters.',
    'page callback'   => 'l10n_feedback_search',
    'file'            => 'includes/translations/search.inc',
    'access callback' => TRUE,
    'weight'          => 2,
  );

  $items['translations/export'] = array(
    'type'            => MENU_LOCAL_TASK,
    'title'           => 'Export',
    'description'     => 'Export the most voted translations of a project into a PO file.',
    'page callback'   => 'l10n_feedback_export',
    'file'            => 'includes/translations/export.inc',
    'access callback' => 'user_is_logged_in',
    'weight'          => 3,
  );

  // The link that is sent to the user for downloading an exported file.
  // The URL is of the form 'translations/exports/filename.tgz'
  // and the filename is passed as a parameter to the function.
  $items['translations/exports'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Download Exported File',
    'page callback'   => 'l10n_feedback_get_exported_file',
    'file'            => 'includes/translations/export.inc',
    'access callback' => TRUE,
  );

  $items['translations/import'] = array(
    'type'            => MENU_LOCAL_TASK,
    'title'           => 'Import',
    'description'     => 'Import strings and translations from POT/PO files of projects.',
    'page callback'   => 'l10n_feedback_import',
    'file'            => 'includes/translations/import.inc',
    //'access callback' => 'user_access',  //default
    'access arguments' => array('btranslator-import'),
    'weight'          => 4,
  );

  $items['translations/addterm'] = array(
    'type'            => MENU_LOCAL_TASK,
    'title'           => 'Add Term',
    'description'     => 'Add a new term on the vocabulary.',
    'page callback'   => 'l10n_feedback_addterm',
    'file'            => 'includes/translations/import.inc',
    //'access callback' => 'user_access',  //default
    'access arguments' => array('btranslator-import'),
    'weight'          => 5,
  );

  $items['translations/get'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Get l10n Translation',
    'description'     => 'Get translation suggestions for a given string.',
    'page callback'   => 'l10n_feedback_get',
    'file'            => 'includes/translations/get.inc',
    'access callback' => TRUE,
  );

  // Return a plain-text list of all the imported projects,
  // filtered by the given origin/project.
  $items['translations/project/list'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project List',
    'page callback'   => 'l10n_feedback_project_list',
    'file'            => 'includes/projects.inc',
    'access callback' => TRUE,
  );

  // Return as plain-text the PO file for a given origin/project/lng.
  $items['translations/project/export'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project Export',
    'page callback'   => 'l10n_feedback_project_export',
    'file'            => 'includes/projects.inc',
    'access callback' => TRUE,
  );

  // Return as an archive the PO files for a given origin/project/lng.
  // Usefull for projects that have many POT files, like LibreOffice, Mozilla, etc.
  $items['translations/project/export_tgz'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project Export',
    'page callback'   => 'l10n_feedback_project_export_tgz',
    'file'            => 'includes/projects.inc',
    'access callback' => TRUE,
  );

  // Return as plain-text the diff of the PO file for a given origin/project/lng,
  // which contains the latest most-voted suggestions since the last snapshot.
  // It gets the parameters origin/project/lng[/nr[/ediff]].
  $items['translations/project/diff'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project Export',
    'page callback'   => 'l10n_feedback_project_diff',
    'file'            => 'includes/projects.inc',
    'access callback' => TRUE,
  );

  // Return a string context, related projects (where a string is found), etc.
  $items['translations/string_details'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'String details',
    'page callback'   => 'l10n_feedback_string_details',
    'file'            => 'includes/ajax_callbacks.inc',
    'access callback' => TRUE,
  );

  // Autocomplete callback for project textfields.
  $items['translations/autocomplete/project'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project autocomplete',
    'page callback'   => 'l10n_feedback_project_autocomplete',
    'file'            => 'includes/ajax_callbacks.inc',
    //'access arguments' => array('access localization community'),
    'access callback' => TRUE,
  );

  // Autocomplete callback for origin textfields.
  $items['translations/autocomplete/origin'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Origin autocomplete',
    'page callback'   => 'l10n_feedback_origin_autocomplete',
    'file'            => 'includes/ajax_callbacks.inc',
    //'access arguments' => array('access localization community'),
    'access callback' => TRUE,
  );

  // Autocomplete callback for user textfields.
  $items['translations/autocomplete/user'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'User autocomplete',
    'page callback'   => 'l10n_feedback_user_autocomplete',
    'file'            => 'includes/ajax_callbacks.inc',
    //'access arguments' => array('access localization community'),
    'access callback' => TRUE,
  );

  // Return a RSS feed.
  $items['translations/rss-feed'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Latest Translation Feedback',
    'page callback'   => 'l10n_feedback_rss_feed',
    'file'            => 'includes/rss_feed.inc',
    //'access arguments' => array('access content'),
    'access callback' => TRUE,
  );

  return $items;
}
