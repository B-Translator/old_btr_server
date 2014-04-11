<?php
/**
 * Run a query on the B-Translator database and return the result.
 */
function btr_query($query, array $args =array(), array $options =array()) {
  $db = _btr_get_db_connection($options);
  return $db->query($query, $args, $options);
}

/**
 * Get the propper connection for the B-Translator database.
 */
function _btr_get_db_connection(&$options) {
  if (empty($options['target'])) {
    $options['target'] = 'default';
  }
  return Database::getConnection($options['target'], BTR_DB);
}

function btr_query_range($query, $from, $count, array $args =array(), array $options =array()) {
  $db = _btr_get_db_connection($options);
  return $db->queryRange($query, $from, $count, $args, $options);
}

function btr_select($table, $alias =NULL, array $options =array()) {
  $db = _btr_get_db_connection($options);
  return $db->select($table, $alias, $options);
}

function btr_insert($table, array $options =array()) {
  $db = _btr_get_db_connection($options);
  return $db->insert($table, $options);
}

function btr_update($table, array $options =array()) {
  $db = _btr_get_db_connection($options);
  return $db->update($table, $options);
}

function btr_delete($table, array $options =array()) {
  $db = _btr_get_db_connection($options);
  return $db->delete($table, $options);
}
