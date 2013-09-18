<?php
/**
 * Implements hook_menu().
 */
function l10n_feedback_menu() {

  $items = array();

  $items['admin/config/btr/general'] = array(
    'title'            => 'B-Translator',
    'description'      => 'B-Translator configuration settings.',
    'page callback'    => 'drupal_get_form',
    'page arguments'   => array('l10n_feedback_config'),
    'access arguments' => array('btranslator-admin'),
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

  return $items;
}
