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

  // Import project from POT file(s).
  $translations['actions']['import'] = array(
    'help' => 'Import project from PO/POT file(s).',
    'file' => $file,
    'callback' => '_btrServices_project_import',
    'args' => array($params),
    'access callback' => 'user_access',
    'access arguments' => array('btranslator-import'),
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
 *   curl -k -i -X POST https://dev.btr.example.org/public/btr/project/list
 *   curl -k -i -X POST https://dev.btr.example.org/public/btr/project/list \
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
  $project_list = btr::project_list($origin, $project);

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
  $params += array(
    'origin' => NULL,
    'project' => NULL,
    'lng' => NULL,
    'export_mode' => NULL,
    'preferred_voters' => NULL,
  );
  if (empty($params['export_mode'])) {
    $params['export_mode'] = 'most_voted';
  }

  $messages = btrCore_schedule_project_export(
    check_plain($params['origin']),
    check_plain($params['project']),
    check_plain($params['lng']),
    check_plain($params['export_mode']),
    check_plain($params['preferred_voters'])
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
 * If you want to create a vocabulary, use 'vocabulary' as the origin
 * of the project, and add the suffix '_lng' to the project name. Also
 * use 'msgctxt "vocabulary"' as the context of each string in the
 * PO/POT file.
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
  // Check access permissions.
  if (!user_access('btranslator-import')) {
    $msg = t('You do not have enough rights for importing projects!');
    return array('messages' => array(array($msg, 'error')));
  }

  // Get the parameters.
  if (!isset($_FILES['file'])) {
    return services_error('No file uploaded.', 406);
  }
  $uploaded_file = $_FILES['file'];
  $origin = check_plain($params['origin']);
  $project = check_plain($params['project']);

  // Check that the given project does not belong to another user.
  $query = "SELECT uid FROM {btr_projects} WHERE pguid = :pguid";
  $args = array(':pguid' => sha1($origin . $project));
  $uid = btr_query($query, $args)->fetchField();
  if ($uid && ($uid != $GLOBALS['user']->uid)) {
    $msg = t("There is already a project '!project' created by another user! Please choose another project name.", array('!project' => "$origin/$project"));
    return array('messages' => array(array($msg, 'error')));
  }

  // Check that a file is uploaded.
  if (!$uploaded_file['tmp_name']) {
    return services_error('File upload failed.', 406);
  }

  // Check for any other upload errors.
  if ($uploaded_file['error'] != 0) {
    return services_error('Error ' . $uploaded_file['error'] . 'happened during file upload.', 406);
  }

  // Check the extension of the uploaded file.
  $extensions = 'pot po tar gz tgz bz2 xz 7z zip';
  $regex = '/\.(' . preg_replace('/ +/', '|', preg_quote($extensions)) . ')$/i';
  if (!preg_match($regex, $uploaded_file['name'])) {
    $msg = t('Only files with the following extensions are allowed: %files-allowed.',
           array('%files-allowed' => $extensions));
    return array('messages' => array(array($msg, 'error')));
  }

  // Move the uploaded file to 'private://' (/var/www/uploads/).
  $file_uri = 'private://' . $uploaded_file['name'];
  if (!drupal_move_uploaded_file($uploaded_file['tmp_name'], $file_uri)) {
    $msg = array(t('Failed to move uploaded file.'), 'error');
    return array('messages' => array($msg));
  }

  // Save the file data to the DB.
  $file = new stdClass();
  $file->uid = $GLOBALS['user']->uid;
  $file->status = FILE_STATUS_PERMANENT;
  $file->filename = trim(drupal_basename($uploaded_file['name']), '.');
  $file->uri = $file_uri;
  $file->filemime = file_get_mimetype($file->filename);
  $file->filesize = $uploaded_file['size'];
  try {
    $file = file_save($file);
    $messages = array();
  }
  catch (Exception $e) {
    $msg = array($e->getMessage(), 'error');
    return array('messages' => array($msg));
  }

  // Schedule the import.
  $queue_params = array(
    'uid' => $GLOBALS['user']->uid,
    'fid' => $file->fid,
    'origin' => $origin,
    'project' => $project,
  );
  btr_queue('import_project', array($queue_params));

  // Schedule a notification to the admin.
  // TODO: Send this notification to the project admin.
  $notify_admin = variable_get('btr_import_notify_admin', TRUE);
  if ($notify_admin) {
    $queue_params['type'] = 'notify-admin-on-import-request';
    $queue_params['recipient'] = user_load(1)->mail;
    $queue_params['username'] = $GLOBALS['user']->name;
    $queue_params['filename'] = $file->filename;
    btr_queue_notifications(array($params));
  }

  // Return a notification message.
  $msg = t("Import of the project '!project' is scheduled. You will be notified by email when it is done.",
         array('!project' => $origin . '/' . $project));
  return array('messages' => array(array($msg, 'status')));
}
