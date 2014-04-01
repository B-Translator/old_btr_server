<?php

/**
 * @file
 * Functions related to the filter form
 * of the translations/search interface.
 */

/**
 * Get the search parameters from the GET request,
 * which is like: translations/search?lng=fr&words=xyz&limit=10
 */
function btrClient_get_search_params() {
  //get a copy of the request parameters
  $request = $_GET;

  // If the search filter is empty, try to search for strings
  // similar to the last one that was reviewed.
  if (!isset($request['lng']) and isset($_SESSION['btrClient']['last_sguid'])) {
    $request['lng'] = variable_get('btrClient_translation_lng', 'fr');
    $params['sguid'] = $_SESSION['btrClient']['last_sguid'];
  }

  //get and check the language
  $lng = isset($request['lng']) ? trim($request['lng']) : '';
  $languages = btrClient_get_languages();
  $lng_codes = array_keys($languages);
  $params['lng'] = in_array($lng, $lng_codes) ? $lng : 'fr';

  //number of results to be displayed
  if (isset($request['limit'])) {
    $limit = (int)trim($request['limit']);
    list($limit_options, $default_limit) = _btrClient_get_filter_options('limit');
    $params['limit'] = in_array($limit, $limit_options) ? $limit : $default_limit;
  }
  //page of results to be displayed
  if (isset($request['page'])) {
    $params['page'] = (int)trim($request['page']);
  }

  //search can be done either by similarity of l10n strings (natural search),
  //or by matching words according to a certain logic (boolean search);
  //search can be performed either on l10n strings or on the translations
  if (isset($request['mode'])) {
    $mode = $request['mode'];
    list($search_mode_options, $default_search_mode) = _btrClient_get_filter_options('mode');
    $params['mode'] = in_array($mode, $search_mode_options) ? $mode : $default_search_mode;
  }
  if (isset($request['words'])) {
    $params['words'] = $request['words'];
  }

  //searching can be limited only to certain projects and/or origins
  if (isset($request['project'])) {
    $params['project'] = trim($request['project']);
  }
  if (isset($request['origin'])) {
  $params['origin'] = trim($request['origin']);
  }

  //limit search only to the strings touched (translated or voted)
  //by the current user
  if (isset($request['only_mine']) && (int)$request['only_mine']) {
    $params['only_mine'] = 1;
  }

  //limit search by the editing users (used by admins)
  if (isset($request['translated_by'])) {
    $params['translated_by'] = trim($request['translated_by']);
  }
  if (isset($request['voted_by'])) {
    $params['voted_by'] = trim($request['voted_by']);
  }

  //limit by date of string, translation or voting (used by admins)
  if (isset($request['date_filter'])) {
    $date_filter = trim($request['date_filter']);
    list($date_filter_options, $default_date_filter) = _btrClient_get_filter_options('date_filter');
    $params['date_filter'] = in_array($date_filter, $date_filter_options) ? $date_filter : $default_date_filter;
  }

  //from_date
  if (isset($request['from_date'])) {
    $from_date = trim($request['from_date']);
    if ($from_date != '') {
      $from_date = date('Y-m-d H:i:s', strtotime($from_date));
      $from_date = str_replace(' 00:00:00', '', $from_date);
    }
    $params['from_date'] = $from_date;
  }

  //to_date
  if (isset($request['to_date'])) {
    $to_date = trim($request['to_date']);
    if ($to_date != '') {
      $to_date = date('Y-m-d H:i:s', strtotime($to_date));
      $to_date = str_replace(' 00:00:00', '', $to_date);
    }
    $params['to_date'] = $to_date;
  }

  return $params;
}

/**
 * Submission handler for filtering form.
 */
function btrClient_filter_form_submit($form, &$form_state) {

  //dpm($form_state['values']);  //debug

  if ($form_state['values']['op'] == t('Reset')) {
    // Just go with the redirection flow => removes URL params.
    return;
  }

  if ($form_state['values']['op'] == t('Filter')) {
    // Redirect (with a GET request) keeping the relevant filters intact in the URL.
    $form_state['redirect'] = array(
      $_GET['q'],
      array('query' => btrClient_get_query_values($form_state['values']))
    );
    return;
  }
}

/**
 * Converts the array of form values into a suitable query (for redirect).
 * All non-string values are converted to string representations.
 * If a form value is equal to the default value, it is removed (unset) from the array.
 */
