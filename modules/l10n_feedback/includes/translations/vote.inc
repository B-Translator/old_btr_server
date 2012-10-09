<?php
/**
 * @file
 * Functions specific to the menu path: translations/vote .
 */

/**
 * Include utility and theme functions.
 */
require_once(dirname(__FILE__) . '/list/list.inc');
require_once(dirname(__FILE__) . '/utils.inc');

/**
 * Menu callback: translations/vote
 * Vote the best translation for a string, or suggest a better translation.
 */
function l10n_feedback_vote($lng =NULL, $sguid =NULL, $one_time_login =NULL) {

  if ($one_time_login != NULL) {
    l10n_feedback_login_one_time($one_time_login);
    drupal_goto("translations/$lng/$sguid");
    return;
  }

  // If no $sguid is given as parameter, get the sguid of a string
  // and the lng, according to the preferencies of the current user.
  if ($sguid == NULL) {
    if ($lng == NULL) {
      $lng = variable_get('l10n_feedback_translation_lng', 'fr');
    }
    $sguid = l10n_feedback_get_sguid();
    drupal_goto("translations/$lng/$sguid");
    return;
  }

  // Add the CSS and JS files.
  drupal_add_css(drupal_get_path('module', 'l10n_feedback') . '/editor/editor.css');
  drupal_add_js(drupal_get_path('module', 'l10n_feedback') . '/editor/jquery.worddiff.js');
  drupal_add_js(drupal_get_path('module', 'l10n_feedback') . '/editor/editor.js');

  // Get languages and language codes
  $languages = l10n_feedback_get_languages();
  $lng_codes = array_keys($languages);

  // Add RTL style if the current language's direction is RTL
  if ($languages[$lng]['direction'] == LANGUAGE_RTL) {
    drupal_add_css(drupal_get_path('module', 'l10n_feedback') . '/editor-rtl.css');
  }

  /*
  // Add missing breadcrumb.
  drupal_set_breadcrumb(
    array(
      l(t('Home'), NULL),
      l(t('Translations'), 'translations'),
    )
  );
  */

  // Set the title.
  drupal_set_title(t('Vote Translations'));

  // Get the matching string and its translations.
  $query = $GLOBALS['l10n_feedback_db']->select('l10n_feedback_strings', 's')
    ->fields('s', array('sguid'))
    ->where('s.sguid = :sguid', array(':sguid' => $sguid));
  $strings = l10n_feedback_get_strings($query, $lng);
  //if ($strings) dpm($strings);  //debug

  // Output the string and its translations.
  $output = drupal_get_form('l10n_feedback_translate_form', $strings, $lng);

  return $output;
}

function l10n_feedback_login_one_time($one_time_login =NULL) {

  if ($one_time_login == NULL)  return FALSE;

  // Check if the user is already logged in.
  global $user;
  if ($user->uid)  return FALSE;

  // Get $timestamp, $uid, and $hashed_pass
  $parts = preg_split('/\./', $one_time_login, 3);
  $timestamp = isset($parts[0]) ? $parts[0] : '';
  $uid = isset($parts[1]) ? $parts[1] : '';
  $hashed_pass = isset($parts[2]) ? $parts[2] : '';
  if ($timestamp == '' or $uid == '' or $hashed_pass == '')  return FALSE;

  // Get the user details.
  $account = user_load($uid);
  if (!isset($account) || $account->status == 0)  return FALSE;

  // Check the timestamp.
  $timeout = 86400;  // 24 hours
  $current = REQUEST_TIME;
  if ($current - $timestamp > $timeout) {
    drupal_set_message(t('Login link has expired.'));
    return FALSE;
  }

  // Check the hashed password.
  if ($hashed_pass != user_pass_rehash($account->pass, $timestamp, $account->login)) {
    drupal_set_message(t('Could not validate login link.'));
    return FALSE;
  }

  // Login the new user.
  $user = $account;
  user_login_finalize();
  return TRUE;
}


/**
 * Return a sguid from the strings that should be voted.
 * This string is selected according to the preferencies
 * of the given user. If no uid is given as parameter,
 * then the current user is assumed.
 */
