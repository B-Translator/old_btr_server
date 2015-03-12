#!/usr/bin/drush @btr php-script
<?php
  // Materialized views are used to speed-up
  // term autocompletion of vocabularies.
  $projects = array('ICT_sq', 'huazime_sq');
  foreach ($projects as $project) {
    $table = 'btr_mv_' . strtolower($project);
    btr_query("TRUNCATE {$table}");
    btr_query("INSERT INTO {$table}
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
?>
