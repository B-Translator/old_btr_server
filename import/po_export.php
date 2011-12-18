#!/usr/bin/php
<?php
   // Check the number of parameters.
if ($argc < 4) {
  print "
Usage: $argv[0] origin project lng [file.po]
  origin  -- the origin of the project (ubuntu, GNOME, KDE, etc.)
  project -- the name of the project to be exported
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
$lng = $argv[3];
$filename = isset($argv[4]) ? $argv[4] : NULL;

// Create a DB variable for handling queries.
include_once(dirname(__FILE__).'/po_db_export.php');
$db = new PODB_Export;

// Get the id of the project.
$pid = $db->get_project_id($project, $origin);
if ($pid === null) {
  print "Project $origin/$project not found!";
  exit(1);
}

// Get the headers, strings and translations.
$headers = $db->get_file_headers($pid, $lng);
$strings = $db->get_strings($pid);
$translations = $db->get_best_translations($pid, $lng);

// Add translations to the corresponding strings.
foreach (array_keys($strings) as $sid) {
  $translation = isset($translations[$sid]) ? $translations[$sid]->translation : '';
  $strings[$sid]->translation = $translation;
}
print_r($strings);  return;  //debug

// Write entries to a PO file.
include_once(dirname(__FILE__).'/POWriter.php');
$writer = new POWriter;
if ($filename === NULL) {
  $output = $writer->write($headers, $strings);
  print(implode("\n", $output) . "\n");
}
else {
  $writer->write($headers, $strings, $filename);
}

?>