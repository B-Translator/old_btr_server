<?php
/**
 * @file
 * Database functions: db_query(), db_select(), db_insert(), etc.
 */

namespace BTranslator;
use \Database;

/**
 * Get the propper connection for the B-Translator database.
 */
function get_db_connection(&$options) {
  if (empty($options['target'])) {
    $options['target'] = 'default';
  }
  return Database::getConnection($options['target'], BTR_DB);
}

/**
 * Run a query on the B-Translator database and return the result.
 */
function db_query($query, array $args =array(), array $options =array()) {
  $db = get_db_connection($options);
  return $db->query($query, $args, $options);
}


function db_query_range($query, $from, $count, array $args =array(), array $options =array()) {
  $db = get_db_connection($options);
  return $db->queryRange($query, $from, $count, $args, $options);
}

function db_select($table, $alias =NULL, array $options =array()) {
  $db = get_db_connection($options);
  return $db->select($table, $alias, $options);
}

function db_insert($table, array $options =array()) {
  $db = get_db_connection($options);
  return $db->insert($table, $options);
}

function db_update($table, array $options =array()) {
  $db = get_db_connection($options);
  return $db->update($table, $options);
}

function db_delete($table, array $options =array()) {
  $db = get_db_connection($options);
  return $db->delete($table, $options);
}

function db_query_temporary($query, array $args =array(), array $options =array()) {
  $db = get_db_connection($options);
  return $db->queryTemporary($query, $args, $options);
}
