<?php
/**
 * @file
 * Function _create_tmp_tables().
 */

/**
 * Create the temporary tables {btr_tpm_translations} and {btr_tmp_votes}
 * with the relevant translations and votes.
 */
function _create_tmp_tables($lng, $origin, $project) {
  // Create a temporary table of the relevant translations.
  $sql_get_translations = "CREATE TEMPORARY TABLE {btr_tmp_translations} AS
        SELECT t.*
        FROM {btr_projects} p
        JOIN {btr_templates} tpl ON (tpl.pguid = p.pguid)
        JOIN {btr_locations} l ON (l.potid = tpl.potid)
        JOIN {btr_strings} s ON (l.sguid = s.sguid)
        JOIN {btr_translations} t ON (t.sguid = s.sguid AND t.lng = :lng)
        WHERE p.origin = :origin";
  $args = [':lng' => $lng, 'origin' => $origin];
  if ($project != NULL) {
    $sql_get_translations .= " AND p.project = :project";
    $args[':project'] = $project;
  }
  btr::db_query($sql_get_translations, $args);

  // Create a temporary table of the relevant votes.
  $sql_get_votes = "CREATE TEMPORARY TABLE {btr_tmp_votes} AS
        SELECT v.*
        FROM {btr_tmp_translations} t
        JOIN {btr_votes} v ON (v.tguid = t.tguid)
    ";
  btr::db_query($sql_get_votes);
}