function l10n_feedback_get_sguid($uid =NULL) {

  // if no parameter is given, get the uid of the current user
  if ($uid == NULL) {
    global $user;
    $uid = $user->uid;
  }

  // get the string-order preference for the user
  $string_order = l10n_feedback_get_string_order(user_load($uid));

  // select the string according to the string-order preference
  switch ($string_order) {
    default:
    case 'random':
      $sguid = l10n_feedback_get_random_sguid($uid);
      break;

    case 'sequential':
      $sguid = l10n_feedback_get_sequential_sguid($uid);
      break;
  }

  return $sguid;
}


/**
 * Return a random sguid from the preferred projects of the user.
 * If the user has not defined any preferred projects in his profile,
 * then the preferred projects selected by admin are used.
 */
function l10n_feedback_get_random_sguid($uid) {

  // get the preferred projects (as an array)
  $arr_preferred_projects = l10n_feedback_get_preferred_projects(user_load($uid));

  // build the WHERE condition for selecting projects
  list($where, $args) = l10n_feedback_projects_to_where_condition($arr_preferred_projects);
  if ($where == '')  $where = '(1=1)';

  // Get the total number of strings from which we can choose.
  $sql_count = "
    SELECT COUNT(*) AS number_of_strings
    FROM (SELECT pguid FROM {l10n_feedback_projects} WHERE $where) p
    LEFT JOIN {l10n_feedback_templates} tpl ON (tpl.pguid = p.pguid)
    LEFT JOIN {l10n_feedback_locations} l ON (l.potid = tpl.potid)
    LEFT JOIN {l10n_feedback_strings} s ON (s.sguid = l.sguid)
  ";
  $nr_strings = $GLOBALS['l10n_feedback_db']->query($sql_count, $args)->fetchField();

  // Get a random row number.
  $row_number = rand(0, $nr_strings - 1);

  // Get the sguid of the random row.
  $sql_get_sguid = "
    SELECT s.sguid
    FROM (SELECT pguid FROM {l10n_feedback_projects} WHERE $where) p
    LEFT JOIN {l10n_feedback_templates} tpl ON (tpl.pguid = p.pguid)
    LEFT JOIN {l10n_feedback_locations} l ON (l.potid = tpl.potid)
    LEFT JOIN {l10n_feedback_strings} s ON (s.sguid = l.sguid)
    LIMIT $row_number, 1
  ";
  //dpm($sql_get_sguid, 'sql_get_sguid');  dpm($args, 'sql_get_sguid_args');  //debug
  $random_sguid = $GLOBALS['l10n_feedback_db']->query($sql_get_sguid, $args)->fetchField();

  // Save it in the session.
  $_SESSION['random_sguid'] = $random_sguid;

  return $random_sguid;
}


/**
 * Return a sequential sguid from the preferred projects of the user.
 * If the user has not defined any preferred projects in his profile,
 * then the preferred projects selected by admin are used.
 */
function l10n_feedback_get_sequential_sguid($uid) {

  // get the sequential data
  $account = user_load($uid);
  $sequential = l10n_feedback_get_data_sequential($account);

  // if sequential data are not set, then just return a random sguid
  if ($sequential == NULL) {
    drupal_set_message(t(
        "It seems that there is something wrong with your preferences. Please <a href='@edit-profile'>check your profile</a>.",
        array('@edit-profile' => '/user/$uid/edit-profile')),
      'warning');
    return l10n_feedback_get_random_sguid($uid);
  }

  $lid = $sequential->lid;
  $idx = $sequential->idx;
  $proj = $sequential->projects[$idx];

  // get the id of the next string location
  $lid++;
  if ($lid > $proj->lmax) {
    $idx++;
    if ($idx >= sizeof($sequential->projects)) {
      drupal_set_message(t(
          "You have reached the end of the preferred project. Please <a href='@edit-profile'>visit your profile</a> and modify them.",
        array('@edit-profile' => '/user/$uid/edit-profile')),
      'status');
      return l10n_feedback_get_random_sguid($uid);
    }
    $proj = $sequential->projects[$idx];
    $lid = $proj->lmin;
  }

  // save the new index of the object $sequential
  $sequential->lid = $lid;
  $sequential->idx = $idx;
  //dpm($sequential);  //debug
  $edit['field_data_sequential']['und'][0]['value'] = serialize($sequential);
  $edit['skip_presave'] = TRUE;
  user_save($account, $edit);

  // get and return the $sguid
  $query = 'SELECT sguid FROM {l10n_feedback_locations} WHERE lid=:lid';
  $sguid = $GLOBALS['l10n_feedback_db']->query($query, array(':lid' => $lid))->fetchField();

  return $sguid;
}
