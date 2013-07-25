#!/usr/bin/php
<?php
   /**
    * 'po_import.php' imports a new PO (translation) file.  It assumes
    * that the POT file of the project has already been imported,
    * otherwise it will quit without doing anything.  If the file has
    * been already imported, then it is skiped.
    *
    * For each file, all the information that is needed for exporting
    * it is stored, like the file name and path, the headers of the
    * file, the content of the file, etc.
    *
    * Along with the file, it also inserts the translations for the
    * corresponding strings, when such translations do not exist.
    *
    * @param origin
    *     The origin of the project (ubuntu, GNOME, KDE, LibreOffice, Mozilla, etc.).
    * @param project
    *     The name of the project.
    * @param tplname
    *     The name of the PO template.
    * @param lng
    *     The language of translation (de, fr, sq, en_GB, etc.).
    * @param file.po
    *     The PO file to be imported.
    */

if ($argc != 6) {
  print "
Usage: $argv[0] origin project tplname lng file.po
  origin  -- The origin of the project (ubuntu, GNOME, KDE, LibreOffice, etc.)
  project -- The name of the project.
  tplname -- The name of the PO template.
  lng     -- The language of translation (de, fr, sq, en_GB, etc.).
  file.po -- The PO file to be imported.

Example:
  $argv[0] KDE kdeedu kturtle fr test/kturtle.po

";
  exit(1);
}

// Get the parameters (origin, project, tplname, lng, filename).
$script = $argv[0];
$origin = $argv[1];
$project = $argv[2];
$tplname = $argv[3];
$lng = $argv[4];
$filename = $argv[5];
//log
print "$script $origin $project $tplname $lng $filename\n";

// Create a DB variable for handling queries.
include_once(dirname(__FILE__).'/po_import.db.php');
$db = new DB_PO_Import;

// Get the template id.
$potid = $db->get_template_potid($origin, $project, $tplname);
if ($potid === NULL) {
  print "Error: The template '$origin/$project/$tplname' does not exist.\n";
  print "       Import first the POT file of the project.";
  exit(1);
}

// Parse the given PO file.
include_once(dirname(dirname(__FILE__)).'/gettext/POParser.php');
$parser = new POParser;
$entries = $parser->parse($filename);

// Get headers and comments.
$headers = $comments = NULL;
if ($entries[0]['msgid'] == '') {
  $headers = $entries[0]['msgstr'];
  $comments = isset($entries[0]['translator-comments']) ? $entries[0]['translator-comments'] : '';
}

// Get the pathname of the file, relative to origin.
$relative_filename = preg_replace("#^.*/$origin/#", '', $filename);
// Add a file and get its id.
$fid = add_file($filename, $relative_filename, $potid, $lng, $headers, $comments);

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
function add_file($filename, $relative_filename, $potid, $lng, $headers, $comments)
{
  // Get the sha1 hash of the file.
  $output = shell_exec("sha1sum $filename");
  $parts = explode('  ', $output);
  $hash = $parts[0];

  // Check whether the file already exists.
  global $db;
  $sql = "SELECT potid, lng FROM l10n_feedback_files WHERE hash = :hash";
  $row = $db->query($sql, array(':hash' => $hash))->fetch();

  // If file already exists.
  if (isset($row['potid']))
    {
      if ($row['potid']==$potid and $row['lng']==$lng) {
	print "...already imported, skipping...\n";
	exit(0);
      }
      else {
        // file already imported for some other template or language
        $sql = "SELECT p.origin, p.project, t.tplname
                FROM l10n_feedback_templates t
                LEFT JOIN l10n_feedback_projects p ON (t.pguid = p.pguid)
                WHERE t.potid = :potid";
        $row1 = $db->query($sql, array(':potid' => $row['potid']))->fetch();
        $origin1 = $row1['origin'];
        $project1 = $row1['project'];
        $tplname1 = $row1['tplname'];
        $lng1 = $row['lng'];
        print "Warning: File '$filename' has already been imported for '$origin1 $project1 $tplname1 $lng1'.\n";
      }
    }

  // Insert the file.
  $fid = $db->insert_file($filename, $relative_filename, $hash, $potid, $lng, $headers, $comments);

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