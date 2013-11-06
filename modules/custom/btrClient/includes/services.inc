<?php
/**
 * Define web services.
 */

/**
 * Implements hook_default_wsclient_service()
 * and defines web service descriptions.
 * This hook is invoked when web service descriptions
 * are loaded like this:
 *     $btr = wsclient_service_load('dev.l10n.org.xx');
 *     $result = $btr->statistics('sq');
 *
 * @return
 *     An array of web service descriptions
 *     with the web service names as keys.
 */
function btrClient_default_wsclient_service() {

  $btr_url = 'https://dev.l10n.org.xx';

  // public services
  $service = new WSClientServiceDescription();
  $service->name = '/public/btr';
  $service->url = $btr_url . '/public/btr/';
  $service->type = 'rest';
  // skip checking the SSL certificate, for testing
  $service->settings['curl options'] = array(
    CURLOPT_SSL_VERIFYPEER => FALSE,
    CURLOPT_SSL_VERIFYHOST => FALSE,
  );

  $service->operations['report_statistics'] = array(
    'url' => 'report/statistics',
    'parameter' => array(
      'lng' => array(),
    ),
  );
  $service->operations['repport_topcontrib'] = array(
    'url' => 'report/topcontrib',
    'parameter' => array(
      'lng' => array(),
      'period' => array(),
      'size' => array(),
    ),
  );
  $service->operations['report_statistics_1'] = array(
    'url' => 'report/statistics',
    'type' => 'POST',
    'data' => 'params',
    'parameter' => array(
      'params' => array(),
    ),
  );
  $service->operations['report_topcontrib_1'] = array(
    'url' => 'report/topcontrib',
    'type' => 'POST',
    'data' => 'params',
    'parameter' => array(
      'params' => array(),
    ),
  );

  // add the service
  $services[$service->name] = $service;

  // authenticated services
  $service = new WSClientServiceDescription();
  $service->name = '/btr';
  $service->url = $btr_url . '/btr/';
  $service->type = 'rest';
  // skip checking the SSL certificate, for testing
  $service->settings['curl options'] = array(
    CURLOPT_SSL_VERIFYPEER => FALSE,
    CURLOPT_SSL_VERIFYHOST => FALSE,
  );

  // add the service
  $services[$service->name] = $service;

  return $services;
}
