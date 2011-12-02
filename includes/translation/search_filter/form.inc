<?php

/**
 * Functions related to the filter form
 * of the translation/search interface.
 */

/**
 * Build the filter data from the GET request,
 * which is like: translation/search?lng=fr&words=xyz&limit=10
 * Check and sanize the data, and put default values where missing.
 */
function l10n_suggestions_build_filter() {

  //get a copy of the request parameters
  $request = $_GET;

  //get language
  $languages = l10n_suggestions_get_languages();
  $lng_codes = array_keys($languages);
  $lng = isset($request['lng']) ? trim($request['lng']) : '';
  $filter['lng'] = in_array($lng, $lng_codes) ? $lng : 'fr';

  //number of results to be displayed
  $limit = isset($request['limit']) ? (int)trim($request['limit']) : 0;
  list($limit_options, $default_limit) = _l10n_suggestions_get_filter_options('limit');
  $filter['limit'] = in_array($limit, $limit_options) ? $limit : $default_limit;

  //search can be done either by similarity of l10n strings (natural search),
  //or by matching words according to a certain logic (boolean search);
  //search can be performed either on l10n strings or on the translations
  $mode = isset($request['mode']) ? $request['mode'] : '';
  list($search_mode_options, $default_search_mode) = _l10n_suggestions_get_filter_options('mode');
  $filter['mode'] = in_array($mode, $search_mode_options) ? $mode : $default_search_mode;
  $filter['words'] = isset($request['words']) ? $request['words'] : '';

  //searching can be limited only to certain packages, projects or releases
  $filter['package'] = isset($request['package']) ? trim($request['package']) : '';
  $filter['project'] = isset($request['project']) ? trim($request['project']) : '';
  $filter['release'] = isset($request['release']) ? trim($request['release']) : '';

  //limit search only to the strings touched (translated or voted) by the current user
  $filter['only_mine'] = isset($request['only_mine']) && (int)$request['only_mine'] ? 1 : 0;

  //limit search by the editing users (used by admins)
  $filter['translated_by'] = isset($request['translated_by']) ? trim($request['translated_by']) : '';
  $filter['voted_by'] = isset($request['voted_by']) ? trim($request['voted_by']) : '';

  //limit by date of string, translation or voting (used by admins)
  $date_filter = isset($request['date_filter']) ? trim($request['date_filter']) : '';
  list($date_filter_options, $default_date_filter) = _l10n_suggestions_get_filter_options('date_filter');
  $filter['date_filter'] = in_array($date_filter, $date_filter_options) ? $date_filter : $default_date_filter;

  //from_date
  $from_date = isset($request['from_date']) ? trim($request['from_date']) : '';
  list($year, $month, $day) = explode('-', $from_date, 3) + array('','','');
  $filter['from_date'] = checkdate((int)$month, (int)$day, (int)$year) ?
    array('year' => (int)$year, 'month' => (int)$month, 'day' => (int)$day) :
    array('year' => date('Y'), 'month' => date('n'), 'day' => date('j'));

  //to_date
  $to_date = isset($request['to_date']) ? trim($request['to_date']) : '';
  list($year, $month, $day) = explode('-', $to_date, 3) + array('','','');
  $filter['to_date'] = checkdate((int)$month, (int)$day, (int)$year) ?
    array('year' => (int)$year, 'month' => (int)$month, 'day' => (int)$day) :
    array('year' => date('Y'), 'month' => date('n'), 'day' => date('j'));

  return $filter;
}

/**
 * Submission handler for filtering form.
 */
function l10n_suggestions_filter_form_submit($form, &$form_state) {

  //dpm($form_state['values']);  //debug

  if ($form_state['values']['op'] == t('Reset')) {
    // Just go with the redirection flow => removes URL params.
    return;
  }

  if ($form_state['values']['op'] == t('Filter')) {
    // Redirect (with a GET request) keeping the relevant filters intact in the URL.
    $form_state['redirect'] = array(
      $_GET['q'],
      array('query' => l10n_suggestions_get_query_values($form_state['values']))
    );
    return;
  }
}

