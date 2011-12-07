#!/usr/bin/php
<?php
// Get the parameters (project, lng, source, file.po).
if ($argc != 5) {
  print "Usage: $argv[0] project lng source file.po\n\n";
  exit(1);
}
$script = $argv[0];
$project = $argv[1];
$lng = $argv[2];
$source = $argv[3];
$file = $argv[4];
print "$project $lng $source $file\n";  exit(0);  //debug

// Get the path of the file (relaive from source).
list($data_root, $path) = split("/$source/", $file);

// Prepare the queries that are used for processing strings.
include_once(dirname(__FILE__).'/prepare_queries.php');

// Set some variable that don't change.
$uid = '1';  //admin
$time = date('Y-m-d H:i:s');
$vcount = '0';

// Parse the given PO file.
include_once(dirname(__FILE__).'/POParser.php');
$parser = new POParser;
list($headers, $entries) = $parser->parse($file);
print_r($headers);  print_r($entries);  exit(0);  //debug

// Process each msgid entry.
foreach ($entries as $entry) {
  //print_r($entry);  continue;  //debug

  // Get $msgid and $s_hash
  $msgid = $entry['msgid'];
  if (isset($entry['msgid_plural'])) {
	$msgid .= "\0" . $entry['msgid_plural'];
  }
  $s_hash = sha1(trim($msgid));

  // Get the $sid of this string, if it is already stored.
  $get_string_id->execute();
  $row = $get_string_id->fetch();
  $sid = isset($row['sid']) ? isset($row['sid']) : null;

  // If such a string is not already stored, then insert it and get its id.
  if ($sid == null) {
	$insert_string->execute();
	$sid = $dbh->lastInsertId();
  }

  // Check that we have a valid $sid.
  if (!$sid) {
	print "Some problems with the string '$msgid'.\n";
	continue;
  }

  // Insert a location record.
  $insert_location->execute();
  $lid = $dbh->lastInsertId();

  // Insert the translation for this string.
  $msgstr = $entry['msgstr'];
  if (is_array($msgstr)) {
	$msgstr = implode("\0", $msgstr);
  }
  $t_hash = sha1(trim($msgstr));
  $insert_translation->execute();
  $tid = $dbh->lastInsertId();
}
?>