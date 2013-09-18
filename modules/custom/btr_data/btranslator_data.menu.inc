<?php
/**
 * Implements hook_menu().
 */
function btranslator_data_menu() {

  $items = array();

  $items['admin/config/btr'] = array(
    'title' => 'B-Translator',
    'description' => 'B-Translator Configuration',
    'weight' => -100,
    'page callback' => 'system_admin_menu_block_page',
    'access arguments' => array('btranslator_data_config'),
    'file' => 'system.admin.inc',
    'file path' => drupal_get_path('module', 'system'),
    //'position' => 'right',
  );

  $items['admin/config/btr/data'] = array(
    'title'            => 'B-Translator Data',
    'description'      => 'B-Translator Back-End configuration settings.',
    'page callback'    => 'drupal_get_form',
    'page arguments'   => array('btranslator_data_config'),
    'access arguments' => array('btranslator-admin'),
    'file'             => 'btranslator_data.admin.inc',
  );

  // Return a plain-text list of all the imported projects,
  // filtered by the given origin/project.
  $items['translations/project/list'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project List',
    'page callback'   => 'btranslator_data_project_list',
    'file'            => 'includes/projects.inc',
    'access callback' => TRUE,
  );

  // Return as plain-text the PO file for a given origin/project/lng.
  $items['translations/project/export'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project Export',
    'page callback'   => 'btranslator_data_project_export',
    'file'            => 'includes/projects.inc',
    'access callback' => TRUE,
  );

  // Return as an archive the PO files for a given origin/project/lng.
  // Usefull for projects that have many POT files, like LibreOffice, Mozilla, etc.
  $items['translations/project/export_tgz'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project Export',
    'page callback'   => 'btranslator_data_project_export_tgz',
    'file'            => 'includes/projects.inc',
    'access callback' => TRUE,
  );

  // Return as plain-text the diff of the PO file for a given origin/project/lng,
  // which contains the latest most-voted suggestions since the last snapshot.
  // It gets the parameters origin/project/lng[/nr[/ediff]].
  $items['translations/project/diff'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project Export',
    'page callback'   => 'btranslator_data_project_diff',
    'file'            => 'includes/projects.inc',
    'access callback' => TRUE,
  );

  // The link that is sent to the user for downloading an exported file.
  // The URL is of the form 'translations/exports/filename.tgz'
  // and the filename is passed as a parameter to the function.
  $items['translations/exports'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Download Exported File',
    'page callback'   => 'btranslator_data_get_exported_file',
    'file'            => 'includes/projects.inc',
    'access callback' => TRUE,
  );


  // Return a string context, related projects (where a string is found), etc.
  $items['translations/string_details'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'String details',
    'page callback'   => 'btranslator_data_string_details',
    'file'            => 'includes/ajax_callbacks.inc',
    'access callback' => TRUE,
  );

  // Autocomplete callback for project textfields.
  $items['translations/autocomplete/project'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Project autocomplete',
    'page callback'   => 'btranslator_data_project_autocomplete',
    'file'            => 'includes/ajax_callbacks.inc',
    //'access arguments' => array('access localization community'),
    'access callback' => TRUE,
  );

  // Autocomplete callback for origin textfields.
  $items['translations/autocomplete/origin'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Origin autocomplete',
    'page callback'   => 'btranslator_data_origin_autocomplete',
    'file'            => 'includes/ajax_callbacks.inc',
    //'access arguments' => array('access localization community'),
    'access callback' => TRUE,
  );

  // Autocomplete callback for user textfields.
  $items['translations/autocomplete/user'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'User autocomplete',
    'page callback'   => 'btranslator_data_user_autocomplete',
    'file'            => 'includes/ajax_callbacks.inc',
    //'access arguments' => array('access localization community'),
    'access callback' => TRUE,
  );

  // Return a RSS feed.
  $items['translations/rss-feed'] = array(
    'type'            => MENU_CALLBACK,
    'title'           => 'Latest Translation Feedback',
    'page callback'   => 'btranslator_data_rss_feed',
    'file'            => 'includes/rss_feed.inc',
    //'access arguments' => array('access content'),
    'access callback' => TRUE,
  );

  return $items;
}
