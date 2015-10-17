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
  $project['actions']['list'] = array(
    'help' => 'Get a list of existing projects.',
    'file' => $file,
    'callback' => '_btrServices_project_list',
    'args' => array($params),
  ) + $public_access;

  // Export a project.
  $project['actions']['export'] = array(
    'help' => 'Export a project.',
    'file' => $file,
    'callback' => '_btrServices_project_export',
    'args' => array($params),
  ) + $public_access;

  // Import project from POT file(s).
  $project['actions']['import'] = array(
    'help' => 'Import project from PO/POT file(s).',
    'file' => $file,
    'callback' => '_btrServices_project_import',
    'args' => array($params),
    'access callback' => 'user_access',
    'access arguments' => array('btranslator-vote'),
  );

  // Subscribe to a project.
  $project['actions']['subscribe'] = array(
    'help' => 'Subscribe to a project.',
    'file' => $file,
    'callback' => '_btrServices_project_subscribe',
    'args' => array($params),
  ) + $public_access;

  // Unsubscribe from a project.
  $project['actions']['unsubscribe'] = array(
    'help' => 'Unsubscribe from a project.',
    'file' => $file,
    'callback' => '_btrServices_project_unsubscribe',
    'args' => array($params),
  ) + $public_access;

  // Get the list of subscribed projects.
  $project['actions']['subscriptions'] = array(
    'help' => 'Get the list of subscribed projects.',
    'file' => $file,
    'callback' => '_btrServices_project_subscriptions',
    'args' => array($params),
  ) + $public_access;

  // Delete a project.
  $project['actions']['delete'] = array(
    'help' => 'Delete a project.',
    'file' => $file,
    'callback' => '_btrServices_project_delete',
    'args' => array($params),
  ) + $public_access;

  return $project;
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
 *   curl -k -i -X POST https://dev.btr.example.org/api/project/list
 *   curl -k -i -X POST https://dev.btr.example.org/api/project/list \
 *        -H "Content-type: application/json" \
 *        -d '{"origin": "t*"}'
 */
