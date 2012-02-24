#!/usr/bin/php
<?php
   /**
    * 'pot_import.php' creates a new template and a new project (if needed).
    * Along with the template, it also creates/updates locations and strings.
    * The POT file that is given as input can be either a *.pot file, or
    * the *.po file of a language (for example fr, de, etc.). In case that
    * it is a *.po file, its translations (msgstr) are not used and the file
    * has to be imported again with 'po_import.php'.
    *
    * @param origin
    *     The origin of the project (ubuntu, GNOME, KDE, LibreOffice, Mozilla, etc.).
    * @param project
    *     The name of the project that is being imported.
    * @param tplname
    *     The name of the PO template.
    * @param file.pot
    *     The POT file of the project.
    */

if ($argc != 5) {
  print "
Usage: $argv[0] origin project tplname file.pot
  origin   -- The origin of the project (ubuntu, GNOME, KDE, LibreOffice, etc.)
  project  -- The name of the project that is being imported.
  tplname  -- The name of the PO template.
  file.pot -- The POT file of the project.

Examples:
  $argv[0] KDE kturtle kturtle test/kturtle.pot
  $argv[0] KDE kturtle kturtle test/kturtle_fr.po

";
  exit(1);
}

// Get the parameters (origin, project, filename).
$script = $argv[0];
$origin = $argv[1];
$project = $argv[2];
$tplname = $argv[3];
$filename = $argv[4];
//log
print "$script $origin $project $tplname $filename\n";

// Create a DB variable for handling queries.
include_once(dirname(__FILE__).'/pot_import.db.php');
$db = new DB_POT_Import;

// Get the pguid of the project with the given name and origin.
$pguid = get_project($project, $origin);

// Get the pathname of the file, relative to origin.
$file = preg_replace("#^.*/$origin/#", '', $filename);
// Create a new template for this project.
$potid = add_template($pguid, $tplname, $file);

// Parse the given PO file.
include_once(dirname(dirname(__FILE__)).'/gettext/POParser.php');
$parser = new POParser;
$entries = $parser->parse($filename);

// Process each gettext entry.
foreach ($entries as $entry)
  {
    // Create a new string, or increment its count.
    $sguid = add_string($entry);
    if ($sguid == NULL) continue;

    // Insert a new location record.
    $lid = $db->insert_location($potid, $sguid, $entry);
  }

// End.
exit(0);

// ----------------- functions ----------------------

/**
 * Get and return the id of the project with the given
 * name and origin.
 * If such a project does not exist, then create a new one.
 */
function get_project($project, $origin)
{
  global $db;

  $pguid = $db->get_project_pguid($project, $origin);
  if (!$pguid) {
    $pguid = $db->insert_project($project, $origin);
  }

  return $pguid;
}

/**
 * Create a new template record for the given project.
 */
function add_template($pguid, $tplname, $filename)
{
  global $db;

  // If such a template already exists, then delete it.
  $potid = $db->get_template_potid($pguid, $tplname);
  if ($potid) {
    delete_template($potid);
  }

  // Insert a new template.
  $potid = $db->insert_template($pguid, $tplname, $filename);

  return $potid;
}

/**
 * Delete the template and the locations and files related to it.
 */
function delete_template($potid)
{
  global $db;

  // Decrement the count of the strings related to this template.
  $db->exec("
         UPDATE l10n_suggestions_strings AS s
         INNER JOIN (SELECT sguid FROM l10n_suggestions_locations WHERE potid = $potid) AS l
             ON (l.sguid = s.sguid)
         SET s.count = s.count - 1"
	    );

  // Delete the locations of this project.
  $db->exec("DELETE FROM l10n_suggestions_locations WHERE potid = $potid");

  // Delete the files related to this project.
  $db->exec("DELETE FROM l10n_suggestions_files WHERE potid = $potid");

  // Delete the template itself.
  $db->exec("DELETE FROM l10n_suggestions_templates WHERE potid = $potid");
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