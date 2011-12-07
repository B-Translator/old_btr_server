#!/usr/bin/php
<?php
   // Check the number of parameters.
if ($argc != 5) {
  print "
Usage: $argv[0] project lng source file.po
  project -- the name of the project that is being imported.
  lng     -- the language of translation (de, fr, sq, en_GB, etc.).
  source  -- the source of the PO file (ubuntu, GNOME, KDE, etc.)
  file.po -- the PO file to be imported.

Example:
  $argv[0] kturtle fr KDE test/kturtle.po

";
  exit(1);
}

// Get the parameters (project, lng, source, file.po).
$script = $argv[0];
$project = $argv[1];
$lng = $argv[2];
$source = $argv[3];
$file = $argv[4];
print "$script $project $lng $source $file\n";  //log

// Get the path of the file (relative from source).
$parts = split("/$source/", $file);
$path = isset($parts[1]) ? $parts[1] : '';

// Create a DB variable for handling queries.
include_once(dirname(__FILE__).'/po_db.php');
$db = new PODB;

// Parse the given PO file.
include_once(dirname(__FILE__).'/POParser.php');
$parser = new POParser;
list($headers, $entries) = $parser->parse($file);
//print_r($headers);  print_r($entries);  exit(0);  //debug

// Process each gettext entry.
foreach ($entries as $entry) {
  //print_r($entry);  continue;  //debug

  // Get the string of this entry
  $string = $entry['msgid'];
  if (isset($entry['msgid_plural'])) {
    $string .= "\0" . $entry['msgid_plural'];
  }

  // Get the $sid of this string.
  $sid = $db->get_string_id($string);
  if ($sid === null) {
    $sid = $db->insert_string($string);
  }
  if (!$sid) {
    print "Some problems with the string '$string'.\n";
    continue;
  }

  // Insert a location record.
  $lid = $db->insert_location($sid, $project);

  // Insert the translation for this string.
  $translation = is_array($entry['msgstr']) ? implode("\0", $entry['msgstr']) : $entry['msgstr'];
  $tid = $db->insert_translation($sid, $lng, $translation);
}
?>