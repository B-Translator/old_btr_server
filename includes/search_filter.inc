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

  //strings can be searched either by the similarity of the given phrase
  //or whether they contain the given words; 'search' keeps the kind of search
  $filter['phrase'] = isset($request['phrase']) ? $request['phrase'] : '';
  $filter['words'] = isset($request['words']) ? $request['words'] : '';
  $search = isset($request['search']) ? $request['search'] : '';
  $filter['search'] = in_array($search, array('phrase', 'words')) ? $search :
    $filter['phrase']!='' && $filter['words']=='' ? 'phrase' : 'words';

  //searching can be limited only to certain packages, projects or releases
  //$filter['package'] = isset($request['package']) ? trim($request['package']) : '';
  $filter['project'] = isset($request['project']) ? trim($request['project']) : '';
  //$filter['release'] = isset($request['release']) ? trim($request['release']) : '';

  //limit search by the editing users (used by admins)
  $filter['translated_by'] = isset($request['translated_by']) ? trim($request['translated_by']) : '';
  $filter['voted_by'] = isset($request['voted_by']) ? trim($request['voted_by']) : '';

  //limit search only to the strings touched (translated or voted) by the current user
  $filter['only_mine'] = isset($request['only_mine']) && (int)$request['only_mine'] ? 1 : 0;

  //limit by date of string, translation or voting (used by admins)
  $date_filter = isset($request['date_filter']) ? trim($request['date_filter']) : '';
  $filter['date_filter'] = in_array($date_filter, array('strings', 'translations', 'votes')) ?
    $date_filter : 'translations';

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

  //number of results to be displayed
  $limit = isset($request['limit']) ? (int)trim($request['limit']) : 5;
  $filter['limit'] = in_array($limit, array(5, 10, 20, 30, 50)) ? $limit : 5;

  dpm($filter);  //debug
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

  //search, words, phrase
  if ($form_values['search'] == 'phrase')  //default: 'words'
    $query['search'] = $form_values['search'];
  if (trim($form_values['words']) != '' )
    $query['words'] = $form_values['words'];
  if (trim($form_values['phrase']) != '' )
    $query['phrase'] = $form_values['phrase'];

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
  if (in_array($form_values['date_filter'], array('strings', 'votes')))  //default: 'translations'
    $query['date_filter'] = $form_values['date_filter'];

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
  if (in_arraY($form_values['limit'], array(10, 20, 30, 50)))  //default: 5
    $query['limit'] = $form_values['limit'];

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
    '#title' => t('Language'),
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

  $form['basic_search']['search'] = array(
    '#type' => 'select',
    '#title' => t('Search Mode'),
    '#description' => t('Choose between one of the two modes for string searching.'),
    '#options' => array(
      'phrase' => t('Search for strings similar to the given phrase.'),
      'words' => t('Search for strings or translations matching the given words.'),
    ),
    '#default_value' => $form_state['values']['search'],
  );

  $form['basic_search']['phrase'] = array(
    '#type' => 'textarea',
    '#title' => t('The Phrase To Be Searched For'),
    '#description' => t('Strings that are as similar as possible to the given phrase will be searched and displayed.'),
    '#rows' => 3,
    '#cols' => 50,
    '#default_value' => $form_state['values']['phrase'],
    '#states' => array(
      'visible' => array(
        ':input[name="search"]' => array('value' => 'phrase'),
      ),
    ),
  );

  $form['basic_search']['words'] = array(
    '#type' => 'textfield',
    '#title' => t('The Words To Be Matched'),
    '#description' => t('Strings or translations that contain any of the given words will be displayed. If some words start with + (plus), then only the strings (or translations) that contain all of these words will be matcched. If some words start with - (minus), then only the strings (or translations) that contain none of these words will be matched.'),
    '#default_value' => $form_state['values']['words'],
    '#size' => 50,
    '#states' => array(
      'visible' => array(
        ':input[name="search"]' => array('value' => 'words'),
      ),
    ),
  );

  $form['limit'] = array(
    '#type' => 'select',
    '#title' => t('Limit'),
    '#description' => t('The number of the results (strings) that can be displayed on a page.'),
    '#options' => drupal_map_assoc(array(5, 10, 20, 30, 50)),
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
    '#autocomplete_path' => 'translation/project-autocomplete',
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
    '#autocomplete_path' => 'translation/user-autocomplete',
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
    '#autocomplete_path' => 'translation/user-autocomplete',
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

  $form['advanced_search']['date']['date_filter'] = array(
    '#type' => 'select',
    '#title' => t('What to Filter'),
    '#description' => t('Select what to filter by date (strings, translations, or votes).'),
    '#options' => array(
      'strings' => t('Filter Strings By Date'),
      'translations' => t('Filter Translations By Date'),
      'votes' => t('Filter Votes By Date'),
    ),
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
    '#prefix' => '<div class="filter-submit-1">',
    '#suffix' => '</div>',
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

/**
 * Theme function for l10n_suggestions_filter_form elements.
 */
function theme_l10n_suggestions_filter_form_element($variables) {
  $element = $variables['element'];

  // Bubble up a js-hide class to the container.
  $class = '';
  if (!empty($element['#display_none'])) {
    $class = ' js-hide';
  }
  return '<div class="filter-widget' . $class . '">' . $element['#children'] . '</div>';
}

?>