<?php
/**
 * Description of the command 'btr-project-list'.
 */
function _btr_project_list_drush_command() {
  return array(
    'description' => "List imported projects, filtered by origin/project.",
    'arguments' => array(
    ),
    'options' => array(
      'origin' => 'The pattern for matching the origin.',
      'project' => 'The pattern for matching the project.',
    ),
    'examples' => array(
      "drush btrp-ls --origin=KDE --project=k%" => 'List KDE projects that start with k.',
      "drush btrp-ls --project=-" => 'Get a list of all origins.'
    ),
    'aliases' => array('btrp-ls'),
  );
}

/**
 * Help text for the command 'btr-project-list'.
 */
function _btr_project_list_drush_help() {
  return dt("List imported projects, filtered by origin/project.

Options origin and project can contain '%' (for LIKE matches).
If --project='-' then only a list of 'origin' is outputed.
");
}

/**
 * Callback function for the command 'btr-project-list'.
 */
function drush_btranslator_btr_project_list() {
  $origin = drush_get_option('origin');
  $project = drush_get_option('project');

  $project_list = btr::project_ls($origin, $project);
  foreach($project_list as $project)  {
    // Exclude vocabularies.
    if (preg_match('#^vocabulary/#', $project))  continue;
    drush_print($project);
  }
}
