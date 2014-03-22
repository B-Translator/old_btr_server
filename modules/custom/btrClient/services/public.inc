<?php
/**
 * Define public web services.
 */

/**
 * Create and return the public service.
 */
function _btrClient_services_public_service($service_name) {
  $server_url = variable_get('oauth2_login_oauth2_server', '');

  $service = new WSClientServiceDescription();
  $service->name = $service_name;
  $service->label = 'Public B-Translator Services';
  $service->type = 'rest';
  $service->url = $server_url . '/public/btr/';

  $service->settings += _btrClient_services_dev_settings();

  $service->operations += _btrClient_services_public_report();
  $service->operations += _btrClient_services_public_translations();

  return $service;
}

/**
 * Return definitions for operations about reports.
 */
function _btrClient_services_public_report() {
  $operations['report_statistics'] = array(
    'label' => 'report_statistics',
    'url' => 'report/statistics',
    'parameter' => array(
      'lng' => array('type' => 'text'),
    ),
  );

  $operations['report_topcontrib'] = array(
    'label' => 'report_topcontrib',
    'url' => 'report/topcontrib',
    'parameter' => array(
      'lng' => array('type' => 'text'),
      'period' => array('type' => 'text'),
      'size' => array('type' => 'integer'),
    ),
  );

  $operations['report_statistics_1'] = array(
    'label' => 'report_statistics_1',
    'url' => 'report/statistics',
    'type' => 'POST',
    'data' => 'params',
    'parameter' => array(
      'params' => array('type' => 'array'),
    ),
  );

  $operations['report_topcontrib_1'] = array(
    'label' => 'report_topcontrib_1',
    'url' => 'report/topcontrib',
    'type' => 'POST',
    'data' => 'params',
    'parameter' => array(
      'params' => array('type' => 'array'),
    ),
  );

  return $operations;
}

/**
 * Return definitions for operations about translations.
 */
function _btrClient_services_public_translations() {
  $operations['get_translations'] = array(
    'label' => 'get_translations',
    'url' => 'translations/@sguid',
    'parameter' => array(
      'sguid' => array('type' => 'text'),
      'lng' => array('type' => 'text'),
    ),
  );

  $operations['get_random_sguid'] = array(
    'label' => 'get_random_sguid',
    'url' => 'translations/get_random_sguid',
    'type' => 'POST',
    'data' => 'params',
    'parameter' => array(
      'params' => array('type' => 'array'),
    ),
  );

  $operations['search'] = array(
    'label' => 'search',
    'url' => 'translations/search',
    'type' => 'POST',
    'data' => 'params',
    'parameter' => array(
      'params' => array('type' => 'array'),
    ),
  );

  return $operations;
}
