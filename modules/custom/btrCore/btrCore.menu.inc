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
    'file'             => 'btrCore.admin.inc',
  );

  // Return a list of the imported projects,
  // filtered by the given origin/project.
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

  // Return as plain-text the diff of the PO file for a given origin/project/lng,
  // which contains the latest most-voted suggestions since the last snapshot.
  // It gets the parameters origin/project/lng[/nr[/ediff]].
  $items['project/diff'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project Export',
    'page callback'   => 'btrCore_project_diff',
    'file'            => 'callback/project.inc',
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
  $items['translations/string_details'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'String details',
    'page callback'   => 'btrCore_string_details',
    'file'            => 'callback/ajax.inc',
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

/**
 * Implements hook_menu_alter().
 *
 * Change the user account menu:
 *  - Remove the View tab.
 *  - Make the Profile tab the default one.
 *  - Change the title of hybridauth.
 */
function btrCore_menu_alter(&$items) {
  $user = $items['user/%user'];
  $profile = $items['user/%user/edit-profile'];

  // Remove the View tab.
  unset($items['user/%user/view']);

  // Make the Profile tab the default one.
  $items['user/%user'] = $profile;
  $items['user/%user']['title callback'] = $user['title callback'];
  $items['user/%user']['title arguments'] = $user['title arguments'];
  $items['user/%user']['menu_name'] = $user['menu_name'];
  unset($items['user/%user']['type']);
  unset($items['user/%user']['weight']);

  $items['user/%user/edit-profile'] = array(
    'type' =>  MENU_DEFAULT_LOCAL_TASK,
    'title' => $profile['title'],
    'weight' => $profile['weight'],
    'module' => $profile['module'],
  );

  // Change the title of hybridauth.
  $items['user/%user/hybridauth']['title'] = t('Authentication');
}
