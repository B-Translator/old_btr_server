<?php
/**
 * @file
 * Resource definition and callbacks for translations.
 */

function _btrServices_translations() {
  $file = array('type' => 'inc', 'module' => 'btrServices', 'name' => 'resources/translations');

  // Return a string, along with its translations,
  // votes and other details.
  $translations['operations']['retrieve'] = array(
    'help' => 'Return a string, along with its translations, votes and other details.',
    'file' => $file,
    'callback' => '_btrServices_translations_retrieve',
    'args' => array(
      array(
        'name' => 'sguid',
        'optional' => FALSE,
        'source' => array('path' => 0),
        'description' => 'The string (globally unique) id.',
        'type' => 'string',
      ),
      array(
        'name' => 'lng',
        'optional' => FALSE,
        'source' => array('param' => 'lng'),
        'description' => 'The language of translations.',
        'type' => 'string',
      ),
    ),
    'access callback' => 'user_access',
    'access arguments' => array('access content'),
  );

  // Filter strings and translations
  // according to the given parameters.
  $translations['operations']['index'] = array(
    'help' => 'Index of strings and translations.',
    'file' => $file,
    'callback' => '_btrServices_translations_index',
    'args' => array(
      array(
        'name' => 'params',
        'optional' => FALSE,
        'source' => 'param',
        'description' => 'Filter parameters (lng, words, project, etc.)',
        'type' => 'array',
      ),
    ),
    'access callback' => 'user_access',
    'access arguments' => array('access content'),
  );

  // Search strings and translations using various filters.
  $translations['actions']['search'] = array(
    'help' => 'Search strings and translations.',
    'file' => $file,
    'callback' => '_btrServices_translations_search',
    'args' => array(
      array(
        'name' => 'params',
        'optional' => FALSE,
        'source' => 'data',
        'description' => 'Filters (lng, words, project, etc.)',
        'type' => 'array',
      ),
    ),
    'access callback' => 'user_access',
    'access arguments' => array('access content'),
  );

  // Get the sguid of a random string according to the target.
  $translations['actions']['get_random_sguid'] = array(
    'help' => 'Get the sguid of a random string according to the target, which can be: next|translated|untranslated.',
    'file' => $file,
    'callback' => '_btrServices_translations_get_random_sguid',
    'args' => array(
      array(
        'name' => 'params',
        'optional' => FALSE,
        'source' => 'data',
        'description' => 'Assoc array containing the target.',
        'type' => 'array',
      ),
    ),
    'access callback' => 'user_access',
    'access arguments' => array('access content'),
  );

  // Get a string, along with its translations, votes and other details.
  $translations['actions']['get'] = array(
    'help' => 'Return a string, along with its translations, votes and other details.',
    'file' => $file,
    'callback' => '_btrServices_translations_get',
    'args' => array(
      array(
        'name' => 'params',
        'optional' => FALSE,
        'source' => 'data',
        'description' => 'Parameters (sguid and lng).',
        'type' => 'array',
      ),
    ),
    'access callback' => 'user_access',
    'access arguments' => array('access content'),
  );

  // Add a new translation to a source string.
  $translations['actions']['add'] = array(
    'help' => 'Add a new translation to a source string.',
    'file' => $file,
    'callback' => '_btrServices_translations_add',
    'args' => array(
      array(
        'name' => 'params',
        'optional' => FALSE,
        'source' => 'data',
        'description' => 'Translation data (sguid, lng, translation).',
        'type' => 'array',
      ),
    ),
    'access callback' => 'user_access',
    'access arguments' => array('btranslator-suggest'),
  );

  // Add a vote for a translation.
  $translations['actions']['vote'] = array(
    'help' => 'Add a vote for a translation.',
    'file' => $file,
    'callback' => '_btrServices_translations_vote',
    'args' => array(
      array(
        'name' => 'params',
        'optional' => FALSE,
        'source' => 'data',
        'description' => 'Translation to be voted (tguid).',
        'type' => 'array',
      ),
    ),
    'access callback' => 'user_access',
    'access arguments' => array('btranslator-vote'),
  );

  // Delete a translation.
  $translations['actions']['del'] = array(
    'help' => 'Delete a translation.',
    'file' => $file,
    'callback' => '_btrServices_translations_del',
    'args' => array(
      array(
        'name' => 'params',
        'optional' => FALSE,
        'source' => 'data',
        'description' => 'Translation (tguid) to be deleted.',
        'type' => 'array',
      ),
    ),
    'access callback' => 'user_access',
    'access arguments' => array('btranslator-suggest'),
  );

  // Delete a vote from a translation.
  $translations['actions']['del_vote'] = array(
    'help' => 'Delete a vote from a translation.',
    'file' => $file,
    'callback' => '_btrServices_translations_del_vote',
    'args' => array(
      array(
        'name' => 'params',
        'optional' => FALSE,
        'source' => 'data',
        'description' => 'Translation (tguid) to be un-voted.',
        'type' => 'array',
      ),
    ),
    'access callback' => 'user_access',
    'access arguments' => array('btranslator-vote'),
  );

  // Submit multiple actions at once.
  $translations['actions']['submit'] = array(
    'help' => 'Submit multiple actions at once.',
    'file' => $file,
    'callback' => '_btrServices_translations_submit',
    'args' => array(
      array(
        'name' => 'params',
        'optional' => FALSE,
        'source' => 'data',
        'description' => 'Array of actions to be executed.',
        'type' => 'array',
      ),
    ),
    'access callback' => 'user_access',
    'access arguments' => array('btranslator-vote'),
  );

  // Import translations from PO files.
  $translations['actions']['import'] = array(
    'help' => 'Import translations from PO files.',
    'file' => $file,
    'callback' => '_btrServices_translations_import',
    'args' => array(
      array(
        'name' => 'params',
        'optional' => FALSE,
        'source' => 'data',
        'description' => 'Assoc array of parameters.',
        'type' => 'array',
      ),
    ),
    'access callback' => 'user_access',
    'access arguments' => array('btranslator-import'),
  );

  return $translations;
}

