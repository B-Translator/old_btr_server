#!/usr/bin/php
<?php
   // Check the number of parameters.
if ($argc != 5) {
  print "
Usage: $argv[0] origin project lng file.po
  origin  -- the origin of the PO file (ubuntu, GNOME, KDE, etc.)
  project -- the name of the project that is being imported.
  lng     -- the language of translation (de, fr, sq, en_GB, etc.).
  file.po -- the PO file to be imported.

Example:
  $argv[0] KDE kturtle fr test/kturtle.po

";
  exit(1);
}

// Get the parameters (project, lng, origin, file.po).
$script = $argv[0];
$origin = $argv[1];
$project = $argv[2];
$lng = $argv[3];
$filename = $argv[4];
//log
print "$script $project $lng $origin $filename\n";

// Get the path of the file relative from origin.
$parts = split("/$origin/", $filename);
$file = isset($parts[1]) ? $parts[1] : '';

// Create a DB variable for handling queries.
include_once(dirname(__FILE__).'/po_db_import.php');
$db = new PODB_Import;

// Parse the given PO file.
include_once(dirname(__FILE__).'/POParser.php');
$parser = new POParser;
$entries = $parser->parse($filename);
/*
// parse the headers from the msgstr of the first (empty) entry
$headers = array();
if ($entries[0]['msgid'] == '') {
  $headers = $parser->parse_headers($entries[0]['msgstr']);
}
*/
//print_r($headers);  print_r($entries);  exit(0);  //debug

// Get the id of the project.
$pid = $db->get_project_id($project, $origin);
if ($pid === null) {
  $pid = $db->insert_project($project, $origin);
}

// Check whether the file already exists.
// If not found, insert a new one, else update the existing one.
$headers = ($entries[0]['msgid'] == '') ? $entries[0]['msgstr'] : '';
$fid = $db->get_file_id($pid, $lng, $file);
if ($fid === null) {
  $fid = $db->insert_file($pid, $lng, $file, $headers);
}
else {
  $db->update_file($pid, $lng, $file, $headers);
}

// If the file has been already imported, then exit.
if ($db->file_is_imported($fid)) {
  print "...Skiping, already imported.\n";
  exit(0);
};

// Process each gettext entry.
foreach ($entries as $entry)
  {
    //print_r($entry);  continue;  //debug

    // Get the string and context of this entry.
    $string = $entry['msgid'];
    if (isset($entry['msgid_plural'])) {
      $string .= "\0" . $entry['msgid_plural'];
    }
    // Don't add the header entry as a translatable string.
    if ($string == '')  continue;
    // Don't add strings like 'translator-credits' etc. as translatable strings.
    if (preg_match('/.*translator.*credit.*/', $string))  continue;

    // Get the $sguid of this string. If not found, insert a new string and get its id.
    $context = isset($entry['msgctxt']) ? $entry['msgctxt'] : '';
    $sguid = $db->get_string_id($string, $context);
    if ($sguid === null) {
      $sguid = $db->insert_string($string, $context);
    }

    // Insert a location record, by replacing any existing one.
    $lid = $db->get_location_id($pid, $sguid);
    if ($lid === null) {
      $lid = $db->insert_location($pid, $sguid, $entry);
    }

    // Insert the translation for this string.
    $translation = is_array($entry['msgstr']) ? implode("\0", $entry['msgstr']) : $entry['msgstr'];
    if (trim($translation) != '')
      {
	// Check first that it does not exist already.
	$tguid = $db->get_translation_id($sguid, $lng, $translation);
	if ($tguid == null) {
	  $tguid = $db->insert_translation($sguid, $lng, $translation);
	}
    }
  }

// Mark the file as imported.
$db->set_file_imported($fid);
?>