/**
 * Converts the array of form values into a suitable query (for redirect).
 * All non-string values are converted to string representations.
 * If a form value is equal to the default value, it is removed (unset) from the array.
 */
function l10n_suggestions_get_query_values($form_values) {

  $query = array();

  //lng
  $languages = l10n_suggestions_get_languages();
  $lng_codes = array_keys($languages);
  $lng = trim($form_values['lng']);
  if (in_array($lng, $lng_codes))
    $query['lng'] = $lng;

  //package, project, release
  if (trim($form_values['project']) != '' )
    $query['project'] = $form_values['project'];
  /*
  if (trim($form_values['package']) != '' )
    $query['package'] = $form_values['pakage'];
  if (trim($form_values['release']) != '' )
    $query['release'] = $form_values['release'];
  */

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
  list($date_filter_options, $default_date_filter) = _l10n_suggestions_get_filter_options('date_filter');
  if ( in_array($form_values['date_filter'], $date_filter_options)
    && $form_values['date_filter'] != $default_date_filter )
    {
      $query['date_filter'] = $form_values['date_filter'];
    }

  //from_date
  $arr_date = $form_values['from_date'];
  $str_date = date('Y-m-d', mktime(1, 0, 0, $arr_date['month'], $arr_date['day'], $arr_date['year']));
  if ($str_date != date('Y-m-d'))
    $query['from_date'] = $str_date;

  //to_date
  $arr_date = $form_values['to_date'];
  $str_date = date('Y-m-d', mktime(1, 0, 0, $arr_date['month'], $arr_date['day'], $arr_date['year']));
  if ($str_date != date('Y-m-d'))
    $query['to_date'] = $str_date;

  //limit
  list($limit_options, $default_limit) = _l10n_suggestions_get_filter_options('limit');
  if ( in_array($form_values['limit'], $limit_options)
    && $form_values['limit'] != $default_limit )
    {
      $query['limit'] = $form_values['limit'];
    }

  //search mode and words
  list($search_mode_options, $default_search_mode) = _l10n_suggestions_get_filter_options('mode');
  if ( in_array($form_values['mode'], $search_mode_options)
    && $form_values['mode'] != $default_search_mode )
    {
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
function l10n_suggestions_filter_form($form, &$form_state, $filter) {

  //if the form has no values yet (either it is the first time that
  //the form is opened, or we have a get request), we set the values
  //of the form according to the $filter values
  if (empty($form_state['values'])) {
    $form_state['values'] = $filter;
  }

  $form = array(
    '#prefix' => '<div class="l10n-suggestions-filter clear-block">',
    '#suffix' => '</div>',
  );

  $languages = l10n_suggestions_get_languages();
  foreach ($languages as $code => $lang)  $lang_options[$code] = $lang['name'];
  $form['lng'] = array(
    '#type' => 'select',
    '#title' => t('Language of Translation'),
    '#description' => t('Select the language of the translations to be searched and displayed.'),
    '#options' => $lang_options,
    '#default_value' => $form_state['values']['lng'],
  );

  // -------- basic search ----------

  $form['basic_search'] = array(
    '#type' => 'fieldset',
    '#title' => t('What To Search For'),
    //'#description' => t('What to search for.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  list($search_mode_options, $default) = _l10n_suggestions_get_filter_options('mode', 'assoc');
  $form['basic_search']['mode'] = array(
    '#type' => 'select',
    '#title' => t('Search Mode'),
    '#options' => $search_mode_options,
    '#default_value' => $form_state['values']['mode'],
  );

  $form['basic_search']['words'] = array(
    '#type' => 'textarea',
    '#title' => t('The String Or Words To Be Searched'),
    '#description' => t('Search for l10n strings or translations that contain the given words. The <emphasized>natural</emphasized> search will try to find strings similar to the given one (see: <a href="http://dev.mysql.com/doc/refman/5.1/en/fulltext-natural-language.html">Natural Language Full-Text Searches</a>). The <emphasized>boolean</emphasized> search will try to match words according to logical rules. The words can be preceded by + (plus), - (minus), etc. (for more details see: <a href="http://dev.mysql.com/doc/refman/5.1/en/fulltext-boolean.html">Boolean Full-Text Searches</a>).'),
    '#default_value' => $form_state['values']['words'],
    '#rows' => 2,
  );

  list($limit_options, $default) = _l10n_suggestions_get_filter_options('limit', 'assoc');
  $form['limit'] = array(
    '#type' => 'select',
    '#title' => t('Limit'),
    '#description' => t('The number of the results (strings) that can be displayed on a page.'),
    '#options' => $limit_options,
    '#default_value' => $form_state['values']['limit'],
  );

  // -------- advanced search ----------

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

  /*
  $form['advanced_search']['projects']['package'] = array(
    '#type' => 'textfield',
    '#title' => t('Package'),
    '#description' => t('Search only the strings belonging to the matching package.'),
    '#default_value' => $form_state['values']['package'],
    '#autocomplete_path' => 'translation/package-autocomplete',
  );
  */

  $form['advanced_search']['projects']['project'] = array(
    '#type' => 'textfield',
    '#title' => t('Project'),
    '#description' => t('Search only the strings belonging to the matching project.'),
    '#default_value' => $form_state['values']['project'],
    '#autocomplete_path' => 'translation/autocomplete/project',
  );

  /*
  $form['advanced_search']['projects']['release'] = array(
    '#type' => 'textfield',
    '#title' => t('Release'),
    '#description' => t('Search only the strings belonging to the matching release.'),
    '#default_value' => $form_state['values']['release'],
    '#autocomplete_path' => 'translation/release-autocomplete',
  );
  */

  //TODO: Some of the advanced filtering options should be available
  //      only if the user has propper access rights.

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

  $form['advanced_search']['author']['translated_by'] = array(
    '#type' => 'textfield',
    '#title' => t('Translated By'),
    '#description' => t('Search only the strings with translations suggested by the selected user.'),
    '#default_value' => $form_state['values']['translated_by'],
    '#autocomplete_path' => 'translation/autocomplete/user',
    '#states' => array(
      'visible' => array(
        ':input[name="only_mine"]' => array('checked' => false),
      ),
    ),
  );

  $form['advanced_search']['author']['voted_by'] = array(
    '#type' => 'textfield',
    '#title' => t('Voted By'),
    '#description' => t('Search only the strings with translations voted by the selected user.'),
    '#default_value' => $form_state['values']['voted_by'],
    '#autocomplete_path' => 'translation/autocomplete/user',
    '#states' => array(
      'visible' => array(
        ':input[name="only_mine"]' => array('checked' => false),
      ),
    ),
  );

  $form['advanced_search']['date'] = array(
    '#type' => 'fieldset',
    '#title' => t('Date'),
    //'#description' => t('Limit the search scope by date.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  list($date_filter_options, $default) = _l10n_suggestions_get_filter_options('date_filter', 'assoc');
  $form['advanced_search']['date']['date_filter'] = array(
    '#type' => 'select',
    '#title' => t('What to Filter'),
    '#description' => t('Select what to filter by date (strings, translations, or votes).'),
    '#options' => $date_filter_options,
    '#default_value' => $form_state['values']['date_filter'],
  );

  $form['advanced_search']['date']['from_date'] = array(
    '#type' => 'date',
    '#title' => t('From Date'),
    '#default_value' => $form_state['values']['from_date'],
  );

  $form['advanced_search']['date']['to_date'] = array(
    '#type' => 'date',
    '#title' => t('To Date'),
    '#default_value' => $form_state['values']['to_date'],
  );

  // --------------------------------------------

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

  $form1['search_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Change Filter Parameters'),
    //'#description' => t('Limit the search scope according to the author.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    $form,
  );
  $form = $form1;

  return $form;
}

// ----------------------- utility functions ----------------------------

/**
 * Utility function that returns an array of options for the given field
 * and the default value. If being associative ($assoc) is not required
 * then only the keys are retrned.
 */
function _l10n_suggestions_get_filter_options($field, $assoc =FALSE) {

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
?>