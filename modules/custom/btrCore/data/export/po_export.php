#!/usr/bin/php
<?php
   // Print the usage of the script and exit.
function print_usage($argv) {
  print "
Usage: $argv[0] origin project tplname lng [file.po [export_mode [preferred_voters]]]

  origin      -- the origin of the project (ubuntu, GNOME, KDE, etc.)
  project     -- the name of the project to be exported
  tplname     -- the name of the PO template
  lng         -- translation to be exported (de, fr, sq, en_GB, etc.)
  file.po     -- output file (stdout if not given)
  export_mode -- 'most_voted' (default), or 'preferred', or 'original'

The export mode 'most_voted' (which is the default one) exports the
most voted translations and suggestions.

The export mode 'preferred' gives priority to translations that are voted
by a certain user or a group of users. It requires an additional argument
(preferred_voters) to specify the user (or a list of users) whose translations
are preferred. The argument 'preferred_voters' is a comma separated list
of email addresses. If a string has no translation that is voted by any
of the preferred users, then the most voted translation is exported.

The export mode 'original' exports the translations of the original
file that was imported (useful for making an initial snapshot of
the project).

If the export_mode argument is missing, then the env variable PO_EXPORT_MODE
will be tried. If the preferred_voters argument is missing, then the env
variable PO_EXPORT_VOTERS will be tried.

Examples:
  $argv[0] KDE kdeedu kturtle fr > test/kturtle_fr.po
  $argv[0] KDE kdeedu kturtle fr test/kturtle_fr.po original
  $argv[0] KDE kdeedu kturtle fr test/kturtle_fr.po preferred \
           'email1@example.com,email2@example.com,email3@example.com'

";
  exit(1);
}

// Check the number of parameters.
if ($argc < 4)  print_usage($argv);

// Get the parameters (project, lng, origin, file.po).
$script = $argv[0];
$origin = $argv[1];
$project = $argv[2];
$tplname = $argv[3];
$lng = $argv[4];
$filename = isset($argv[5]) ? $argv[5] : NULL;
$export_mode = isset($argv[6]) ? $argv[6] : getenv('PO_EXPORT_MODE');
if (!$export_mode) {
  $export_mode = 'most_voted';
}
if (!in_array($export_mode, array('most_voted', 'preferred', 'original'))) {
  print_usage($argv);
}
if ($export_mode=='preferred') {
  $preferred_voters = isset($argv[7]) ? $argv[7] : getenv('PO_EXPORT_VOTERS');
  if (empty($preferred_voters)) {
    print_usage($argv);
  }
  $preferred_voters = explode(',', $preferred_voters);
}

// Create a DB variable for handling queries.
include_once(dirname(__FILE__).'/po_export.db.php');
$db = new DB_PO_Export;

// Get the id of the template.
$potid = $db->get_template_potid($origin, $project, $tplname);
if ($potid === NULL) {
  print "Template $origin/$project/$tplname not found!";
  exit(1);
}

// Get the headers, strings and translations.
list($headers, $comments) = $db->get_file_headers($potid, $lng);
$strings = $db->get_strings($potid);

// Get translations.
switch ($export_mode) {
case 'preferred':
  $preferred_trans = $db->get_preferred_translations($potid, $lng, $preferred_voters);
  //cascade, no break
case 'most_voted':
  $most_voted_trans = $db->get_most_voted_translations($potid, $lng);
  //cascade, no break
case 'original':
  $original_po_file = $db->get_original_file($potid, $lng);
  $original_trans = get_translations_from_file($original_po_file);
  shell_exec("rm $original_po_file");
  break;
}

// Add translations to the corresponding strings.
foreach (array_keys($strings) as $sguid) {
  $translation = '';
  switch ($export_mode) {
  case 'preferred':
    if (empty($translation)) {
      $translation = isset($preferred_trans[$sguid]) ? $preferred_trans[$sguid] : '';
    }
    //cascade, no break
  case 'most_voted':
    if (empty($translation)) {
      $translation = isset($most_voted_trans[$sguid]) ? $most_voted_trans[$sguid] : '';
    }
    //cascade, no break
  case 'original':
    if (empty($translation)) {
      $translation = isset($original_trans[$sguid]) ? $original_trans[$sguid] : '';
    }
    break;
  }
  $strings[$sguid]->translation = $translation;
}
//print_r($strings);  exit(0);  //debug

// Write entries to a PO file.
include_once(dirname(dirname(__FILE__)).'/gettext/POWriter.php');
$writer = new POWriter;
if ($filename === NULL or $filename == 'stdout') {
  $output = $writer->write($headers, $comments, $strings);
  print(implode("\n", $output) . "\n");
}
else {
  $writer->write($headers, $comments, $strings, $filename);
}

// End.
exit(0);

/* -------------------------------------------- */

/**
 * Parse the given PO file and return an associative array
 * of its translations, indexed by sguid.
 */
function get_translations_from_file($file)
{
  // Parse the given PO file.
  include_once(dirname(dirname(__FILE__)).'/gettext/POParser.php');
  $parser = new POParser;
  $entries = $parser->parse($file);

  // Process each gettext entry.
  $arr_translations = array();
  foreach ($entries as $entry)
    {
      // Get the string sguid.
      $string = $entry['msgid'];
      if (isset($entry['msgid_plural'])) {
	$string .= "\0" . $entry['msgid_plural'];
      }
      $context = isset($entry['msgctxt']) ? $entry['msgctxt'] : '';
      $sguid = sha1($string . $context);

      // Add the translation for this string.
      $translation = is_array($entry['msgstr']) ? implode("\0", $entry['msgstr']) : $entry['msgstr'];
      $arr_translations[$sguid] = $translation;
    }

  return $arr_translations;
}
?>