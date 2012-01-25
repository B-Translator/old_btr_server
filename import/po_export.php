#!/usr/bin/php
<?php
   // Check the number of parameters.
if ($argc < 4) {
  print "
Usage: $argv[0] origin project lng dir
  origin  -- the origin of the project (ubuntu, GNOME, KDE, etc.)
  project -- the name of the project to be exported
  lng     -- translation to be exported (de, fr, sq, en_GB, etc.)
  dir     -- directory where to put the exported file

Example:
  $argv[0] KDE kturtle fr test/kturtle_fr.po

";
  exit(1);
}

// Get the parameters (project, lng, origin, file.po).
$script = $argv[0];
$origin = $argv[1];
$project = $argv[2];
$lng = $argv[3];
$dir = $argv[4];

// Create a DB variable for handling queries.
include_once(dirname(__FILE__).'/po_export.db.php');
$db = new DB_PO_Export;

// Get the id of the project.
$arr_potid = $db->get_potid_list($origin, $project);
if (empty($arr_potid)) {
  print "Project $origin/$project has no data!";
  exit(1);
}

foreach ($arr_potid as $potid)
  {
    // Get the headers, strings and translations.
    list($filename, $headers, $comments) = $db->get_file_headers($potid, $lng);
    $strings = $db->get_strings($potid);
    $translations = $db->get_best_translations($potid, $lng);

    // Add translations to the corresponding strings.
    foreach (array_keys($strings) as $sguid) {
      $translation = isset($translations[$sguid]) ? $translations[$sguid]->translation : '';
      $strings[$sguid]->translation = $translation;
    }
    //print_r($strings);  exit(0);  //debug

    // Write entries to a PO file.
    include_once(dirname(__FILE__).'/POWriter.php');
    $writer = new POWriter;
    $file = "$dir/$filename";
    exec('mkdir -p ' . dirname($file));
    $writer->write($headers, $comments, $strings, $file);
  }
?>