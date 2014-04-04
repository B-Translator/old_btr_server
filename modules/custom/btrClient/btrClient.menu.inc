<?php
/**
 * Implements hook_menu().
 */
function btrClient_menu() {

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

  $items['admin/config/btr/client'] = array(
    'title'            => 'BTR Client',
    'description'      => 'B-Translator Client configuration settings.',
    'page callback'    => 'drupal_get_form',
    'page arguments'   => array('btrClient_config'),
    'access arguments' => array('btranslator-admin'),
    'file'             => 'btrClient.admin.inc',
  );

  $items['translations'] = array(
    'type'            => MENU_NORMAL_ITEM,
    'title'           => 'Translations',
    'description'     => 'Vote the best translation for a string, or suggest a better translation.',
    'page callback'   => 'btrClient_vote',
    'file'            => 'translations/vote.inc',
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
    'page callback'   => 'btrClient_search',
    'file'            => 'translations/search.inc',
    'access callback' => TRUE,
    'weight'          => 2,
  );

  $items['translations/export'] = array(
    'type'            => MENU_LOCAL_TASK,
    'title'           => 'Export',
    'description'     => 'Export the most voted translations of a project into a PO file.',
    'page callback'   => 'btrClient_export',
    'file'            => 'translations/export.inc',
    'access callback' => 'user_is_logged_in',
    'weight'          => 3,
  );

  $items['translations/import'] = array(
    'type'            => MENU_LOCAL_TASK,
    'title'           => 'Import',
    'description'     => 'Import strings and translations from POT/PO files of projects.',
    'page callback'   => 'btrClient_import',
    'file'            => 'translations/import.inc',
    'access callback' => 'btr_user_access',
    'access arguments' => array('btranslator-import'),
    'weight'          => 4,
  );

  $items['translations/addterm'] = array(
    'type'            => MENU_LOCAL_TASK,
    'title'           => 'Add Term',
    'description'     => 'Add a new term on a vocabulary.',
    'page callback'   => 'btrClient_addterm',
    'file'            => 'translations/addterm.inc',
    'access callback' => 'btr_user_access',
    'access arguments' => array('btranslator-import'),
    'weight'          => 5,
  );

  return $items;
}
