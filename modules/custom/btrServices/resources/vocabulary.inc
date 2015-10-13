<?php
/**
 * @file
 * Resource definition and callbacks for project.
 */

function _btrServices_vocabulary() {
  $file = array('type' => 'inc', 'module' => 'btrServices', 'name' => 'resources/vocabulary');
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

  // Add a new string to a vocabulary.
  $vocabulary['actions']['add_string'] = array(
    'help' => 'Add a new string to a vocabulary.',
    'file' => $file,
    'callback' => '_btrServices_vocabulary_add_string',
    'args' => array($params),
    'access callback' => 'user_access',
    'access arguments' => array('btranslator-suggest'),
  );

  // Delete a string from a vocabulary.
  $vocabulary['actions']['del_string'] = array(
    'help' => 'Delete a string from a vocabulary.',
    'file' => $file,
    'callback' => '_btrServices_vocabulary_del_string',
    'args' => array($params),
    'access callback' => 'user_access',
    'access arguments' => array('btranslator-suggest'),
  );

  // Import vocabulary from a text file.
  $vocabulary['actions']['import'] = array(
    'help' => 'Import vocabulary from a text file.',
    'file' => $file,
    'callback' => '_btrServices_vocabulary_import',
    'args' => array($params),
    'access callback' => 'user_access',
    'access arguments' => array('btranslator-vote'),
  );

  // Delete a vocabulary.
  $vocabulary['actions']['delete'] = array(
    'help' => 'Delete a vocabulary.',
    'file' => $file,
    'callback' => '_btrServices_vocabulary_delete',
    'args' => array($params),
  ) + $public_access;

  return $vocabulary;
}

/**
 * Add a new string to a vocabulary.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - name
 *       The name of the vocabulary.
 *   - lng
 *       The language of the vocabulary.
 *   - string
 *       String to be added.
 *   - notify (optional)
 *       If TRUE, notify translators about the new string. Default is TRUE.
 *
 * @return
 *   array('sguid' => $sguid, 'messages' => $messages)
 *   - $sguid is the ID of the new string,
 *               or NULL if no string was added
 *   - $messages is an array of notification messages; each notification
 *               message is an array of a message and a type, where
 *               type can be one of 'status', 'warning', 'error'
 */
function _btrServices_vocabulary_add_string($params) {
  // Check access permissions.
  if (!user_access('btranslator-suggest')) {
    $msg = t('No rights for contributing suggestions!');
    return ['sguid' => NULL, 'messages' => [[$msg, 'error']]];
  }
  // Check that the language matches the translation language of the user.
  $account = user_load($GLOBALS['user']->uid);
  if (!user_access('btranslator-admin') and ($lng != $account->translation_lng)) {
    $msg = t('No rights for contributing to language <strong>!lng</strong>.', ['!lng' => $lng]);
    return ['sguid' => NULL, 'messages' => [[$msg, 'error']]];
  }

  $params += array(
    'name' => NULL,
    'lng' => NULL,
    'string' => NULL,
    'notify' => TRUE,
  );
  $sguid = btr::vocabulary_string_add(
    check_plain($params['name']),
    check_plain($params['lng']),
    check_plain($params['string']),
    $GLOBALS['user']->uid,
    check_plain($params['notify'])
  );
  return ['sguid' => $sguid, 'messages' => []];
}

/**
 * Delete a string from a vocabulary.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - name
 *       The name of the vocabulary.
 *   - lng
 *       The language of the vocabulary.
 *   - sguid
 *       ID of the string to be deleted.
 *
 * @return
 *   Associative array containing:
 *   - messages
 *       Array of notification messages; each notification message
 *       is an array of a message and a type, where type can be one of
 *       'status', 'warning', 'error'.
 */
function _btrServices_vocabulary_del_string($params) {
  $params += array(
    'name' => NULL,
    'lng' => NULL,
    'sguid' => NULL,
  );
  $name = check_plain($params['name']);
  $lng = check_plain($params['lng']);
  $sguid = check_plain($params['sguid']);
  if (btr::vocabulary_string_del($name, $lng, $sguid)) {
    return ['messages' => []];
  }
  else {
    $msg = t('Insufficient permissions.');
    return ['messages' => [[$msg, 'error']]];
  };
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
 * If you want to create a vocabulary, use 'vocabulary' as the origin of the
 * project, and add the suffix '_lng' to the project name.  Use 'msgctxt
 * "project_name"' as the context of each string in the PO/POT file. Also the
 * uploaded PO file must have the same name as the project, for example
 * 'ICT_sq.po'. These restrictions are needed because vocabularies are
 * pseudo-projects (for example you can add strings to them) and certain
 * assumptions are made about them.
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
function _btrServices_vocabulary_import($params) {
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
  $params += array(
    'origin' => NULL,
    'project' => NULL,
  );
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
  };

  // Schedule the project import.
  $messages = btr::schedule_vocabulary_import($origin, $project, $uploaded_file);
  return ['messages' => $messages];
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
function _btrServices_vocabulary_delete($params) {
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
