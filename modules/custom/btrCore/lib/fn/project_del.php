<?php
/**
 * @file
 * Definition of function project_del() which is used for deleting projects.
 */

namespace BTranslator;
use \btr;

/**
 * Delete everything related to the given origin and project.
 *
 * It will delete templates, locations, files, snapshots, diffs
 * and the projects itself (but not the strings, translations, etc.)
 * If no project is given, then all the projects of the given origin
 * will be deleted. If the origin is NULL, then all the projects
 * of the given name (from any origin) will be deleted.
 *
 * @param $origin
 *   The origin of the project to be deleted.
 *
 * @param $project
 *   The name of the project to be deleted.
 *
 * @param $erase
 *   If true, then snapshots and diffs are deleted as well.
 *
 * @param $purge
 *   If true, delete as well any dangling strings that don't belong
 *   to any project (and their translations that have no votes).
 */
function project_del($origin = NULL, $project = NULL, $erase = TRUE, $purge = TRUE) {
  // The parameters should not be both NULL.
  if ($origin === NULL and $project === NULL)  return;

  // Get an array of matching projects.
  $get_pguid = btr_select('btr_projects', 'p')->fields('p', array('pguid'));
  if ($origin != NULL)  $get_pguid->condition('origin', $origin);
  if ($project != NULL)  $get_pguid->condition('project', $project);
  $pguid_list = $get_pguid->execute()->fetchCol();
  if (empty($pguid_list))  return;

  // Get an array of templates related to the projects.
  $potid_list = btr_query(
    'SELECT potid FROM {btr_templates} t
     LEFT JOIN {btr_projects} p ON (t.pguid = p.pguid)
     WHERE p.pguid IN (:pguid_list)',
    array(
      ':pguid_list' => $pguid_list,
    ))
    ->fetchCol();

  // Erase the data of each template.
  foreach ($potid_list as $potid) {
    _delete_template($potid);
  }

  // Delete the diffs and snapshots of each project.
  if ($erase) {
    foreach ($pguid_list as $pguid) {
      btr_delete('btr_diffs')->condition('pguid', $pguid)->execute();
      btr_delete('btr_snapshots')->condition('pguid', $pguid)->execute();
    }
  }

  // Delete the projects themselves.
  btr_delete('btr_projects')
    ->condition('pguid', $pguid_list, 'IN')
    ->execute();

  // Delete any dangling strings.
  if ($purge) {
    btr::string_cleanup();
  }
}

/**
 * Delete the template with the given id, as well as the locations
 * and files related to it.
 */
function _delete_template($potid) {
  // Decrement the count of the strings related to this template.
  btr_query(
    'UPDATE {btr_strings} AS s
     INNER JOIN (SELECT sguid FROM {btr_locations} WHERE potid = :potid) AS l
             ON (l.sguid = s.sguid)
     SET s.count = s.count - 1',
    array(':potid' => $potid));

  // Delete the locations, files, and the template itself.
  btr_delete('btr_locations')->condition('potid', $potid)->execute();
  btr_delete('btr_files')->condition('potid', $potid)->execute();
  btr_delete('btr_templates')->condition('potid', $potid)->execute();
}

