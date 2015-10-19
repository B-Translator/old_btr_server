<?php
/**
 * @file
 * Exporting translation files of a project.
 */

namespace BTranslator;
use \btr;

module_load_include('php', 'btrCore', 'lib/gettext/POParser');
module_load_include('php', 'btrCore', 'lib/gettext/POWriter');

/**
 * Export the translation (PO) files of a given origin/project/lng.
 *
 * It the environments variable QUIET is defined, then it will
 * be less verbose (will not output much progress/debug info).
 *
 * @param $origin
 *   The origin of the project.
 *
 * @param $project
 *   The name of the project.
 *
 * @param $lng
 *   The language of the translation files.
 *
 * @param $path
 *   The directory where the translation files will be saved.
 *
 * @param $export_mode
 *   Can be 'most_voted' (default), or 'preferred', or 'original'.
 *
 * @param $preferred_voters
 *   Array of email addresses of users whose translations are preferred.
 *
 * @param $uid
 *   ID of the user that has requested the export.
 *
 * The export mode 'most_voted' (which is the default one) exports the most
 * voted translations and suggestions.
 *
 * The export mode 'preferred' gives priority to translations that are voted
 * by a certain user or a group of users. It requires an additional argument
 * (preferred_voters) to specify the user (or a list of users) whose
 * translations are preferred. If a string has no translation that is voted by
 * any of the preferred users, then the most voted translation is exported.
 *
 * The export mode 'original' exports the translations of the original file
 * that was imported (useful for making an initial snapshot of the project).
 */
function project_export($origin, $project, $lng, $path, $export_mode = 'most_voted',
  $preferred_voters = NULL, $uid = NULL)
{
  btr::messages("Export project: $origin/$project/$lng: $path");

  // Check arguments $export_mode and $preferred_voters.
  if (!in_array($export_mode, ['most_voted', 'preferred', 'original'])) {
    $export_mode = 'most_voted';
  }
  if ($export_mode == 'preferred' and empty($preferred_voters)) {
    $account = user_load(btr::user_check($uid));
    $preferred_voters = [$account->init];
  }

  // Get the templates and filenames of the project.
  $result = btr::db_query(
    'SELECT t.tplname, f.filename
     FROM {btr_files} f
     LEFT JOIN {btr_templates} t ON (f.potid = t.potid)
     LEFT JOIN {btr_projects} p ON (t.pguid = p.pguid)
     WHERE p.origin = :origin
       AND p.project = :project
       AND f.lng = :lng',
    [
      ':origin' => $origin,
      ':project' => $project,
      ':lng' => $lng,
    ])
    ->fetchAll();

  // Export each file of the project.
  foreach ($result as $row) {
    btr::messages("Export PO file: $origin/$project/$lng: $row->filename");

    $tplname = $row->tplname;
    $po_file = $path . '/' . $row->filename;

    // Get the id of the template ($potid).
    $potid = btr::db_query(
      'SELECT potid FROM {btr_templates}
       WHERE pguid = :pguid AND tplname = :tplname',
      [
        ':pguid' => sha1($origin . $project),
        ':tplname' => $tplname,
      ])
      ->fetchField();
    if (!$potid) {
      $msg = t("Template '!tplname' not found!", ['!tplname' => $tplname]);
      btr::messages($msg, 'warning');
      continue;
    }

    // Export this file.
    _export_po_file($potid, $lng, $po_file, $export_mode, $preferred_voters);
  }
}


/**
 * Export a PO file.
 */
