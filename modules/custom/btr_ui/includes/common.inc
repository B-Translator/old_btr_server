<?php
/**
 * @file
 * Functions that are common for all the pages.
 */

/**
 * Return the value of the field 'field_order_of_strings'
 * (which can be either 'random' or 'sequential'),
 * for the given user.
 * Return 'random' if the field has no value.
 */
function l10n_feedback_get_string_order($account) {

  $lang = 'und';
  if (isset($account->field_order_of_strings[$lang][0]['value'])) {
    $string_order = $account->field_order_of_strings[$lang][0]['value'];
  }
  else {
    $string_order = 'random';
  }

  return $string_order;
}


/**
 * Return the value of the field 'field_preferred_projects'
 * as an array of strings. If the user has not defined any
 * preferred projects on his profile/settings, then get the
 * preferred projects defined by admin on the config page.
 */
function l10n_feedback_get_preferred_projects($account) {

  $lang = 'und';
  $arr_preferred_projects = array();
  if ( isset($account->field_preferred_projects[$lang])
    and is_array($account->field_preferred_projects[$lang]) ) {

    // get the preferred projects from the user settings
    $field_preferred_projects = $account->field_preferred_projects[$lang];
    foreach ($field_preferred_projects as $project) {
      $arr_preferred_projects[] = $project['value'];
    }
  }
  else {
    // get the preferred projects from the site config
    $preferred_projects_txt = variable_get('btr_preferred_projects', '');
    $lines = preg_split('#\r\n|\r|\n#', $preferred_projects_txt);
    foreach ($lines as $line) {
      $line = trim($line);
      if ($line != '') {
        $arr_preferred_projects[] = $line;
      }
    }
  }

  if (isset($_SESSION['same_project']) && $_SESSION['same_project']) {
    $last_projects = btr_get_projects($_SESSION['sguid']);
    if (!empty($last_projects)) {
      $arr_preferred_projects = array_intersect($arr_preferred_projects, $last_projects);
      if (empty($arr_preferred_projects)) {
	$arr_preferred_projects = $last_projects;
      }
    }
  }

  return $arr_preferred_projects;
}


/**
 * Return the value of the field 'field_auxiliary_languages' as an array.
 */
function l10n_feedback_get_auxiliary_languages($account) {

  $lang = 'und';
  $arr_auxiliary_languages = array();
  if ( isset($account->field_auxiliary_languages[$lang])
    and is_array($account->field_auxiliary_languages[$lang]) ) {

    // get the preferred projects from the user settings
    $field_auxiliary_languages = $account->field_auxiliary_languages[$lang];
    foreach ($field_auxiliary_languages as $language) {
      $arr_auxiliary_languages[] = $language['value'];
    }
  }

  return $arr_auxiliary_languages;
}


/**
 * Get the sequential data from the field 'field_data_sequential'.
 * Return NULL if no such data is found.
 */
function l10n_feedback_get_data_sequential($account) {

  $lang = 'und';
  if (isset($account->field_data_sequential[$lang][0]['value'])) {
    $sequential = unserialize($account->field_data_sequential[$lang][0]['value']);
  }
  else {
    $sequential = NULL;
  }

  return $sequential;
}

/**
 * From the given (possibly long) string, returns a short string
 * of the given length (that can be suitable for title, subject, etc.)
 */
function l10n_feedback_shorten($string, $length) {
  $str = strip_tags(str_replace("\n", ' ', $string));
  if (strlen($str) > $length) {
    $str = substr($str, 0, strrpos(substr($str, 0, $length - 3), ' '));
    $str .= '...';
  }
  $str = utf8_decode($str);
  $str = htmlentities($str);
  return $str;
}
