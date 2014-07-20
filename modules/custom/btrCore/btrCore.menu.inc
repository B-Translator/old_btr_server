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
  $items['translations/project/list'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project List',
    'page callback'   => 'btrCore_project_list',
    'file'            => 'includes/project_callback.inc',
    'access callback' => TRUE,
  );

  // Return a list of the templates (names of POT files) for a project.
  $items['translations/project/templates'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project Templates',
    'page callback'   => 'btrCore_project_templates',
    'file'            => 'includes/project_callback.inc',
    'access callback' => TRUE,
  );

  // Return as plain-text the PO file for a given origin/project/lng.
  $items['translations/project/export'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project Export',
    'page callback'   => 'btrCore_project_export',
    'file'            => 'includes/project_callback.inc',
    'access callback' => TRUE,
  );

  // Return as an archive the PO files for a given origin/project/lng.
  // Usefull for projects that have many POT files, like LibreOffice, Mozilla, etc.
  $items['translations/project/export_tgz'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project Export',
    'page callback'   => 'btrCore_project_export_tgz',
    'file'            => 'includes/project_callback.inc',
    'access callback' => TRUE,
  );

  // Return the items of a vocabulary and all the corresponding translations.
  $items['translations/vocabulary/export'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Export Vocabulary',
    'page callback'   => 'btrCore_vocabulary_export',
    'file'            => 'includes/vocabulary.inc',
    'access callback' => TRUE,
  );

  // Return as plain-text the diff of the PO file for a given origin/project/lng,
  // which contains the latest most-voted suggestions since the last snapshot.
  // It gets the parameters origin/project/lng[/nr[/ediff]].
  $items['translations/project/diff'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project Export',
    'page callback'   => 'btrCore_project_diff',
    'file'            => 'includes/project_callback.inc',
    'access callback' => TRUE,
  );

  // The link that is sent to the user for downloading an exported file.
  // The URL is of the form 'translations/exports/filename.tgz'
  // and the filename is passed as a parameter to the function.
  $items['translations/exports'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Download Exported File',
    'page callback'   => 'btrCore_get_exported_file',
    'file'            => 'includes/project_callback.inc',
    'access callback' => TRUE,
  );


  // Return a string context, related projects (where a string is found), etc.
  $items['translations/string_details'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'String details',
    'page callback'   => 'btrCore_string_details',
    'file'            => 'includes/ajax_callbacks.inc',
    'access callback' => TRUE,
  );

  // Autocomplete callback for project textfields.
  $items['translations/autocomplete/project'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project autocomplete',
    'page callback'   => 'btrCore_project_autocomplete',
    'file'            => 'includes/ajax_callbacks.inc',
    'access callback' => TRUE,
  );

  // Autocomplete callback for origin textfields.
  $items['translations/autocomplete/origin'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Origin autocomplete',
    'page callback'   => 'btrCore_origin_autocomplete',
    'file'            => 'includes/ajax_callbacks.inc',
    'access callback' => TRUE,
  );

  // Autocomplete callback for user textfields.
  $items['translations/autocomplete/user'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'User autocomplete',
    'page callback'   => 'btrCore_user_autocomplete',
    'file'            => 'includes/ajax_callbacks.inc',
    'access callback' => TRUE,
  );

  // Autocomplete callback for strings.
  $items['translations/autocomplete/string'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'String autocomplete',
    'page callback'   => 'btrCore_string_autocomplete',
    'file'            => 'includes/ajax_callbacks.inc',
    'access callback' => TRUE,
  );

  // Return latest translations.
  $items['translations/latest'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Latest Translation Feedback',
    'page callback'   => 'btrCore_latest',
    'file'            => 'includes/latest.inc',
    'access callback' => TRUE,
  );

  // Return a random twitter.
  $items['translations/twitter'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Return a random string (and translations) in a form suitable for twitter.',
    'page callback'   => 'btrCore_twitter',
    'file'            => 'includes/twitter.inc',
    'access callback' => TRUE,
  );

  // Return a json list of languages and their details.
  $items['translations/languages'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Return a json list of languages and their details.',
    'page callback'   => 'btrCore_languages',
    'file'            => 'includes/languages.inc',
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

