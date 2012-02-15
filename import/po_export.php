#!/usr/bin/php
<?php
   // Print the usage of the script and exit.
function print_usage($argv) {
  print "
Usage: $argv[0] origin project tplname lng [file.po [algorithm]]
  origin    -- the origin of the project (ubuntu, GNOME, KDE, etc.)
  project   -- the name of the project to be exported
  tplname   -- The name of the PO template.
  lng       -- translation to be exported (de, fr, sq, en_GB, etc.)
  file.po   -- output file (stdout if not given)
  algorithm -- 'most_voted' (default) or 'original'

The algorithm 'most_voted' (which is the default one) exports the
most voted translations and suggestions.
The algorithm 'original' exports the translations of the original
file that was imported (useful for making an initial snapshot of
the project).

Examples:
  $argv[0] KDE kturtle kturtle fr > test/kturtle_fr.po
  $argv[0] KDE kturtle kturtle fr test/kturtle_fr.po original

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
$filename = isset($argv[5]) ? $argv[5] : null;
$algorithm = isset($argv[6]) ? $argv[6] : 'most_voted';
if (!in_array($algorithm, array('most_voted', 'original'))) {
  print_usage($argv);
}

// Create a DB variable for handling queries.
include_once(dirname(__FILE__).'/po_export.db.php');
$db = new DB_PO_Export;

// Get the id of the template.
$potid = $db->get_template_potid($origin, $project, $tplname);
if ($potid === null) {
  print "Template $origin/$project/$tplname not found!";
}

// Get the headers, strings and translations.
list($headers, $comments) = $db->get_file_headers($potid, $lng);
$strings = $db->get_strings($potid);

// Get translations.
$most_voted_trans = $db->get_most_voted_translations($potid, $lng);
$original_po_file = $db->get_original_file($potid, $lng);
$original_trans = get_translations_from_file($original_po_file);

// Add translations to the corresponding strings.
foreach (array_keys($strings) as $sguid) {
  if ($algorithm == 'original')
    {
      $translation = isset($original_trans[$sguid]) ? $original_trans[$sguid] : '';
    }
  else // ($algorithm == 'most_voted')
    {
      $translation = isset($most_voted_trans[$sguid]) ? $most_voted_trans[$sguid] : '';
      if ($translation=='') {
	$translation = isset($original_trans[$sguid]) ? $original_trans[$sguid] : '';
      }
    }
  $strings[$sguid]->translation = $translation;
}
//print_r($strings);  exit(0);  //debug

// Write entries to a PO file.
include_once(dirname(__FILE__).'/POWriter.php');
$writer = new POWriter;
if ($filename === NULL) {
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
  include_once(dirname(__FILE__).'/POParser.php');
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