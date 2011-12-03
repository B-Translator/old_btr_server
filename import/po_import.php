#!/usr/bin/php
<?php
// Get the parameters (project, lng, file.po).
if ($argc != 4) {
  print "Usage: $argv[0] project lng file.po\n";
  exit(1);
}
$project = $argv[1];
$lng = $argv[2];
$filename = $argv[3];
//print "$project $lng $filename\n";  exit(0);  //debug

// Get the POParser class.
include_once(dirname(__FILE__).'/POParser.php');

// Get the DB parameters.
@include_once(dirname(__FILE__).'/settings.php');
$db = $databases['default']['default'];
$dbdriver = $db['driver'];
$dbhost = $db['host'];
$dbname = $db['database'];  $dbname = 'l10nsq_test';  //debug
$dbuser = $db['username'];
$dbpass = $db['password'];

// Create a persistent DB connection.
$DSN = "$dbdriver:host=$dbhost;dbname=$dbname";
//print "$DSN\n";  exit(0);  //debug
$dbh = new PDO($DSN, $dbuser, $dbpass);

// Prepare the query for getting the id of a string (if it is already stored).
$get_string_id = $dbh->prepare("SELECT sid FROM l10n_suggestions_strings WHERE hash = :hash");
$get_string_id->bindParam(':hash', $s_hash);

// Prepare the query for inserting a string into the table of strings.
$insert_string = $dbh->prepare("
  INSERT INTO l10n_suggestions_strings
     (string, hash, uid_entered, time_entered)
  VALUES
     (:string, :hash, :uid, :time)
");
$insert_string->bindParam(':string', $msgid);
$insert_string->bindParam(':hash', $s_hash);
$insert_string->bindParam(':uid', $uid);
$insert_string->bindParam(':time', $time);

// Prepare the query for inserting a location into the table of locations.
$insert_location = $dbh->prepare("
  INSERT INTO l10n_suggestions_locations
     (sid, projectname)
  VALUES
     (:sid, :project)
");
$insert_location->bindParam(':sid', $sid);
$insert_location->bindParam(':project', $project);

// Prepare the query for inserting a translation into the table of translations.
$insert_translation = $dbh->prepare("
  INSERT INTO l10n_suggestions_translations
     (sid, lng, translation, hash, vcount, uid_entered, time_entered)
  VALUES
     (:sid, :lng, :translation, :hash, :vcount, :uid, :time)
");
$insert_translation->bindParam(':sid', $sid);
$insert_translation->bindParam(':lng', $lng);
$insert_translation->bindParam(':translation', $msgstr);
$insert_translation->bindParam(':vcount', $vcount);
$insert_translation->bindParam(':hash', $t_hash);
$insert_translation->bindParam(':uid', $uid);
$insert_translation->bindParam(':time', $time);

// Set some variable that don't change.
$uid = '1';  //admin
$time = date('Y-m-d H:i:s');
$vcount = '0';

// Parse the given PO file.
$parser = new POParser;
list($headers, $entries) = $parser->parse($filename);
//print_r($headers);  print_r($entries);  exit(0);  //debug

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