function _btrServices_project_list($params) {
  $params += array('origin' => NULL, 'project' => NULL);

  // Get and sanitize the parameters.
  $origin = $params['origin'];
  $project = $params['project'];
  if (!empty($origin)) {
    $origin = str_replace('*', '%', $origin);
    $origin = check_plain($origin);
  }
  if (!empty($project) && $project != '-') {
    $project = str_replace('*', '%', $project);
    $project = check_plain($project);
  }

  // Get the project list.
  $project_list = btr::project_ls($origin, $project);

  // Output it as json.
  drupal_json_output($project_list);
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
 *       The name of the project.
 *   - lng
 *       Translation to be exported.
 *   - export_mode
 *       The export mode that should be used. It can be one of:
 *       (original | most_voted | preferred).
 *        - The mode 'original' exports the translations of the
 *          original files that were imported.
 *        - The mode 'most_voted' exports the translations with the
 *          highest number of votes.
 *        - The mode 'preferred' gives precedence to the translations
 *          voted by a user or a list of users, despite the number of
 *          votes.
 *   - preferred_voters
 *       Comma separated list of usernames. Used only when export_mode
 *       is 'preferred'.
 *
 * @return
 *   Associative array containing:
 *   - messages
 *       Array of notification messages; each notification message
 *       is an array of a message and a type, where type can be one of
 *       'status', 'warning', 'error'.
 */
function _btrServices_project_export($params) {
  $params += [
    'origin' => NULL,
    'project' => NULL,
    'lng' => NULL,
    'export_mode' => NULL,
    'preferred_voters' => NULL,
  ];

  btr::schedule_project_export(
    check_plain($params['origin']),
    check_plain($params['project']),
    check_plain($params['lng']),
    check_plain($params['export_mode']),
    check_plain($params['preferred_voters'])
  );

  return ['messages' => btr::messages()];
}

/**
 * Create a custom project or update an existing one by importing PO/POT files.
 *
 * This is useful for creating custom translation projects. The PO/POT
 * files that are uploaded will be used for importing strings and
 * translations. If there are no POT files, then the PO files will be
 * used both for importing strings and for importing translations. If
 * there are POT files and PO files, their names have to match (except
 * for the extension).
 *
 * If there are several PO/POT files, upload them as an archive (tar,
 * tgz, bz2, 7z, zip).
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - origin
 *       The origin of the project that will be imported.
 *   - project
 *       The name of the project that will be imported.
 *
 * @return
 *   Associative array containing:
 *   - messages
 *       Array of notification messages; each notification message
 *       is an array of a message and a type, where type can be one of
 *       'status', 'warning', 'error'.
 */
function _btrServices_project_import($params) {
  // Get the uploaded file.
  if (!isset($_FILES['file'])) {
    return services_error('No file uploaded.', 406);
  }
  $uploaded_file = $_FILES['file'];

  // Check that a file is uploaded.
  if (!$uploaded_file['tmp_name']) {
    return services_error('File upload failed.', 406);
  }

  // Check for any other upload errors.
  if ($uploaded_file['error'] != 0) {
    return services_error('Error ' . $uploaded_file['error'] . 'happened during file upload.', 406);
  }

  // Get the parameters.
  $params += ['origin' => NULL, 'project' => NULL];
  $origin = check_plain($params['origin']);
  $project = check_plain($params['project']);

  // Check the rights for re-importing an existing project.
  if (btr::project_exists($origin, $project)) {
    $is_owner = ( btr::project_owner($origin, $project) == $GLOBALS['user']->uid );
    $can_reimport = ( $is_owner or user_access('btranslator-admin') );
    if (!$can_reimport) {
      $msg = t("The project '!project' already exists. You can re-import only your own projects.",
             ['!project' => "$origin/$project"]);
      return ['messages' => [[$msg, 'error']]];
    }
  }

  // Schedule the project import.
  btr::schedule_project_import($origin, $project, $uploaded_file);
  return ['messages' => btr::messages()];
}

/**
 * Subscribe an authenticated user to the given project.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - origin
 *       The origin of the project.
 *   - project
 *       The name of the project.
 */
function _btrServices_project_subscribe($params) {
  $params += array(
    'origin' => NULL,
    'project' => NULL,
  );
  $origin = check_plain($params['origin']);
  $project = check_plain($params['project']);

  // Check that this project exists.
  if (!btr::project_exists($origin, $project)) {
    return services_error("Project '$origin/$project' does not exist.", 406);
  };

  btr::project_subscribe($origin, $project);
}

/**
 * Unsubscribe an authenticated user from the given project.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - origin
 *       The origin of the project.
 *   - project
 *       The name of the project.
 */
function _btrServices_project_unsubscribe($params) {
  $params += array(
    'origin' => NULL,
    'project' => NULL,
  );
  $origin = check_plain($params['origin']);
  $project = check_plain($params['project']);

  // Check that this project exists.
  if (!btr::project_exists($origin, $project)) {
    return services_error("Project '$origin/$project' does not exist.", 406);
  };

  btr::project_unsubscribe($origin, $project);
}

/**
 * Return the list of projects to which the user is subscribed.
 */
function _btrServices_project_subscriptions() {
  return btr::project_subscriptions();
}

/**
 * Delete a project.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - origin
 *       The origin of the project that will be deleted.
 *   - project
 *       The name of the project that will be deleted.
 *
 * @return
 *   Associative array containing:
 *   - message
 *       Notification message, which is an array of a message and a type, where
 *       type can be one of 'status', 'warning', 'error'.
 */
function _btrServices_project_delete($params) {
  $params += array(
    'origin' => NULL,
    'project' => NULL,
  );
  $origin = check_plain($params['origin']);
  $project = check_plain($params['project']);

  // Check that this project exists.
  if (!btr::project_exists($origin, $project)) {
    $msg = t("Project '!project' does not exist.", ['!project' => "$origin/$project"]);
    return ['message' => [$msg, 'error']];
  };

  // Check the rights for deleting this project.
  $is_owner = ( btr::project_owner($origin, $project) == $GLOBALS['user']->uid );
  $can_delete = ( $is_owner or user_access('btranslator-admin') );
  if (!$can_delete) {
    $msg = t('You can delete only your own projects.');
    return ['message' => [$msg, 'error']];
  }

  // Delete the project.
  btr::project_del($origin, $project);
  $msg = t("Project '!project' deleted.", ['!project' => "$origin/$project"]);
  return ['message' => [$msg, 'status']];
}
