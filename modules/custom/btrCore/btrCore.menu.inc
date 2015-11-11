<?php
/**
 * Implements hook_menu().
 */
function btrCore_menu() {

  $items = array();

  $items['admin/config/btr'] = array(
    'title' => 'B-Translator',
    'description' => 'B-Translator Configuration',
    'weight' => -100,
    'page callback' => 'system_admin_menu_block_page',
    'file' => 'system.admin.inc',
    'file path' => drupal_get_path('module', 'system'),
    'access callback' => TRUE,
    //'position' => 'right',
  );

  $items['admin/config/btr/core'] = array(
    'title'            => 'BTR Core',
    'description'      => 'B-Translator Core configuration settings.',
    'page callback'    => 'drupal_get_form',
    'page arguments'   => array('btrCore_config'),
    'access arguments' => array('btranslator-admin'),
    'file'             => 'admin/core.inc',
  );

  $items['admin/config/btr/data'] = array(
    'title'            => 'BTR Data',
    'description'      => 'B-Translator Backup/Restore.',
    'page callback'    => 'drupal_get_form',
    'page arguments'   => ['btrCore_backup'],
    'access arguments' => ['btranslator-admin'],
    'file'            => 'admin/data.inc',
  );

  // Synchronize a project with the upstream one.
  $items['project/sync'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Synchronize Project',
    'page callback'   => 'btrCore_project_sync',
    'file'            => 'callback/project.inc',
    'access callback' => TRUE,
  );

  // Return a list of the imported projects,
  // filtered by the given origin/project.
  $items['project/list'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project List',
    'page callback'   => 'btrCore_project_list',
    'file'            => 'callback/project.inc',
    'access callback' => TRUE,
  );

  // Return a full list of all the imported projects and languages.
  $items['project/list/all'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project List',
    'page callback'   => 'btrCore_project_list_all',
    'file'            => 'callback/project.inc',
    'access callback' => TRUE,
  );

  // Return a list of vocabularies in JSON format.
  $items['vocabulary/list'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Vocabulary List',
    'page callback'   => 'btrCore_vocabulary_list',
    'file'            => 'callback/vocabulary_list.inc',
    'access callback' => TRUE,
  );

  // Return a list of the languages
  // for the given origin/project.
  $items['project/langs'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project List',
    'page callback'   => 'btrCore_project_langs',
    'file'            => 'callback/project.inc',
    'access callback' => TRUE,
  );

  // Return an archive of the PO files for a given origin/project/lng.
  $items['project/export'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project Export',
    'page callback'   => 'btrCore_project_export',
    'file'            => 'callback/project_export.inc',
    'access callback' => TRUE,
  );

  // Return the items of a vocabulary and all the corresponding translations.
  $items['vocabulary/export'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Export Vocabulary',
    'page callback'   => 'btrCore_vocabulary_export',
    'file'            => 'callback/vocabulary_export.inc',
    'access callback' => TRUE,
  );

  // Return as plain-text the diff of the PO file for a given origin/project/lng.
  // It gets the parameters origin/project/lng[/nr[/ediff]].
  $items['project/diff'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project Diffs',
    'page callback'   => 'btrCore_project_diff',
    'file'            => 'callback/diff.inc',
    'access callback' => TRUE,
  );

  // Return as a download the diff of the PO file for a given origin/project/lng.
  $items['project/diff-dl'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Diff Download',
    'page callback'   => 'btrCore_project_diff_download',
    'file'            => 'callback/diff.inc',
    'access callback' => TRUE,
  );

  // Return as a download the latest diff of the PO file for a given origin/project/lng.
  $items['project/diff-latest'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Latest Diff Download',
    'page callback'   => 'btrCore_project_diff_latest',
    'file'            => 'callback/diff_latest.inc',
    'access callback' => TRUE,
  );

  // Make a project snapshot for a given origin/project/lng.
  $items['project/snapshot'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Make Snapshot',
    'page callback'   => 'btrCore_project_snapshot',
    'file'            => 'callback/snapshot.inc',
    'access callback' => TRUE,
  );

  // The link that is sent to the user for downloading an exported file.
  // The URL is of the form 'exports/filename.tgz'
  // and the filename is passed as a parameter to the function.
  $items['exports'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Download Exported File',
    'page callback'   => 'btrCore_get_exported_file',
    'file'            => 'callback/exports.inc',
    'access callback' => TRUE,
  );

  // Return a string context, related projects (where a string is found), etc.
  $items['string_details'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'String details',
    'page callback'   => 'btrCore_string_details',
    'file'            => 'callback/string_details.inc',
    'access callback' => TRUE,
  );

  // Autocomplete callback for project textfields.
  $items['auto/project'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project autocomplete',
    'page callback'   => 'btrCore_project_autocomplete',
    'file'            => 'callback/ajax.inc',
    'access callback' => TRUE,
  );

  // Autocomplete callback for origin textfields.
  $items['auto/origin'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Origin autocomplete',
    'page callback'   => 'btrCore_origin_autocomplete',
    'file'            => 'callback/ajax.inc',
    'access callback' => TRUE,
  );

  // Autocomplete callback for user textfields.
  $items['auto/user'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'User autocomplete',
    'page callback'   => 'btrCore_user_autocomplete',
    'file'            => 'callback/ajax.inc',
    'access callback' => TRUE,
  );

  // Autocomplete callback for strings.
  $items['auto/string'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'String autocomplete',
    'page callback'   => 'btrCore_string_autocomplete',
    'file'            => 'callback/ajax.inc',
    'access callback' => TRUE,
  );

  // Return latest translations.
  $items['latest'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Latest Translation Feedback',
    'page callback'   => 'btrCore_latest',
    'file'            => 'callback/latest.inc',
    'access callback' => TRUE,
  );

  // Return a RSS feed.
  $items['rss-feed'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Latest Translation Feedback',
    'page callback'   => 'btrCore_rss_feed',
    'file'            => 'callback/rss_feed.inc',
    'access callback' => TRUE,
  );

  // Return a random twitter.
  $items['tweet'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Return a random string (and translations) in a form suitable for twitter.',
    'page callback'   => 'btrCore_tweet',
    'file'            => 'callback/tweet.inc',
    'access callback' => TRUE,
  );

  // Return a json list of languages and their details.
  $items['languages'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Return a json list of languages and their details.',
    'page callback'   => 'btrCore_languages',
    'file'            => 'callback/languages.inc',
    'access callback' => TRUE,
  );

  return $items;
}
