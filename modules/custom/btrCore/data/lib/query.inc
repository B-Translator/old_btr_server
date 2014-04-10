<?php
/**
 * Run a query on the B-Translator database and return the result.
 */
function btr_query($sql, $args) {
  return $GLOBALS['btr_db']->query($sql, $args);
}