function btrClient_get_query_values($form_values) {

  $query = array();

  //lng
  $languages = btrClient_get_languages();
  $lng_codes = array_keys($languages);
  $lng = trim($form_values['lng']);
  if (in_array($lng, $lng_codes))
    $query['lng'] = $lng;

  //package, project, release
  if (trim($form_values['project']) != '' )
    $query['project'] = $form_values['project'];
  if (trim($form_values['origin']) != '' )
    $query['origin'] = $form_values['origin'];

  if (user_is_logged_in()) {
    //only_mine
    if ($form_values['only_mine'] == 1) {
      $query['only_mine'] = '1';
    }
    else {
      //translated_by, voted_by
      if (trim($form_values['translated_by']) != '' )
        $query['translated_by'] = $form_values['translated_by'];
      if (trim($form_values['voted_by']) != '' )
        $query['voted_by'] = $form_values['voted_by'];
    }

    //date_filter
    list($date_filter_options, $default_date_filter) = _btrClient_get_filter_options('date_filter');
    if ( in_array($form_values['date_filter'], $date_filter_options) && $form_values['date_filter'] != $default_date_filter ) {
      $query['date_filter'] = $form_values['date_filter'];
    }

    //from_date
    if (trim($form_values['from_date']) != '' )
      $query['from_date'] = $form_values['from_date'];

    //to_date
    if (trim($form_values['to_date']) != '' )
      $query['to_date'] = $form_values['to_date'];
  }

  //limit
  list($limit_options, $default_limit) = _btrClient_get_filter_options('limit');
  if ( in_array($form_values['limit'], $limit_options) && $form_values['limit'] != $default_limit ) {
    $query['limit'] = $form_values['limit'];
  }

  //search mode and words
  list($search_mode_options, $default_search_mode) = _btrClient_get_filter_options('mode');
  if ( in_array($form_values['mode'], $search_mode_options) && $form_values['mode'] != $default_search_mode ) {
    $query['mode'] = $form_values['mode'];
  }
  if (trim($form_values['words']) != '' )
    $query['words'] = $form_values['words'];

  return $query;
}

/**
 * Translation form filter.
 *
 * @param $filters
 *   Array of filter options.
 */
function btrClient_filter_form($form, &$form_state, $filter) {

  //if the form has no values yet (either it is the first time that
  //the form is opened, or we have a get request), we set the values
  //of the form according to the $filter values
  if (empty($form_state['values'])) {
    $form_state['values'] = $filter;
  }

  $form = array(
    //'#prefix' => '<div class="btr-ui-filter clear-block">',
    '#prefix' => '<div class="clear-block">',
    '#suffix' => '</div>',
  );

  // Add form fields: lng, mode, words, limit
  _btrClient_filter_form_basic_search($form, $form_state);

  // Add form fieldset advanced_search/projects, with the fields: project and origin.
  _btrClient_filter_form_advanced_search($form, $form_state);

  // Search by author and serach by date
  // are available only to logged in users.
  if (user_is_logged_in()) {
    // Add fieldset advanced_search/author,
    // with fields: only_mine, translated_by, voted_by
    _btrClient_filter_form_author($form, $form_state);

    // Add fieldset advanced_search/date,
    // with fields: date_filter, from_date, to_date
    _btrClient_filter_form_date($form, $form_state);
  }

  $form['buttons'] = array(
    //'#prefix' => '<div class="filter-submit">',
    //'#suffix' => '</div>',
  );
  $form['buttons']['submit'] = array(
    '#value' => t('Filter'),
    '#type' => 'submit',
  );
  $form['buttons']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
  );

  // enclose the whole form in another fieldset/container
  $form1['search_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Change Filter Parameters'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    $form,
  );
  $form = $form1;

  return $form;
}

/**
 * Add form fields: lng, mode, words, limit
 */
