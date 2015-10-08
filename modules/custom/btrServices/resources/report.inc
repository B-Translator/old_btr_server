<?php
/**
 * @file
 * Resource definition and callbacks for report.
 */

function _btrServices_report() {
  $file = array('type' => 'inc', 'module' => 'btrServices', 'name' => 'resources/report');
  $access = array(
    'access callback' => 'user_access',
    'access arguments' => array('access content'),
  );

  // Getting reports of different kinds.
  $report['operations']['retrieve'] = array(
    'help' => 'Reports of different kinds.',
    'file' => $file,
    'callback' => '_btr_report_retrieve',
    'args' => array(
      array(
        'name' => 'report',
        'optional' => FALSE,
        'source' => array('path' => 0),
        'description' => 'The name/id of the report.',
        'type' => 'string',
      ),
      array(
        'name' => 'params',
        'optional' => FALSE,
        'source' => 'param',
        'description' => 'Parameters of the report.',
        'type' => 'array',
      ),
    ),
  ) + $access;

  // Getting general statistics (number of votes and
  // translations) for the last week, month and year.
  $report['actions']['statistics'] = array(
    'help' => 'General statistics (number of votes and translations) for the last week, month and year.',
    'file' => $file,
    'callback' => '_btr_report_statistics',
    'args' => array(
      array(
        'name' => 'params',
        'optional' => FALSE,
        'source' => 'data',
        'description' => 'The parameters of the report.',
        'type' => 'array',
      ),
    ),
  ) + $access;

  // Getting project details and statistics.
  $report['actions']['project_stats'] = array(
    'help' => 'Project details and statistics.',
    'file' => $file,
    'callback' => '_btr_report_project_stats',
    'args' => array(
      array(
        'name' => 'params',
        'optional' => FALSE,
        'source' => 'data',
        'description' => 'The parameters of the report.',
        'type' => 'array',
      ),
    ),
  ) + $access;

  // Getting statistics about top contributors.
  $report['actions']['topcontrib'] = array(
    'help' => 'Statistics about top contributors.',
    'file' => $file,
    'callback' => '_btr_report_topcontrib',
    'args' => array(
      array(
        'name' => 'params',
        'optional' => FALSE,
        'source' => 'data',
        'description' => 'The parameters of the report.',
        'type' => 'array',
      ),
    ),
  ) + $access;

  return $report;
}

/**
 * Getting reports of different kinds. Anybody can
 * retrieve them, there are no access restrictions.
 *
 * @param $report
 *   The name/id of the report.
 *
 * @param $params
 *   Parameters of the report, comming from the
 *   GET request. They depend on the kind of report.
 *
 * @return
 *   The data of the requested report.
 *
 * @example
 *   curl -k -i \
 *     'https://dev.btr.example.org/api/report/statistics?lng=sq'
 *   curl -k -i \
 *     'https://dev.btr.example.org/api/report/topcontrib?lng=sq&period=week'
 */
function _btr_report_retrieve($report, $params) {
  $report_function = '_btr_report_' . $report;
  if (! function_exists($report_function) ) {
    return services_error("Unknown report: $report", 406);
  }
  return $report_function($params);
}

/**
 * Getting general statistics (number of votes and
 * translations) for the last week, month and year.
 *
 * @param $params
 *   Parameters of the report, comming from the POST request.
 *   It contains these fields (variables):
 *   - lng: language of translations
 *   - origin: (optional) origin of the project
 *   - project: (optional) name of the project
 *
 * @return
 *   Array of general stats for week, month and year.
 *
 * @example
 *   curl -k -i -H "Content-type: application/json"  \
 *        -X POST https://dev.btr.example.org/api/report/statistics \
 *        -d '{"lng": "sq"}'
 */
function _btr_report_statistics($params) {
  $params += array(
    'lng' => NULL,
    'origin' => NULL,
    'project' => NULL,
  );

  // get parameters and validate them
  $lng = $params['lng'];
  if (!$lng)  $lng = 'all';
  if (!in_array($lng, btr::languages_get()) and $lng != 'all') {
    return services_error('Language missing or not supported.', 406);
  }
  $origin = $params['origin'];
  $project = $params['project'];

  return btr::report_statistics($lng, $origin, $project);
}

/**
 * Getting project details and statistics (number of translated and untranslated
 * strings, number of votes and translations, users and contributers, etc.)
 *
 * @param $params
 *   Parameters of the report, comming from the POST request.
 *   It contains these fields (variables):
 *   - origin: origin of the project
 *   - project: name of the project
 *   - lng: language of translations
 *
 * @return
 *   Array of general stats for week, month and year.
 *
 * @example
 *   curl -k -i -H "Content-type: application/json"  \
 *        -X POST https://dev.btr.example.org/api/report/project_stats \
 *        -d '{"origin": "LibreOffice", "project": "cui", "lng": "sq"}'
 */
function _btr_report_project_stats($params) {
  $params += array(
    'origin' => NULL,
    'project' => NULL,
    'lng' => NULL,
  );

  // get parameters and validate them
  $lng = $params['lng'];
  if (!in_array($lng, btr::languages_get())) {
    return services_error('Language missing or not supported.', 406);
  }
  $origin = $params['origin'];
  $project = $params['project'];
  if (!btr::project_exists($origin, $project)) {
    $msg = "The project '$origin/$project' does not exist.";
    return services_error($msg, 406);
  }

  return btr::report_project_stats($origin, $project, $lng);
}

/**
 * Getting statistics about top contributors.
 *
 * @param $params
 *   Parameters of the report, comming from the POST request.
 *   It contains these fields (variables):
 *   - lng: language of translations
 *   - period: period of report: day | week | month | year
 *   - size: number of results (top contributers), between 5 and 100
 *   - origin: (optional) origin of the project
 *   - project: (optional) name of the project
 *
 * @return
 *   Array of users, where each user is an object with these attributes:
 *   uid, name, umail, score, translations, votes
 *
 * @example
 *   curl -k -i -H "Content-type: application/json"  \
 *     -X POST https://dev.btr.example.org/api/report/topcontrib \
 *     -d '{"lng": "sq", "period": "week", "size": 10}'
 */
function _btr_report_topcontrib($params) {
  $params += array(
    'lng' => NULL,
    'period' => 'week',
    'size' => 5,
    'origin' => NULL,
    'project' => NULL,
  );

  // get parameters and validate them
  $period = $params['period'];
  if (!in_array($period, array('day', 'week', 'month', 'year'))) {
    return services_error('Period missing or not supported.', 406);
  }
  $size = (int)$params['size'];
  if ($size < 5 or $size > 100) {
    return services_error('Size must be between 5 and 100.', 406);
  }
  $lng = $params['lng'];
  if (!$lng)  $lng = 'all';
  if (!in_array($lng, btr::languages_get()) and $lng != 'all') {
    return services_error('Language missing or not supported.', 406);
  }
  $origin = $params['origin'];
  $project = $params['project'];

  return btr::report_topcontrib($period, $size, $lng, $origin, $project);
}
