<?php
/**
 * @file
 * Function: cron_update_mysql_materialized_views()
 */

namespace BTranslator;
use \btr;

/**
 * Update MySQL materialized views.
 */
function cron_update_mysql_materialized_views() {
  // Materialized views are used to speed-up
  // term autocompletion of vocabularies.
  // For each vocabulary project update the mv table.
  $project_list = btr::project_ls('vocabulary');
  foreach ($project_list as $project) {
    $project = str_replace('vocabulary/', '', $project);
    $table = 'btr_mv_' . strtolower($project);
    btr::db_query("TRUNCATE {$table}");
    btr::db_query("INSERT INTO {$table}
               SELECT DISTINCT s.string FROM {btr_strings} s
               JOIN {btr_locations} l ON (l.sguid = s.sguid)
               JOIN {btr_templates} t ON (t.potid = l.potid)
               JOIN {btr_projects}  p ON (p.pguid = t.pguid)
               WHERE p.project = :project
                 AND p.origin = 'vocabulary'
               ORDER BY s.string",
      array(':project' => $project)
    );
  }
}