/**
 * Get a string, along with its translations votes and other details.
 *
 * @param $sguid
 *   The string (globally unique) id, calculated
 *   as: $sguid = sha1($string . $context)
 *   It can also be: next|translated|untranslated
 *
 * @param $lng
 *   The language of translations, like: 'fr', 'sq', etc.
 *
 * @return
 *   A nested structure containing the string, its
 *   translations, votes, etc.
 *
 * @example
 *   curl -k -i \
 *     'https://dev.l10n.org.xx/public/btr/translations/next?lng=sq'
 */
function _btrServices_translations_retrieve($sguid, $lng) {
  $strings = _btrServices_translations_get(array(
               'sguid' => $sguid,
               'lng' => $lng,
             ));
  return $strings;
}


/**
 * Filter strings and translations according to the given parameters.
 *
 * This provides the same functionality and has the same parameters
 * as the operation 'translations/search'. The only difference is that
 * the parameters are provided as a GET request (in the URL), whereas
 * the parameters of 'translations/search' are provided as a POST
 * request. Sometimes this may be more convenient.
 *
 * @param $params
 *   Parameters for filtering the strings etc.
 *
 * @return
 *   Array containing search results, along with the filters
 *   and the pager info (same as for the search case).
 *
 * @example
 *   curl -k -i -H 'Accept: application/json' \
 *     'https://dev.l10n.org.xx/public/btr/translations?lng=sq&words=file'
 */
function _btrServices_translations_index($params) {
  return _btrServices_translations_search($params);
}


/**
 * Search strings and translations using various filters.
 *
 * @param $params
 *   Associative array of the POST data, which contains
 *   the filter parameters. These parameters can be:
 *   - lng
 *       The language of translations.
 *   - limit
 *       The number of results to be returned (min: 5, max: 50).
 *   - words
 *       Words to be searched for.
 *   - sguid
 *       If the 'words' is empty and there is a 'sguid' then the
 *       words of this string are used for searching.
 *   - mode
 *       Search mode. Can be one of:
 *       - natural-strings       Natural search on strings (default).
 *       - natural-translations  Natural search on translations.
 *       - boolean-strings       Boolean search on strings.
 *       - boolean-translations  Boolean search on translations.
 *   - page
 *       Page of results to be displayed.
 *   - project
 *       Limit search only to this project
 *   - origin
 *       Limit search only to the projects of this origin.
 *   - only_mine (boolean)
 *       Limit search only to the strings touched (translated or voted)
 *       by the current user.
 *   - translated_by
 *       Limit search by the author of translations
 *       (can be used only by admins).
 *   - voted_by
 *       Limit search by a voter (can be used only by admins).
 *   - date_filter
 *       Which date to filter (used only by admins). Can be one of:
 *       - strings       Filter Strings By Date
 *       - translations  Filter Translations By Date (default)
 *       - votes         Filter Votes By Date
 *   - from_date
 *   - to_date
 *
 * @return
 *   Array containing search results, along with the filters
 *   and the pager info. Each result is a nested structure
 *   containing the string, its translations, votes, etc.
 */