function _export_po_file($potid, $lng, $filename, $export_mode = 'most_voted', $preferred_voters = NULL) {
  // Get headers and comments of the template.
  $row = btr::db_query(
    'SELECT headers, comments FROM {btr_files}
     WHERE potid = :potid AND lng = :lng',
    [':potid' => $potid, ':lng' => $lng])
    ->fetch();
  $headers = isset($row->headers) ? $row->headers : NULL;
  $comments = isset($row->comments) ? $row->comments : NULL;

  // Get strings of the template.
  $strings = btr::db_query(
    'SELECT l.sguid, s.string, s.context,
            translator_comments, extracted_comments, line_references, flags,
            previous_msgctxt, previous_msgid, previous_msgid_plural
     FROM {btr_locations} l
     LEFT JOIN {btr_strings} s ON (s.sguid = l.sguid)
     WHERE l.potid = :potid',
    [':potid' => $potid]
  )->fetchAllAssoc('sguid');

  // Get translations.
  switch ($export_mode) {
    case 'preferred':
      $preferred_trans = _get_preferred_translations($potid, $lng, $preferred_voters);
      //cascade, no break
    case 'most_voted':
      $most_voted_trans = _get_most_voted_translations($potid, $lng);
      //cascade, no break
    case 'original':
      $original_trans = _get_original_translations($potid, $lng);
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

  // Write entries to a PO file.
  exec('mkdir -p ' . dirname($filename));
  $writer = new POWriter;
  $writer->write($headers, $comments, $strings, $filename);
}


/**
 * Export from DB the content of the original file that was imported, parse it
 * and return an associative array of its translations, indexed by sguid.
 */
function _get_original_translations($potid, $lng)
{
  // Get the content of the imported PO file.
  $file_content = btr::db_query(
    'SELECT content FROM {btr_files}
     WHERE potid = :potid AND lng = :lng',
    [':potid' => $potid, ':lng' => $lng]
  )->fetchField();

  if (!$file_content) {
    return [];
  }

  // Write it content to a temporary file.
  $tmpfile = '/tmp/' . md5($file_content) . '.po';
  file_put_contents($tmpfile, $file_content);

  // Parse this file and delete it.
  $parser = new POParser;
  $entries = $parser->parse($tmpfile);
  unlink($tmpfile);

  // Process each gettext entry.
  $arr_translations = [];
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


/**
 * Get and return an associative array of the most voted translations,
 * indexed by sguid. Translations which have no votes at all are skipped.
 */
function _get_most_voted_translations($potid, $lng) {
  // Create a temporary table with the maximum vote count for each string.
  $tmp_table_translations_max_count =
    btr::db_query_temporary(
      'SELECT t.sguid, MAX(t.count) AS max_count
       FROM {btr_locations} AS l
       LEFT JOIN {btr_translations} AS t
                 ON (t.sguid = l.sguid AND t.lng = :lng)
       WHERE l.potid = :potid
       GROUP BY t.sguid',
      [':potid' => $potid, ':lng' => $lng]);

  // Get the translations with the max vote count for each string.
  // The result will be an assoc array (sguid => translation).
  $most_voted_translations =
    btr::db_query(
      "SELECT t.sguid, t.translation
       FROM {$tmp_table_translations_max_count} AS cnt
       LEFT JOIN {btr_translations} AS t
             ON ( t.sguid = cnt.sguid
             AND  t.count = cnt.max_count
             AND  t.lng = :lng )
       GROUP BY t.sguid",
      [':lng' => $lng]
    )
    ->fetchAllKeyed();

  return $most_voted_translations;
}


/**
 * Get and return an associative array of the translations that are voted
 * by any of the people in the array of voters, indexed by sguid.
 * Translations which have no votes from these users are skipped.
 * Voters are identified by their emails.
 */
function _get_preferred_translations($potid, $lng, $arr_voters) {
  if (empty($arr_voters)) {
    return [];
  }

  // Build a temporary table with translations
  // that have any votes from the preferred users.
  $tmp_table_voted_translations =
    btr::db_query_temporary(
      'SELECT t.sguid, t.tguid, t.translation, COUNT(*) AS v_count
       FROM {btr_locations} AS l
       LEFT JOIN {btr_translations} AS t
                 ON (t.sguid = l.sguid AND t.lng = :lng)
       LEFT JOIN {btr_votes} AS v
                 ON (v.tguid = t.tguid)
       WHERE l.potid = :potid
         AND v.umail IN (:voters)
       GROUP BY t.tguid
       HAVING COUNT(*) > 0',
      [
        ':potid' => $potid,
        ':lng' => $lng,
        ':voters' => $arr_voters,
      ]);

  // Build a temporary table with the maximum votes for each string.
  $tmp_table_max_vote_count =
    btr::db_query_temporary(
      "SELECT sguid, MAX(v_count) AS max_count
       FROM {$tmp_table_voted_translations}
       GROUP BY sguid"
    );

  // Get translations with the max vote count for each string,
  // as an assoc array (sguid => translation).
  $preferred_translations =
    btr::db_query(
      "SELECT cnt.sguid, t.translation
       FROM {$tmp_table_max_vote_count} AS cnt
       LEFT JOIN {$tmp_table_voted_translations} AS t
                 ON (t.sguid = cnt.sguid AND t.v_count = cnt.max_count)
       GROUP BY cnt.sguid"
    )
    ->fetchAllKeyed();

  return $preferred_translations;
}
