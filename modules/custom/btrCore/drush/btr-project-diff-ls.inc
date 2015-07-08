<?php
/**
 * Description of the command 'btr-project-diff-ls'.
 */
function _btr_project_diff_ls_drush_command() {
  return array(
    'description' => "Show a list of diffs for the given origin/project/lng.",
    'arguments' => array(
      'origin' => 'The origin of the project.',
      'project' => 'The name of the project',
      'lng' => 'The language of translations.',
    ),
    'options' => array(
    ),
    'examples' => array(
      'drush btrp-diff-ls KDE kdeedu sq' => '',
    ),
    'aliases' => array('btrp-diff-ls'),
  );
}

/**
 * Help text for the command 'btr-project-diff-ls'.
 */
function _btr_project_diff_ls_drush_help() {
  return dt("Show a list of diffs for the given origin/project/lng.");
}

/**
 * Callback function for the command 'btr-project-diff-ls'.
 */
function drush_btranslator_btr_project_diff_ls($origin, $project, $lng) {
  // Check parameters $origin, $project, $lng.
  _btranslator_drush_check_params($origin, $project, $lng);

  $arr_diffs = array();
  $diff_list = btr::project_diff_list($origin, $project, $lng);
  foreach ($diff_list as $diff) {
    // Separate fields by TAB.
    $arr_diffs[] = implode("\t", array($diff->nr, $diff->time, $diff->comment));
  }
  $output = implode("\n", $arr_diffs) . "\n";
  print $output;
}