function _btrServices_translations_search($params) {
  // Get and check the parameter 'lng'.
  $lng = $params['lng'];
  $arr_langs = array_keys(btr_get_languages());
  if (!in_array($lng, $arr_langs)) {
    return services_error('Language missing or not supported.', 406);
  }

  // The PagerDefault of Drupal7 queries gets the current page
  // from $_GET['page']. This is a trick to make it work.
  // See: https://api.drupal.org/api/drupal/includes%21pager.inc/function/pager_find_page/7
  $_GET['page'] = isset($params['page']) ? (int)trim($params['page']) : 0;

  // Build the filter and the query, and then get the strings.
  $filter = btr_build_search_filter($params);
  $query = btr_build_search_query($filter);
  $strings = ($query===NULL ? array() : btr_get_query_strings($query, $lng));

  // The PagerDefault of Drupal7 defines the pager variables
  // as global variables (these variables are later used by theme_pager).
  // See: https://api.drupal.org/api/drupal/includes!pager.inc/function/pager_default_initialize/7
  $pager = array(
    'number_of_items' => $GLOBALS['pager_total_items'][0],
    'items_per_page' => $GLOBALS['pager_limits'][0],
    'number_of_pages' => $GLOBALS['pager_total'][0],
    'current_page' => $GLOBALS['pager_page_array'][0],
  );

  return array(
    'filter' => $filter,
    'pager' => $pager,
    'strings' => $strings,
  );
}


/**
 * Get the sguid of a random string according to the target.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - target
 *       Can be one of: next|translated|untranslated
 *   - lng
 *       Code of the language (required for translated and untranslated)
 *   - last_sguid (optional)
 *       If provided, restricts the pool of selection the project(s)
 *       of the last reviewed sguid.
 *
 * @return
 *   Associative array containing:
 *   - sguid
 *       ID of a random string, or the target itself
 *       if it is different from next|translated|untranslated
 */
function _btrServices_translations_get_random_sguid($params) {
  $projects = NULL;
  if (isset($params['last_sguid'])) {
    $projects = btr_get_projects_of_sguid($params['last_sguid']);
  }
  $target = $params['target'];
  $lng = $params['lng'];
  list($sguid, $messages) = btr_get_random_sguid($target, $lng, $projects);

  return array(
    'sguid' => $sguid,
    'messages' => $messages,
  );
}


/**
 * Get a string, along with its translations votes and other details.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - sguid
 *       The string (globally unique) id, calculated
 *       as: $sguid = sha1($string . $context)
 *       It can also be: next|translated|untranslated
 *   - lng
 *       The language of translations, like: 'fr', 'sq', etc.
 *
 * @return
 *   A nested structure containing the string, its
 *   translations, votes, etc.
 *
 * @example
 *   curl -k -i -H 'Content-type: application/json' \
 *     -X POST https://dev.l10n.org.xx/public/btr/translations/get
 *     -d '{"lng": "sq"}'
 */
function _btrServices_translations_get($params) {
  $lng = $params['lng'];
  $arr_langs = array_keys(btr_get_languages());
  if (!in_array($lng, $arr_langs)) {
    return services_error('Language missing or not supported.', 406);
  }

  $sguid = $params['sguid'];
  $messages = array();
  if (in_array($sguid, array('next', 'translated', 'untranslated'))) {
    list($sguid, $messages) = btr_get_random_sguid($sguid, $lng);
  }

  $strings = btr_get_strings(array($sguid), $lng);
  $string = empty($strings) ? NULL : $strings[0];

  return array(
    'string' => $string,
    'messages' => $messages,
  );
}

/**
 * Add a new translation to a source string.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - sguid
 *       The string ID for which a new translation should be added.
 *   - lng
 *       The language (code) of the new translation.
 *   - translation
 *       The new translation as a string. If the string has plural
 *       version(s) as well, they are concatenated with NULL bytes ("\0")
 *       between them.
 *
 * @return
 *   Associative array containing:
 *   - tguid
 *       ID of the new translation, or NULL if no translation was added.
 *   - messages
 *       Array of notification messages; each notification message
 *       is an array of a message and a type, where type can be one of
 *       'status', 'warning', 'error'.
 */
function _btrServices_translations_add($params) {
  // get parameters and validate them
  $sguid = $params['sguid'];
  $translation = $params['translation'];
  $lng = $params['lng'];
  $arr_langs = array_keys(btr_get_languages());
  if (!in_array($lng, $arr_langs)) {
    return services_error('Language missing or not supported.', 406);
  }

  list($tguid, $messages) = btr_add_translation($sguid, $lng, $translation);
  return array(
    'tguid' => $tguid,
    'messages' => $messages
  );
}


/**
 * Add a vote for the given translation.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - tguid
 *       ID of the translation
 *
 * @return
 *   Associative array containing:
 *   - vid
 *       ID of the new vote, or NULL
 *   - messages
 *       Array of notification messages; each notification message
 *       is an array of a message and a type, where type can be one of
 *       'status', 'warning', 'error'.
 */
