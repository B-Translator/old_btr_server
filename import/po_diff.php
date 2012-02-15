#!/usr/bin/php
<?php

function print_usage($argv)
{
  print "
Usage: $argv[0] add  origin project lng file.ediff [comment [user_id]]
       $argv[0] list origin project lng
       $argv[0] get  origin project lng number [file.ediff]

  origin     -- the origin of the project (ubuntu, GNOME, KDE, etc.)
  project    -- the name of the project to be exported
  lng        -- language of translation (de, fr, sq, en_GB, etc.)
  file.ediff -- file in ediff (embedded diff) format
  comment    -- optional comment about the ediff file that is being added
  user_id    -- optional (drupal) uid of the user that is adding the ediff
  number     -- the number of ediff that is being retrieved

Examples:
  $argv[0] add LibreOffice sw fr LibreOffice-sw-fr.ediff
  $argv[0] list LibreOffice sw fr
  $argv[0] get LibreOffice sw fr 5 > LibO/fr/sw_5.ediff

";
  exit(1);
}

// Check the number of parameters.
if ($argc < 4)  print_usage($argv);

// Get the common parameters (operation, origin, project, lng)
$script = $argv[0];
$operation = $argv[1];
$origin = $argv[2];
$project = $argv[3];
$lng = $argv[4];

// Get the additional parameters for each operation.
if ($operation == 'add') {
  $file = isset($argv[5]) ? $argv[5] : null;
  if ($file == null)  print_usage($argv);
  $comment = isset($argv[6]) ? $argv[6] : null;
  $user_id = isset($argv[7]) ? $argv[7] : null;
}
else if ($operation == 'list') {
}
else if ($operation == 'get') {
  $number = isset($argv[5]) ? $argv[5] : null;
  if ($number == null)  print_usage($argv);
  $file = isset($argv[6]) ? $argv[6] : null;
}
else {
  print_usage($argv);
}

// Create a DB variable for handling queries.
include_once(dirname(__FILE__).'/po_diff.db.php');
$db = new DB_PO_Diff;

// Perform the requested operation.
if ($operation == 'add')
  // Insert the content of a diff file into the DB.
  {
    $db->insert_diff($origin, $project, $lng, $file, $comment, $user_id);
  }
else if ($operation == 'list')
  // Print a list of diffs that are in the DB.
  {
    $diff_list = $db->get_diff_list($origin, $project, $lng);
    foreach ($diff_list as $diff) {
      $diff_line = implode("\t", $diff);
      print $diff_line . "\n";
    }
  }
else if ($operation == 'get')
  // Retrive a specific diff from the DB.
  {
    $diff = $db->get_diff($origin, $project, $lng, $number);
    if ($file == null) {
      print $diff;
    }
    else {
      file_put_contents($file, $diff);
    }
  }
?>