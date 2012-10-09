#!/usr/bin/php
<?php

function print_usage($argv)
{
  print "
Usage: $argv[0] (init|update|get) origin project lng file.tgz

  origin   -- the origin of the project (ubuntu, GNOME, KDE, etc.)
  project  -- the name of the project to be exported
  lng      -- language of translation (de, fr, sq, en_GB, etc.)
  file.tgz -- tgz archive of the snapshot of the project

The operation 'init' is used to insert into the DB the snapshot
for the first time. The operation 'update' to update it, and
'get' to retrive it from the DB.

Examples:
  $argv[0] init   LibreOffice sw fr LibreOffice-sw-fr.tgz
  $argv[0] update LibreOffice sw fr LibreOffice-sw-fr.tgz
  $argv[0] get    LibreOffice sw fr LibreOffice-sw-fr.tgz

";
  exit(1);
}

// Check the number of parameters.
if ($argc < 5)  print_usage($argv);

// Get the common parameters (operation, origin, project, lng, file)
$script = $argv[0];
$operation = $argv[1];
$origin = $argv[2];
$project = $argv[3];
$lng = $argv[4];
$file = $argv[5];
if ($operation != 'get') {
  print "$script $operation $origin $project $lng $file\n";
}

// Create a DB variable for handling queries.
include_once(dirname(__FILE__).'/db_snapshot.db.php');
$db = new DB_Snapshot;

// Perform the requested operation.
if ($operation == 'init') {
  $db->insert_snapshot($origin, $project, $lng, $file);
}
elseif ($operation == 'update') {
  $db->update_snapshot($origin, $project, $lng, $file);
}
elseif ($operation == 'get') {
  $db->get_snapshot($origin, $project, $lng, $file);
}
else {
  print_usage($argv);
}
?>