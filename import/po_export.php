#!/usr/bin/php
<?php
   // Check the number of parameters.
if ($argc < 5) {
  print "
Usage: $argv[0] origin project tplname lng [file.po]
  origin  -- the origin of the project (ubuntu, GNOME, KDE, etc.)
  project -- the name of the project to be exported
  tplname -- The name of the PO template.
  lng     -- translation to be exported (de, fr, sq, en_GB, etc.)
  file.po -- output file (stdout if not given)

Example:
  $argv[0] KDE kturtle fr test/kturtle_fr.po

";
  exit(1);
}

// Get the parameters (project, lng, origin, file.po).
$script = $argv[0];
$origin = $argv[1];
$project = $argv[2];
$tplname = $argv[3];
$lng = $argv[4];
$filename = isset($argv[5]) ? $argv[5] : NULL;

// Create a DB variable for handling queries.
include_once(dirname(__FILE__).'/po_export.db.php');
$db = new DB_PO_Export;

// Get the id of the template.
$potid = $db->get_template_potid($origin, $project, $tplname);
if ($potid === null) {
  print "Template $origin/$project/$tplname not found!";
}

// Get the headers, strings and translations.
list($headers, $comments) = $db->get_file_headers($potid, $lng);
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
if ($filename === NULL) {
  $output = $writer->write($headers, $comments, $strings);
  print(implode("\n", $output) . "\n");
}
else {
  $writer->write($headers, $comments, $strings, $filename);
}
?>