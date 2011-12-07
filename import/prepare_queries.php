<?php
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

?>