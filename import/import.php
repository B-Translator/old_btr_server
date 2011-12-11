#!/usr/bin/php
<?php

function usage()
{
  global $argv;
  print "
Usage: $argv[0] [init|done]
  init -- Initializes the import process.
  done -- Ends up the import process.

";
  exit(1);
}

// Get the parameters.
if ($argc != 2) {
  usage();
}
$action = $argv[1];

// Create a DB variable for handling queries.
include_once(dirname(__FILE__).'/po_db.php');
$db = new PODB;

switch ($action)
  {
  case 'init':
    // Add the column imported.
    $sql = "ALTER TABLE l10n_suggestions_files ADD COLUMN imported tinyint(1) DEFAULT 0";
    $db->exec($sql);
    break;

  case 'done':
    // Drop the column imported.
    $sql = "ALTER TABLE l10n_suggestions_files DROP COLUMN imported";
    $db->exec($sql);
    // Update the string count (in how many projects a string occurs).
    $sql = "UPDATE l10n_suggestions_strings s
            SET s.count = (SELECT count(*) FROM l10n_suggestions_locations l WHERE l.sid = s.sid)";
    $db->exec($sql);
    break;

  default:
    usage();
    break;
  }
?>