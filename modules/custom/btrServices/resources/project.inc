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

  // Export a project.
  $translations['actions']['export'] = array(
    'help' => 'Export a project.',
    'file' => $file,
    'callback' => '_btrServices_project_export',
    'args' => array($params),
  ) + $public_access;


  // Add a new string to a project (useful for vocabularies).
  $translations['actions']['add_string'] = array(
    'help' => 'Add a new string to a project.',
    'file' => $file,
    'callback' => '_btrServices_project_add_string',
    'args' => array($params),
    'access callback' => 'user_access',
    'access arguments' => array('btranslator-import'),
  );

  // Delete a string from a project (useful for vocabularies).
  $translations['actions']['del_string'] = array(
    'help' => 'Delete a string from a project.',
    'file' => $file,
    'callback' => '_btrServices_project_del_string',
    'args' => array($params),
    'access callback' => 'user_access',
    'access arguments' => array('btranslator-admin'),
  );

  return $translations;
}

/**
 * Get a list of existing projects.
 *
 * @param $params
 *   Associative array of the POST data, which contains
 *   the parameters. These parameters can be:
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

/**
 * Export a project.
 *
 * Submit a request for exporting a project. When the request
 * is completed, the user will be notified by email.
 *
 * @param $params
 *   Associative array of the POST data, which contains
 *   the export parameters. These parameters are:
 *   - origin
 *       The origin of the project.
 *   - project
 *       The name of the project. If not given, then all the projects
 *       of the 'origin' will be exported, however only those with
 *       export access rights (usually translators) can do this.
 *       Contributors can export only a single project at a time.
 *   - export_mode
 *       The export mode that should be used. It can be one of:
 *       (most_voted | preferred_by_me | preferred_by_my_friends).
 *       Normal users can use only the default mode: most_voted.
 *       However those with export access rights (usually translators)
 *       can choose another export mode.
 *        - When the mode most_voted is used, then the translations
 *          with the highest number of votes are exported.
 *        - When the mode preferred_by_me is used, then the translations
 *          voted by the user take precedence over the other translations
 *          despite the number of votes.
 *        - When the mode preferred_by_my_friends is used, then the
 *          translations voted by any friends of the user take precedence.
 *          Friends are the users that are listed on the parameter
 *          'friends' (see below).
 *   - friends
 *       Comma separated list of usernames. Used only when export_mode
 *       is preferred_by_my_friends.
 *
 * @return
 *   Associative array containing:
 *   - messages
 *       Array of notification messages; each notification message
 *       is an array of a message and a type, where type can be one of
 *       'status', 'warning', 'error'.
 */
function _btrServices_project_export($params) {
  $params += array(
    'origin' => NULL,
    'project' => NULL,
    'export_mode' => NULL,
    'friends' => NULL,
  );
  if (empty($params['export_mode'])) {
    $params['export_mode'] = 'most_voted';
  }

  $messages = btr_project_export(
    check_plain($params['origin']),
    check_plain($params['project']),
    check_plain($params['export_mode']),
    check_plain($params['friends'])
  );

  return array('messages' => $messages);
}


/**
 * Add a new string to a project (useful for vocabularies).
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - origin
 *       Origin (category) of the project.
 *   - project
 *       Name of the project.
 *   - tplname (optional)
 *       Name of the template (POT) file.
 *   - string
 *       String to be added.
 *   - context (optional)
 *       The context of the string.
 *   - notify (optional)
 *       It TRUE, notify translators about the new string.
 *
 * @return
 *   The sguid of the new string, or NULL if such a string already exists.
 */
function _btrServices_project_add_string($params) {
  $params += array(
    'origin' => NULL,
    'project' => NULL,
    'tplname' => NULL,
    'string' => NULL,
    'context' => NULL,
    'notify' => NULL,
  );
  $sguid = btr_add_string(
    check_plain($params['origin']),
    check_plain($params['project']),
    check_plain($params['tplname']),
    check_plain($params['string']),
    check_plain($params['context']),
    check_plain($params['notify'])
  );
  return array('sguid' => $sguid);
}

/**
 * Delete a string from a project (useful for vocabularies).
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - sguid
 *       ID of the string to be deleted.
 */
function _btrServices_project_del_string($params) {
  $sguid = check_plain($params['sguid']);
  btr_del_string($sguid);
}