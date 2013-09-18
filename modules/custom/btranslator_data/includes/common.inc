<?php
/**
 * @file
 * Functions that are common for all the pages.
 */

/**
 * Returns an array of languages and their details.
 */
function btr_get_languages() {

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