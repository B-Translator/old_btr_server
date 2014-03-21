<?php
/**
 * @file
 * Resource definition and callbacks for project.
 */

function _btrServices_project() {
  $file = array('type' => 'inc', 'module' => 'btrServices', 'name' => 'resources/project');
  $params = array(
    'name' => 'params',
    'optional' => FALSE,
    'source' => 'data',
    'description' => 'Array of parameters.',
    'type' => 'array',
  );
  $public_access = array(
    'access callback' => 'user_access',
    'access arguments' => array('access content'),
  );

  // Get a list of existing projects.
  $translations['actions']['list'] = array(
    'help' => 'Get a list of existing projects.',
    'file' => $file,
    'callback' => '_btrServices_project_list',
    'args' => array($params),
  ) + $public_access;

  return $translations;
}

/**
 * Get a list of existing projects.
 *
 * @param $params
 *   Associative array of the POST data, which contains
 *   the filter parameters. These parameters can be:
 *   - origin
 *   - project
 *
 *   Variables $origin and $project can contain '*', which
 *   is replaced by '%' (for LIKE matches).
 *
 *   If $project=='-' then only a list of 'origin' is outputed,
 *   otherwise a list of 'origin/project'.
 *
 * @return
 *   Project list as an array, where each item can be on the form
 *   'origin/project' or just 'origin'.
 *
 * @example
 *   curl -k -i -X POST https://dev.l10n.org.xx/public/btr/project/list
 *   curl -k -i -X POST https://dev.l10n.org.xx/public/btr/project/list \
 *        -H "Content-type: application/json" \
 *        -d '{"origin": "t*"}'
 */
function _btrServices_project_list($params) {
  $params += array('origin' => NULL, 'project' => NULL);
  $result = btr_project_list($params['origin'], $params['project']);
  drupal_json_output($result);
  drupal_exit();
}
