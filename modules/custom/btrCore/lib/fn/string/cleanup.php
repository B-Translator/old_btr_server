<?php
/**
 * @file
 * Definition of function string_cleanup().
 */

namespace BTranslator;
use \btr;

/**
 * Delete any dangling strings that don't belong to any project, and their
 * translations that have no votes.
 *
 * @param $purge
 *   If true, delete as well translations that have votes.
 */
function string_cleanup($purge = FALSE) {
  // Create a temporary table with the dangling strings.
  $dangling_strings =
    btr::db_query_temporary(
      'SELECT s.sguid
       FROM {btr_strings} s
       LEFT JOIN {btr_locations} l ON (l.sguid = s.sguid)
       WHERE l.lid IS NULL'
    );

  // Count the dangling strings.
  $count = btr::db_query(
    "SELECT COUNT(*) AS cnt FROM {$dangling_strings}"
  )->fetchField();

  // If there are no dangling strings, stop here.
  if (!$count)  return;

  // Delete translations of dangling strings that have no votes.
  btr::db_query(
    "DELETE t.* FROM {btr_translations} t
     INNER JOIN {$dangling_strings} d ON (d.sguid = t.sguid)
     LEFT JOIN {btr_votes} v ON (v.tguid = t.tguid)
     WHERE v.vid IS NULL"
  );

  // Delete translations that have votes as well.
  if ($purge) {
    // Get a list of translations that will be deleted.
    $tguid_list = btr::db_query(
      "SELECT t.tguid FROM {btr_translations} t
       INNER JOIN {$dangling_strings} d ON (d.sguid = t.sguid)"
    )->fetchCol();

    // Delete each translation (and related votes as well).
    foreach ($tguid_list as $tguid) {
      btr::translation_del($tguid, $notify=FALSE, $uid=1);
    }
  }

  // Delete the dangling strings itself.
  btr::db_query(
    "DELETE s.* FROM {btr_strings} s
     INNER JOIN {$dangling_strings} d ON (d.sguid = s.sguid)"
  );
}
