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
    'help' => 'Get the sguid of a random string according to the target, which can be: random|translated|untranslated.',
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

  // Import translations and votes from PO files.
  $translations['actions']['import'] = array(
    'help' => 'Import translations and votes from PO files.',
    'file' => $file,
    'callback' => '_btrServices_vote_import',
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
    'access arguments' => array('btranslator-vote'),
  );

  return $translations;
}

/**
 * Get a string, along with its translations votes and other details.
 *
 * @param $sguid
 *   The string (globally unique) id, calculated
 *   as: $sguid = sha1($string . $context)
 *   It can also be: random|translated|untranslated
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
 *     'https://dev.btr.example.org/api/translations/random?lng=sq'
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
 *     'https://dev.btr.example.org/api/translations?lng=sq&words=file'
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
 *   - list_mode
 *       Used when listing the strings of a project.
 *       Can be one of: 'all', 'translated', 'untranslated'
 *
 * @return
 *   Array containing search results, along with the filters
 *   and the pager info. Each result is a nested structure
 *   containing the string, its translations, votes, etc.
 */
function _btrServices_translations_search($params) {
  // Get and check the parameter 'lng'.
  $lng = $params['lng'];
  if (!in_array($lng, btr::languages_get())) {
    return services_error('Language missing or not supported.', 406);
  }

  // The PagerDefault of Drupal7 queries gets the current page
  // from $_GET['page']. This is a trick to make it work.
  // See: https://api.drupal.org/api/drupal/includes%21pager.inc/function/pager_find_page/7
  $_GET['page'] = isset($params['page']) ? (int)trim($params['page']) : 0;

  // Build the filter and the query, and then get the strings.
  $filter = btr::search_build_filter($params);
  $query = btr::search_build_query($filter);
  $strings = ($query===NULL ? array() : btr::string_details($query, $lng));

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
 *       Can be one of: random|translated|untranslated
 *   - lng
 *       Code of the language (required for translated and untranslated)
 *   - scope (optional)
 *       If provided, restricts the pool of selection to the given
 *       list of project. It is a space separated list of origin/project
 *       like this: 'origin1/project1 origin2 origin1/project2'
 *
 * @return
 *   Associative array containing:
 *   - sguid
 *       ID of a random string, or the target itself
 *       if it is different from random|translated|untranslated
 */
function _btrServices_translations_get_random_sguid($params) {
  $projects = NULL;
  if (isset($params['scope'])) {
    $projects = array();
    $scope = preg_replace('/\s+/', ' ', trim($params['scope']));
    $arr = explode(' ', $scope);
    foreach ($arr as $proj) {
      $projects[] = $proj;
    }
  }
  $target = $params['target'];
  $lng = $params['lng'];
  $sguid = btr::sguid_get($target, $lng, $projects);

  return [ 'sguid' => $sguid ];
}


/**
 * Get a string, along with its translations votes and other details.
 *
 * @param $params
 *   Associative array of the POST data, which contains:
 *   - sguid
 *       The string (globally unique) id, calculated
 *       as: $sguid = sha1($string . $context)
 *       It can also be: random|translated|untranslated
 *   - lng
 *       The language of translations, like: 'fr', 'sq', etc.
 *
 * @return
 *   Associative array comtaining:
 *    - sguid
 *        A nested structure containing the string, its
 *        translations, votes, etc.
 *
 * @example
 *   curl -k -i -H 'Content-type: application/json' \
 *     -X POST https://dev.btr.example.org/api/translations/get
 *     -d '{"lng": "sq"}'
 */
function _btrServices_translations_get($params) {
  $lng = $params['lng'];
  if (!in_array($lng, btr::languages_get())) {
    return services_error('Language missing or not supported.', 406);
  }

  $sguid = $params['sguid'];
  if (in_array($sguid, ['random', 'translated', 'untranslated'])) {
    $sguid = btr::sguid_get($sguid, $lng);
  }

  $strings = btr::string_load([$sguid], $lng);
  $string = empty($strings) ? NULL : $strings[0];

  return [ 'string' => $string ];
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
  if (!in_array($lng, btr::languages_get())) {
    return services_error(t('Language missing or not supported.'), 406);
  }

  // Check access permissions.
  if (!user_access('btranslator-suggest')) {
    $msg = t('No rights for contributing suggestions!');
    return ['tguid' => NULL, 'messages' => [[$msg, 'error']]];
  }
  // Check that the language matches the translation language of the user.
  $account = user_load($GLOBALS['user']->uid);
  if (!user_access('btranslator-admin') and ($lng != $account->translation_lng)) {
    $msg = t('No rights for contributing to language <strong>!lng</strong>.', ['!lng' => $lng]);
    return ['tguid' => NULL, 'messages' => [[$msg, 'error']]];
  }

  // Add the translation.
  $tguid = btr::translation_add($sguid, $lng, $translation);
  return ['tguid' => $tguid, 'messages' => btr::messages()];
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

  // Check access permissions.
  if (!user_access('btranslator-vote')) {
    $msg = t('No rights for submitting votes!');
    return ['vid' => NULL, 'messages' => [[$msg, 'error']]];
  }

  // Add the vote.
  $vid = btr::vote_add($tguid);
  return ['vid' => $vid, 'messages' => btr::messages()];
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
  btr::translation_del($tguid);
  return ['messages' => btr::messages()];
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
  btr::vote_del($tguid);
  return ['messages' => btr::messages()];
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
  $nr_votes = $nr_suggestions = $nr_deletions = 0;
  foreach ($params as $item) {
    $action = $item['action'];
    if (!$action) continue;
    switch ($action) {
    case 'add':
      $result = _btrServices_translations_add($item['params']);
      if ($result['tguid'] != NULL)  $nr_suggestions++;
      btr::messages($result['messages']);
      break;

    case 'vote':
      $result = _btrServices_translations_vote($item['params']);
      if ($result['vid'] != NULL)  $nr_votes++;
      btr::messages($result['messages']);
      break;

    case 'del':
      $result = _btrServices_translations_del($item['params']);
      if (sizeof($result['messages'])==0) {
        $nr_deletions++;
      }
      else {
        btr::messages($result['messages']);
      }
      break;

    case 'del_vote':
      $result = _btrServices_translations_del_vote($item['params']);
      btr::messages($result['messages']);
      break;

    default:
      $msg = t('Action !action is not supported!', ['!action' => $action]);
      btr::messages($msg, 'error');
      break;
    }
  }

  if ($nr_suggestions > 0) {
    $msg = format_plural($nr_suggestions, '1 suggestion saved', '@count suggestions saved');
    btr::messages($msg);
  }
  if ($nr_votes > 0) {
    $msg = format_plural($nr_votes, '1 vote saved', '@count votes saved');
    btr::messages($msg);
  }
  if ($nr_deletions > 0) {
    $msg = format_plural($nr_deletions, '1 translation deleted', '@count translations deleted');
    btr::messages($msg);
  }

  return ['messages' => btr::messages()];
}

/**
 * Bulk import of translations and votes from PO files.
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
function _btrServices_vote_import($params) {
  // Get and check the parameter 'lng'.
  $lng = $params['lng'];
  if (!in_array($lng, btr::languages_get())) {
    return services_error('Language missing or not supported.', 406);
  }

  // Make sure that the current user can make
  // translations for the given language.
  $user = user_load($GLOBALS['user']->uid);
  if ($lng != $user->translation_lng) {
    $msg = t('No rights for contributing to language <strong>!lng</strong>.', ['!lng' => $lng]);
    return ['messages' => [[$msg, 'error']]];
  }

  // Check access permissions.
  if (!user_access('btranslator-vote')) {
    $msg = t('No rights for submitting votes!');
    return ['messages' => [[$msg, 'error']]];
  }
  if (!user_access('btranslator-suggest')) {
    $msg = t('No rights for submitting translations!');
    return ['messages' => [[$msg, 'error']]];
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
           ['%files-allowed' => $extensions]);
    return ['messages' => [[$msg, 'error']]];
  }

  // Move the uploaded file to 'private://' (/var/www/uploads/).
  $file_uri = 'private://' . $uploaded_file['name'];
  if (!drupal_move_uploaded_file($uploaded_file['tmp_name'], $file_uri)) {
    $msg = [t('Failed to move uploaded file.'), 'error'];
    return ['messages' => [$msg]];
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
  }
  catch (Exception $e) {
    $msg = [$e->getMessage(), 'error'];
    return ['messages' => [$msg]];
  }

  // Schedule the import.
  $queue_params = [
    'uid' => $GLOBALS['user']->uid,
    'fid' => $file->fid,
    'lng' => $lng,
  ];
  btr::queue('import_translations', array($queue_params));

  // Return a notification message.
  $msg = t("Import of the file '!filename' is scheduled. You will be notified by email when it is done.",
         ['!filename' => $file->filename]);
  return ['messages' => [[$msg, 'status']]];
}
