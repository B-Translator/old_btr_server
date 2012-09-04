<?php
/**
 * @file
 *   Functions specific to the menu path: translations/vote .
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

  if ($lng == NULL) {
    $lng = l10n_feedback_get_translation_lng();
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

  // If no $sguid is given as parameter, get the sguid of a string,
  // according to the preferencies of the current user.
  if ($sguid == NULL) {
    $sguid = l10n_feedback_get_sguid();
  }

  // Get the matching string and its translations.
  $query = db_select('l10n_feedback_strings', 's')
    ->fields('s', array('sguid'))
    ->where('s.sguid = :sguid', array(':sguid' => $sguid));
  $strings = l10n_feedback_get_strings($query, $lng);
  //if ($strings) dpm($strings);  //debug

  // Output the string and its translations.
  $output = drupal_get_form('l10n_feedback_translate_form', $strings, $lng);

  return $output;
}

function l10n_feedback_login_one_time($one_time_login =NULL)
{
  if ($one_time_login == NULL)  return false;

  // Check if the user is already logged in.
  global $user;
  if ($user->uid)  return false;

  // Get $timestamp, $uid, and $hashed_pass
  $parts = preg_split('/\./', $one_time_login, 3);
  $timestamp = isset($parts[0]) ? $parts[0] : '';
  $uid = isset($parts[1]) ? $parts[1] : '';
  $hashed_pass = isset($parts[2]) ? $parts[2] : '';
  if ($timestamp == '' or $uid == '' or $hashed_pass == '')  return false;

  // Get the user details.
  $account = user_load($uid);
  if (!isset($account) || $account->status == 0)  return false;

  // Check the timestamp.
  $timeout = 86400;  // 24 hours
  $current = REQUEST_TIME;
  if ($current - $timestamp > $timeout) {
    drupal_set_message(t('Login link has expired.'));
    return false;
  }

  // Check the hashed password.
  if ($hashed_pass != user_pass_rehash($account->pass, $timestamp, $account->login)) {
    drupal_set_message(t('Could not validate login link.'));
    return false;
  }

  // Login the new user.
  $user = $account;
  user_login_finalize();
  return true;
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
  $string_order = l10n_feedback_get_string_order($uid);

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
 * Return the value of the field 'field_order_of_strings'
 * (which can be either 'random' or 'sequential'),
 * for the given user.
 * Return 'random' if the field has no value.
 */
function l10n_feedback_get_string_order($uid) {

  $account = user_load($uid);
  $field_order_of_strings = field_get_items('user', $account, 'field_order_of_strings');

  if (isset($field_order_of_strings[0]['value'])) {
    $string_order = $field_order_of_strings[0]['value'];
  } else {
    $string_order = 'random';
  }

  return $string_order;
}


/**
 * Return a random sguid from the preferred projects of the user.
 * If the user has not defined any preferred projects in his profile,
 * then the preferred projects selected by admin are used.
 */
function l10n_feedback_get_random_sguid($uid) {

  // get the preferred projects (as an array)
  $arr_preferred_projects = l10n_feedback_get_preferred_projects($uid);

  // build the WHERE condition for selecting projects
  $arr_conditions = array();
  foreach ($arr_preferred_projects as $preferred_project) {
    $arr_parts = preg_split('#/#', $preferred_project, 2);
    if (isset($arr_parts[1])) {
      $origin = $arr_parts[0];
      $project = $arr_parts[1];
      $arr_conditions[] = "(origin='$origin' AND project='$project')";
    }
    else {
      $origin = $arr_parts[0];
      $arr_conditions[] = "(origin='$origin')";
    }
  }
  $where = implode(' OR ', $arr_conditions);
  if ($where == '')  $where = '(1=1)';
  // $where = "(origin='test')";

  // Get the total number of strings from which we can choose.
  $sql_count = "
    SELECT COUNT(*) AS number_of_strings
    FROM (SELECT pguid FROM l10n_feedback_projects WHERE $where) p
    LEFT JOIN l10n_feedback_templates tpl ON (tpl.pguid = p.pguid)
    LEFT JOIN l10n_feedback_locations l ON (l.potid = tpl.potid)
    LEFT JOIN l10n_feedback_strings s ON (s.sguid = l.sguid)
  ";
  $nr_strings = db_query($sql_count)->fetchField();

  // Get a random row number.
  $row_number = rand(0, $nr_strings - 1);

  // Get the sguid of the random row.
  $sql_get_sguid = "
    SELECT s.sguid
    FROM (SELECT pguid FROM l10n_feedback_projects WHERE $where) p
    LEFT JOIN l10n_feedback_templates tpl ON (tpl.pguid = p.pguid)
    LEFT JOIN l10n_feedback_locations l ON (l.potid = tpl.potid)
    LEFT JOIN l10n_feedback_strings s ON (s.sguid = l.sguid)
    LIMIT $row_number, 1
  ";
  $random_sguid = db_query($sql_get_sguid)->fetchField();

  // Save it in the session.
  $_SESSION['random_sguid'] = $random_sguid;

  return $random_sguid;
}


/**
 * Return the value of the field 'field_preferred_projects'
 * as an array of strings. If the user has not defined any
 * preferred projects on his profile/settings, then get the
 * the preferred projects defined by admin on the config page.
 */
function l10n_feedback_get_preferred_projects($uid) {

  // get the preferred projects from the user settings
  $account = user_load($uid);
  $field_preferred_projects = field_get_items('user', $account, 'field_preferred_projects');

  $arr_preferred_projects = array();
  if (is_array($field_preferred_projects) and sizeof($field_preferred_projects) > 0) {
    foreach ($field_preferred_projects as $project) {
      $arr_preferred_projects[] = $project['safe_value'];
    }
  } else {
    // get the preferred projects from the site config
    $preferred_projects_txt = variable_get('l10n_feedback_preferred_projects', '');
    $lines = preg_split('#\r\n|\r|\n#', $preferred_projects_txt);
    foreach ($lines as $line) {
      $line = trim($line);
      if ($line != '') {
        $arr_preferred_projects[] = $line;
      }
    }
  }

  return $arr_preferred_projects;
}


/**
 * Return a sequential sguid from the preferred projects of the user.
 * If the user has not defined any preferred projects in his profile,
 * then the preferred projects selected by admin are used.
 */
function l10n_feedback_get_sequential_sguid($uid) {

  // TODO

  $arr_preferred_projects = l10n_feedback_get_preferred_projects($uid);

  return $sguid;
}
?>