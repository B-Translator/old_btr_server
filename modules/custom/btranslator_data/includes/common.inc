<?php
/**
 * @file
 * Functions that are common for all the pages.
 */

/**
 * Returns an array of languages and their details.
 */
function btranslator_data_get_languages() {

  $arr_langs = array(
    'en' => array(
      'code' => 'en',
      'name' => 'English',
      'encoding' => 'latin1',
      'direction' => LANGUAGE_LTR,
      'plurals' => 2,
    ),
    'fr' => array(
      'code' => 'fr',
      'name' => 'French',
      'encoding' => 'latin1',
      'direction' => LANGUAGE_LTR,
      'plurals' => 2,
    ),
    'sq' => array(
      'code' => 'sq',
      'name' => 'Albanian',
      'encoding' => 'latin1',
      'direction' => LANGUAGE_LTR,
      'plurals' => 2,
    ),
  );

  return $arr_langs;
}


/**
 * Return the value of the field 'field_order_of_strings'
 * (which can be either 'random' or 'sequential'),
 * for the given user.
 * Return 'random' if the field has no value.
 */
function btranslator_data_get_string_order($account) {

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
 * the preferred projects defined by admin on the config page.
 */
function btranslator_data_get_preferred_projects($account) {

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
    $last_project = btranslator_data_get_last_project();
    if (!empty($last_project)) {
      $arr_preferred_projects = array_intersect($arr_preferred_projects, $last_project);
      if (empty($arr_preferred_projects)) {
	$arr_preferred_projects = $last_project;
      }
    }
  }

  return $arr_preferred_projects;
}

/**
 * Return the project(s) of the last sguid
 * as an array.
 */
function btranslator_data_get_last_project() {
  if ( !isset($_SESSION['sguid']))  return array();

  $args = array(':last_sguid' => $_SESSION['sguid']);
  $get_projects = "
      SELECT p.origin, p.project
      FROM {btr_locations} l
      LEFT JOIN {btr_templates} tpl ON (tpl.potid = l.potid)
      LEFT JOIN {btr_projects} p ON (p.pguid = tpl.pguid)
      WHERE l.sguid = :last_sguid
  ";
  $db = $GLOBALS['btr_db'];
  $result = $db->query($get_projects, $args)->fetchAll();
  $last_projects = array();
  foreach ($result as $proj) {
    $last_projects[] = $proj->origin . '/' . $proj->project;
  }

  return $last_projects;
}

/**
 * Return the value of the field 'field_auxiliary_languages' as an array.
 */
function btranslator_data_get_auxiliary_languages($account) {

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
function btranslator_data_get_data_sequential($account) {

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
 * Return an array of a WHERE condition for SQL queries, and arguments
 * that are used in it. These can be used in a db_query() for selecting
 * all the projects specified in the given parameter.
 *
 * The parameter is an array of project specifications, where each items is
 * in the form of either 'origin/project', or in the form of 'origin' (which
 * includes all the projects from this origin).
 */
function btranslator_data_projects_to_where_condition($arr_projects) {

  $arr_conditions = array();
  $arguments = array();
  $arg_origin  = ':origin01';
  $arg_project = ':project01';

  foreach ($arr_projects as $proj) {
    $parts = preg_split('#/#', $proj, 2);
    if (sizeof($parts)==2) {
      list($origin, $project) = $parts;
      $arguments[$arg_origin] = $origin;
      $arguments[$arg_project] = $project;
      $arr_conditions[] = "(origin=$arg_origin AND project=$arg_project)";
      $arg_origin++;  $arg_project++;
    }
    else {
      $origin = $parts[0];
      $arguments[$arg_origin] = $origin;
      $arr_conditions[] = "(origin=$arg_origin)";
      $arg_origin++;
    }
  }
  $where_condition = implode(' OR ', $arr_conditions);

  return array($where_condition, $arguments);
}

/**
 * From the given (possibly long) string, returns a short string
 * of the given length (that can be suitable for title, subject, etc.)
 */
function btranslator_data_shorten($string, $length) {
  $str = strip_tags(str_replace("\n", ' ', $string));
  if (strlen($str) > $length) {
    $str = substr($str, 0, strrpos(substr($str, 0, $length - 3), ' '));
    $str .= '...';
  }
  $str = utf8_decode($str);
  $str = htmlentities($str);
  return $str;
}

/**
 * Return the sender of the email notifications
 * (which is always the same, as defined on smtp variables)
 */
function btranslator_data_get_email_sender() {
  $smtp_from = variable_get('smtp_from');
  $smtp_fromname = variable_get('smtp_fromname');
  $sender = "$smtp_fromname <$smtp_from>";
}