function _btrClient_filter_form_basic_search(&$form, &$form_state) {

  $languages = btrClient_get_languages();
  foreach ($languages as $code => $lang)  $lang_options[$code] = $lang['name'];
  $form['lng'] = array(
    '#type' => 'select',
    '#title' => t('Language of Translation'),
    '#description' => t('Select the language of the translations to be searched and displayed.'),
    '#options' => $lang_options,
    '#default_value' => $form_state['values']['lng'],
  );

  $form['basic_search'] = array(
    '#type' => 'fieldset',
    '#title' => t('What To Search For'),
    //'#description' => t('What to search for.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  list($search_mode_options, $default) = _btrClient_get_filter_options('mode', 'assoc');
  $form['basic_search']['mode'] = array(
    '#type' => 'select',
    '#title' => t('Search Mode'),
    '#options' => $search_mode_options,
    '#default_value' => $form_state['values']['mode'],
  );

  $form['basic_search']['words'] = array(
    '#type' => 'textarea',
    '#title' => t('The String Or Words To Be Searched'),
    '#description' => t('Search for l10n strings or translations that contain the given words. The <emphasized>natural</emphasized> search will try to find strings similar to the given one (see: <a href="!url1">Natural Language Full-Text Searches</a>). The <emphasized>boolean</emphasized> search will try to match words according to logical rules. The words can be preceded by + (plus), - (minus), etc. (for more details see: <a href="!url2">Boolean Full-Text Searches</a>).',
                    array(
                      '!url1' => 'http://dev.mysql.com/doc/refman/5.1/en/fulltext-natural-language.html',
                      '!url2' => 'http://dev.mysql.com/doc/refman/5.1/en/fulltext-boolean.html',
                    )),
    '#default_value' => $form_state['values']['words'],
    '#rows' => 2,
  );

  list($limit_options, $default) = _btrClient_get_filter_options('limit', 'assoc');
  $form['limit'] = array(
    '#type' => 'select',
    '#title' => t('Limit'),
    '#description' => t('The number of the results (strings) that can be displayed on a page.'),
    '#options' => $limit_options,
    '#default_value' => $form_state['values']['limit'],
  );
}

/**
 * Add form fieldset advanced_search/projects, with the fields: project and origin.
 */
function _btrClient_filter_form_advanced_search(&$form, &$form_state) {

  $form['advanced_search'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search Scope'),
    //'#description' => t('Limit the search scope only to certain interesting areas.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['advanced_search']['projects'] = array(
    '#type' => 'fieldset',
    '#title' => t('Projects'),
    //'#description' => t('Limit the search scope according to projects.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['advanced_search']['projects']['project'] = array(
    '#type' => 'textfield',
    '#title' => t('Project'),
    '#description' => t('Search only the strings belonging to the matching project.'),
    '#default_value' => $form_state['values']['project'],
    '#autocomplete_path' => 'translations/autocomplete/project',
  );

  $form['advanced_search']['projects']['origin'] = array(
    '#type' => 'textfield',
    '#title' => t('Origin'),
    '#description' => t('Limit search only to the projects from a certain origin.'),
    '#default_value' => $form_state['values']['origin'],
    '#autocomplete_path' => 'translations/autocomplete/origin',
  );
}

/**
 * Add fieldset advanced_search/author, with fields:
 * only_mine, translated_by, voted_by
 */
function _btrClient_filter_form_author(&$form, &$form_state) {

  $form['advanced_search']['author'] = array(
    '#type' => 'fieldset',
    '#title' => t('Author'),
    //'#description' => t('Limit the search scope according to the author.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['advanced_search']['author']['only_mine'] = array(
    '#type' => 'checkbox',
    '#title' => t('Only Mine'),
    '#description' => t('Search only the strings with translations suggested or voted by me.'),
    '#default_value' => $form_state['values']['only_mine'],
  );

  $lng = variable_get('btrClient_translation_lng', 'fr');
  $form['advanced_search']['author']['translated_by'] = array(
    '#type' => 'textfield',
    '#title' => t('Translated By'),
    '#description' => t('Search only the strings with translations suggested by the selected user.'),
    '#default_value' => $form_state['values']['translated_by'],
    '#autocomplete_path' => "translations/autocomplete/user/$lng",
    '#states' => array(
      'visible' => array(
        ':input[name="only_mine"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['advanced_search']['author']['voted_by'] = array(
    '#type' => 'textfield',
    '#title' => t('Voted By'),
    '#description' => t('Search only the strings with translations voted by the selected user.'),
    '#default_value' => $form_state['values']['voted_by'],
    '#autocomplete_path' => "translations/autocomplete/user/$lng",
    '#states' => array(
      'visible' => array(
        ':input[name="only_mine"]' => array('checked' => FALSE),
      ),
    ),
  );
}

/**
 * Add fieldset advanced_search/date,
 * with fields: date_filter, from_date, to_date
 */
function _btrClient_filter_form_date(&$form, &$form_state) {
  $form['advanced_search']['date'] = array(
    '#type' => 'fieldset',
    '#title' => t('Date'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  list($date_filter_options, $default) = _btrClient_get_filter_options('date_filter', 'assoc');
  $form['advanced_search']['date']['date_filter'] = array(
    '#type' => 'select',
    '#title' => t('What to Filter'),
    '#description' => t('Select what to filter by date (strings, translations, or votes).'),
    '#options' => $date_filter_options,
    '#default_value' => $form_state['values']['date_filter'],
  );

  $form['advanced_search']['date']['from_date'] = array(
    '#type' => 'textfield',
    '#title' => t('From Date'),
    '#default_value' => $form_state['values']['from_date'],
  );

  $form['advanced_search']['date']['to_date'] = array(
    '#type' => 'textfield',
    '#title' => t('To Date'),
    '#default_value' => $form_state['values']['to_date'],
  );
}


// ----------------------- utility functions ----------------------------

/**
 * Utility function that returns an array of options for the given field
 * and the default value. If being associative ($assoc) is not required
 * then only the keys are retrned.
 */
function _btrClient_get_filter_options($field, $assoc =FALSE) {

  switch ($field) {

    case 'limit':
      //number of results to be displayed per page
      $options = array(
        '5'  => '5',
        '10' => '10',
        '20' => '20',
        '30' => '30',
        '50' => '50'
      );
      $default = 5;
      break;

    case 'mode':
      //search mode
      $options = array(
        'natural-strings' => t('Natural search on strings.'),
        'natural-translations' => t('Natural search on translations.'),
        'boolean-strings' => t('Boolean search on strings.'),
        'boolean-translations' => t('Boolean search on translations.'),
      );
      $default = 'natural-strings';
      break;

    case 'date_filter':
      //which date to filter
      $options = array(
        'strings' => t('Filter Strings By Date'),
        'translations' => t('Filter Translations By Date'),
        'votes' => t('Filter Votes By Date'),
      );
      $default = 'translations';
      break;
  }
  if (!$assoc) $options = array_keys($options);
  return array($options, $default);
}
