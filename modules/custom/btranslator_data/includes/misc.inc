<?php

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
 * Unpacks a string as retrieved from the database.
 *
 * Creates an array out of the string. If it was a single string, the array
 * will have one item. If the string was a plural string, the array will have
 * as many items as the language requires (two for source strings).
 *
 * @param $string
 *   The string with optional separation markers (NULL bytes)
 * @return
 *   An array of strings with one element for each plural form in case of
 *   a plural string, or one element in case of a regular string. This
 *  is called a $textarray elsewhere.
 */
function btr_unpack_string($string) {
  return explode("\0", $string);
}

/**
 * Packs a string for storage in the database.
 *
 * @param $string
 *   An array of strings.
 * @return
 *   A packed string with NULL bytes separating each string.
 */
function btr_pack_string($strings) {
  if (is_array($strings)) {
    return implode("\0", $strings);
  }
  else {
    return $strings;
  }
}

function btr_query($sql, $args) {
  return $GLOBALS['btr_db']->query($sql, $args);
}

/**
 * Queue actions for batch execution.
 * @param $queue_name
 *   Name of the queue.
 * @param $items
 *   Array of items to be queued. Each item is an associative array
 *   that provides data for the batch process.
 */
function btr_queue($queue_name, $items) {
  $queue = DrupalQueue::get($queue_name);
  $queue->createQueue();  // There is no harm in trying to recreate existing.
  foreach ($items as $item) {
    $queue->createItem((object)$item);
  }
}

/**
 * Queue notifications for sending by email.
 *
 * @param $notifications
 *   Array of notification items. Each item is an associative array
 *   containing at least 'type' and 'recipient' (email), and optionally
 *   other parameters that can be used on the notification template
 *   (depending on the type of the notification).
 */
function btr_queue_notifications($notifications) {
  $queue = DrupalQueue::get('notifications');
  $queue->createQueue();  // There is no harm in trying to recreate existing.
  foreach ($notifications as $item) {
    $queue->createItem((object)$item);
  }
}


/**
 * From the given (possibly long) string, returns a short string
 * of the given length (that can be suitable for title, subject, etc.)
 */
function btr_data_shorten($string, $length) {
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
 * For each project on the list, get the min and max location ids
 * and return them in the object $sequential.
 *
 * The data in this object makes it possible for a user to visit
 * the strings of his preferred projects sequentially (in the same
 * order that they appear on the PO file), rather than randomly.
 */
function btr_get_sequential_data($arr_projects) {
  list($where_condition, $args) = _btr_projects_to_where_condition($arr_projects);
  if ($where_condition == '') {
    $sequential = NULL;
  }
  else {
    $get_all_min_and_max_locations = "
      SELECT min(l.lid) AS lmin, max(l.lid) AS lmax
      FROM {btr_locations} l
      RIGHT JOIN {btr_templates} t ON (l.potid = t.potid)
      RIGHT JOIN {btr_projects} p ON (t.pguid = p.pguid)
      WHERE $where_condition
      GROUP BY p.project
    ";
    $result = $GLOBALS['btr_db']->query($get_all_min_and_max_locations, $args);
    $sequential->projects = $result->fetchAll();
    $sequential->idx = 0;
    $sequential->lid = $sequential->projects[0]->lmin;
  }
  return $sequential;
}


/**
 * Return an array of a WHERE condition for SQL queries, and arguments
 * that are used in it. These can be used in a db_query() for selecting
 * all the projects specified in the given parameter.
 *
 * The parameter is an array of project specifications, where each item is
 * in the form of either 'origin/project', or in the form of 'origin' (which
 * includes all the projects from this origin).
 */
function _btr_projects_to_where_condition($arr_projects) {

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
 * Return an array of the projects that contain the given string.
 * Each item of the array is of the form 'origin/project'.
 */
function btr_get_projects($sguid) {
  if (empty($sguid))  return array();

  $args = array(':sguid' => $sguid);
  $get_projects = "
      SELECT p.origin, p.project
      FROM {btr_locations} l
      LEFT JOIN {btr_templates} tpl ON (tpl.potid = l.potid)
      LEFT JOIN {btr_projects} p ON (p.pguid = tpl.pguid)
      WHERE l.sguid = :sguid
  ";
  $db = $GLOBALS['btr_db'];
  $result = $db->query($get_projects, $args)->fetchAll();
  $projects = array();
  foreach ($result as $proj) {
    $projects[] = $proj->origin . '/' . $proj->project;
  }

  return $projects;
}
