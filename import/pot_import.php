#!/usr/bin/php
<?php
   /**
    * 'pot_import.php' creates a new project (or updates an existing one).
    * Along with the project, it also creates/updates locations and strings.
    * The POT file that is given as input can be either a *.pot file, or
    * the *.po file of a language (for example fr, de, etc.). In case that
    * it is a *.po file, its translations (msgstr) are not used and the file
    * has to be imported again with 'po_import.php'.
    *
    * @param origin
    *     The origin of the project (ubuntu, GNOME, KDE, etc.).
    * @param project
    *     The name of the project that is being imported.
    * @param file.pot
    *     The POT file of the project.
    */

if ($argc != 4) {
  print "
Usage: $argv[0] origin project file.pot
  origin   -- The origin of the project (ubuntu, GNOME, KDE, etc.)
  project  -- The name of the project that is being imported.
  file.pot -- The POT file of the project.

Examples:
  $argv[0] KDE kturtle test/kturtle.pot
  $argv[0] KDE kturtle test/kturtle_fr.po

";
  exit(1);
}

// Get the parameters (origin, project, filename).
$script = $argv[0];
$origin = $argv[1];
$project = $argv[2];
$filename = $argv[3];
//log
print "$script $origin $project $filename\n";

// Create a DB variable for handling queries.
include_once(dirname(__FILE__).'/pot_import.db.php');
$db = new DB_POT_Import;

// Create a new project with the given name and origin.
$pid = add_project($project, $origin);

// Parse the given PO file.
include_once(dirname(__FILE__).'/POParser.php');
$parser = new POParser;
$entries = $parser->parse($filename);

// Process each gettext entry.
foreach ($entries as $entry)
  {
    // Create a new string, or increment its count.
    $sguid = add_string($entry);
    if ($sguid == NULL) continue;

    // Insert a new location record.
    $lid = $db->insert_location($pid, $sguid, $entry);
  }

// End.
exit(0);

// ----------------- functions ----------------------

/**
 * Create a new project record with the given name and origin.
 */
function add_project($project, $origin)
{
  global $db;

  // If such a project already exist, then delete it.
  $pid = $db->get_project_id($project, $origin);
  if ($pid) {
    delete_project($pid);
  }

  // Insert a new project.
  $pid = $db->insert_project($project, $origin);

  return $pid;
}

/**
 * Delete the project and the locations and files related to it.
 */
function delete_project($pid)
{
  global $db;

  // Decrement the count of the strings related to this project.
  $db->exec("UPDATE l10n_suggestions_strings SET count = count - 1
             WHERE sguid IN (SELECT sguid FROM l10n_suggestions_locations WHERE pid = $pid)");

  // Delete the locations of this project.
  $db->exec("DELETE FROM l10n_suggestions_locations WHERE pid = $pid");

  // Delete the files related to this project.
  $db->exec("DELETE FROM l10n_suggestions_files WHERE pid = $pid");

  // Delete the project itself.
  $db->exec("DELETE FROM l10n_suggestions_projects WHERE pid = $pid");
}


/**
 * Insert a new string in the DB for the msgid and msgctxt of the
 * given entry. If such a string already exists, then just increment
 * its count.
 *
 * If the msgid is empty (the header entry), don't add a string
 * for it. The same for some other entries like 'translator-credits' etc.
 *
 * Return the sguid of the string record, or NULL.
 */
function add_string($entry)
{
  // Get the string.
  $string = $entry['msgid'];
  if (isset($entry['msgid_plural'])) {
    $string .= "\0" . $entry['msgid_plural'];
  }

  // Don't add the header entry as a translatable string.
  // Don't add strings like 'translator-credits' etc. as translatable strings.
  if ($string == '')  return NULL;
  if (preg_match('/.*translator.*credit.*/', $string))  return NULL;

  // Get the context.
  $context = isset($entry['msgctxt']) ? $entry['msgctxt'] : '';

  // Get the $sguid of this string.
  $sguid = sha1($string . $context);

  // Increment the count of the string.
  // If no record was affected, it means that such a string
  // does not exist, so insert a new string.
  $sql = "UPDATE l10n_suggestions_strings SET count = count + 1 WHERE sguid = '$sguid'";
  global $db;
  if (!$db->exec($sql)) {
    $db->insert_string($string, $context);

    // TODO: If the entry has a previous-msgid, then deprecate the
    //       corresponding string.
  }

  return $sguid;
}
?>