function _btrServices_translations_vote($params) {
  $tguid = $params['tguid'];
  list($vid, $messages) = btr_add_vote($tguid);
  return array(
    'vid' => $vid,
    'messages' => $messages
  );
}

/**
 * Delete a translation.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - tguid
 *       ID of the translation
 *
 * @return
 *   Associative array containing:
 *   - messages
 *       Array of notification messages; each notification message
 *       is an array of a message and a type, where type can be one of
 *       'status', 'warning', 'error'.
 */
function _btrServices_translations_del($params) {
  $tguid = $params['tguid'];
  $messages = btr_del_translation($tguid);
  return array(
    'messages' => $messages
  );
}

/**
 * Delete a vote from the given translation.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - tguid
 *       ID of the translation
 *
 * @return
 *   Associative array containing:
 *   - messages
 *       Array of notification messages; each notification message
 *       is an array of a message and a type, where type can be one of
 *       'status', 'warning', 'error'.
 */
function _btrServices_translations_del_vote($params) {
  $tguid = $params['tguid'];
  $messages = btr_del_vote($tguid);
  return array(
    'messages' => $messages
  );
}

/**
 * Submit multiple actions at once.
 *
 * @param $params
 *   Array of the POST data, which contains an item for each action.
 *   Each action is an associated array that contains the items:
 *   - action
 *       The action to be done (add, vote, del, del_vote)
 *   - params
 *       Associative array of the needed parameters for this action.
 *
 * @return
 *   Associative array containing:
 *   - messages
 *       Array of notification messages; each notification message
 *       is an array of a message and a type, where type can be one of
 *       'status', 'warning', 'error'.
 */
function _btrServices_translations_submit($params) {
  $messages = array();
  $nr_votes = $nr_suggestions = $nr_deletions = 0;
  foreach ($params as $item) {
    switch ($item['action']) {
    case 'add':
      $result = _btrServices_translations_add($item['params']);
      if ($result['tguid'] != NULL)  $nr_suggestions++;
      $messages += $result['messages'];
      break;

    case 'vote':
      $result = _btrServices_translations_vote($item['params']);
      if ($result['vid'] != NULL)  $nr_votes++;
      $messages += $result['messages'];
      break;

    case 'del':
      $result = _btrServices_translations_del($item['params']);
      if (sizeof($result['messages'])==0) {
	$nr_deletions++;
      }
      else {
	$messages += $result['messages'];
      }
      break;

    case 'del_vote':
      $result = _btrServices_translations_del_vote($item['params']);
      $messages += $result['messages'];
      break;

    default:
      $msg = t('Action !action is not supported!',
	       array('!action' => $item['action']));
      $messages[] = array($msg, 'error');
      break;
    }
  }

  if ($nr_suggestions > 0) {
    $msg = format_plural($nr_suggestions, '1 suggestion saved', '@count suggestions saved');
    $messages[] = array($msg, 'status');
  }
  if ($nr_votes > 0) {
    $msg = format_plural($nr_votes, '1 vote saved', '@count votes saved');
    $messages[] = array($msg, 'status');
  }
  if ($nr_deletions > 0) {
    $msg = format_plural($nr_deletions, '1 translation deleted', '@count translations deleted');
    $messages[] = array($msg, 'status');
  }

  return array(
    'messages' => $messages
  );
}

/**
 * Bulk import of translations from PO files.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - lng
 *       Language of translations.
 *
 * @return
 *   Associative array containing:
 *   - messages
 *       Array of notification messages; each notification message
 *       is an array of a message and a type, where type can be one of
 *       'status', 'warning', 'error'.
 */
function _btrServices_translations_import($params) {
  // Check access permissions.
  if (!user_access('btranslator-suggest')) {
    $msg = t('You do not have enough rights for submitting translations!');
    return array('messages' => array(array($msg, 'error')));
  }

  // Get and check the parameter 'lng'.
  $lng = $params['lng'];
  $arr_langs = array_keys(btr_get_languages());
  if (!in_array($lng, $arr_langs)) {
    return services_error('Language missing or not supported.', 406);
  }

  // Make sure that the current user can make
  // translations for the given language.
  $user = user_load($GLOBALS['user']->uid);
  if ($lng != $user->translation_lng) {
    $msg = t('You cannot submit translations for the language !lng', array('!lng' => $lng));
    return array('messages' => array(array($msg, 'error')));
  }

  // Get the parameters.
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

  // Check the extension of the uploaded file.
  $extensions = 'po tar gz tgz bz2 xz 7z zip';
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
    'lng' => $lng,
  );
  btr_queue('import_translations', array($queue_params));

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
  $msg = t("Import of the file '!filename' is scheduled. You will be notified by email when it is done.",
         array('!filename' => $file->filename));
  return array('messages' => array(array($msg, 'status')));
}
