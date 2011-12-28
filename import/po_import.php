#!/usr/bin/php
<?php
   /**
    * 'po_import.php' imports a new PO (translation) file, if such a file
    * does not exist. It assumes that the POT file of the project has
    * already been imported, otherwise it will quit without doing anything.
    * Along with the file, it also inserts the translations for the
    * corresponding strings, when such translations do not exist.
    *
    * @param origin
    *     The origin of the project (ubuntu, GNOME, KDE, etc.).
    * @param project
    *     The name of the project.
    * @param lng
    *     The language of translation (de, fr, sq, en_GB, etc.).
    * @param file.pot
    *     The PO file to be imported.
    */

if ($argc != 5) {
  print "
Usage: $argv[0] origin project lng file.po
  origin  -- The origin of the project (ubuntu, GNOME, KDE, etc.)
  project -- The name of the project.
  lng     -- The language of translation (de, fr, sq, en_GB, etc.).
  file.po -- The PO file to be imported.

Example:
  $argv[0] KDE kturtle fr test/kturtle.po

";
  exit(1);
}

// Get the parameters (origin, project, lng, filename).
$script = $argv[0];
$origin = $argv[1];
$project = $argv[2];
$lng = $argv[3];
$filename = $argv[4];
//log
print "$script $origin $project $lng $filename\n";

// Create a DB variable for handling queries.
include_once(dirname(__FILE__).'/po_import.db.php');
$db = new DB_PO_Import;

// Get the project id.
$pid = $db->get_project_id($project, $origin);
if ($pid === null) {
  print "Error: The project '$origin/$project' does not exist.\n";
  print "       Import first the POT file of the project.";
  exit(1);
}

// Parse the given PO file.
include_once(dirname(__FILE__).'/POParser.php');
$parser = new POParser;
$entries = $parser->parse($filename);

// Get headers and comments.
$headers = $comments = null;
if ($entries[0]['msgid'] == '') {
  $headers = $entries[0]['msgstr'];
  $comments = $entries[0]['translator-comments'];
}
// Add a file and get its id.
$fid = add_file($filename, $pid, $lng, $headers, $comments);

// Process each gettext entry.
foreach ($entries as $entry)
  {
    // Get the string sguid.
    $sguid = get_string_sguid($entry);
    if ($sguid == NULL)  continue;

    // Add the translation for this string.
    $translation = is_array($entry['msgstr']) ? implode("\0", $entry['msgstr']) : $entry['msgstr'];
    if (trim($translation) != '') {
      //print_r('--  ' . $translation . "\n");  //debug
      $tguid = $db->insert_translation($sguid, $lng, $translation);
    }
  }

// End.
exit(0);

// ------------------------ functions ----------------------

/**
 * Insert a file in the DB, if it does not already exist.
 */
function add_file($filename, $pid, $lng, $headers, $comments)
{
  // Get the sha1 hash of the file.
  $output = shell_exec("sha1sum $filename");
  $parts = explode('  ', $output);
  $hash = $parts[0];

  // Check whether the file already exists.
  global $db;
  $sql = "SELECT pid, lng FROM l10n_suggestions_files WHERE hash = :hash";
  $row = $db->query($sql, array(':hash' => $hash))->fetch();

  // If file already exists.
  if (isset($row['pid']))
    {
      if ($row['pid']==$pid and $row['lng']==$lng) {
	print "...already imported, skipping...\n";
	exit(0);
      }
      else {
        // file already imported for some other project or language
        $sql = "SELECT origin, project FROM l10n_suggestions_projects WHERE pid = :pid";
        $row1 = $db->query($sql, array(':pid' => $row['pid']))->fetch();
        $origin1 = $row1['origin'];
        $project1 = $row1['project'];
        $lng1 = $row['lng'];
	print "Error: File has already been imported for '$origin1/$project1/$lng1'.";
	exit(2);
      }
    }

  // File does not exits, insert it.
  $fid = $db->insert_file($hash, $pid, $lng, $headers, $comments);

  return $fid;
}

/**
 * Return the sguid of the string, if it already exists on the DB;
 * otherwise return NULL.
 */
function get_string_sguid($entry)
{
  // Get the string.
  $string = $entry['msgid'];
  if (isset($entry['msgid_plural'])) {
    $string .= "\0" . $entry['msgid_plural'];
  }

  // Get the context.
  $context = isset($entry['msgctxt']) ? $entry['msgctxt'] : '';

  // Get the $sguid of this string.
  $sguid = sha1($string . $context);

  // Check that it exists.
  global $db;
  if ($db->check_string_sguid($sguid)) {
    return $sguid;
  }
  else {
    return NULL;
  };
}
?>