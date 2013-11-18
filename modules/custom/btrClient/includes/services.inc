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
  $service->name = 'public/btr';
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
  $service->operations['report_topcontrib'] = array(
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
  $service->operations['get_translations'] = array(
    'url' => 'translations/@sguid',
    'parameter' => array(
      'sguid' => array(),
      'lng' => array(),
    ),
  );
  // add the service
  $services[$service->name] = $service;

  // authenticated services
  $service = new WSClientServiceDescription();
  $service->name = 'btr';
  $service->url = $btr_url . '/btr/';
  $service->type = 'rest';
  // skip checking the SSL certificate, for testing
  $service->settings['curl options'] = array(
    CURLOPT_SSL_VERIFYPEER => FALSE,
    CURLOPT_SSL_VERIFYHOST => FALSE,
  );
  $service->settings['authentication']['oauth2'] = array(
    'token_endpoint' => 'https://dev.l10n.org.xx/oauth2/token',
    // auth_flow can be: server-side | client-credentials | user-password
    'auth_flow' => 'user-password',
    'client_id' => 'test1',
    'client_secret' => 'test1',
    'username' => 'user1',
    'password' => 'user1',
    //'redirect_uri' => 'https://dev.l10n.org.xx/oauth2/authorized',
    //'authorization_endpoint' => 'https://dev.l10n.org.xx/oauth2/authorize',
    //'scope' => '',
    //'query_auth' => TRUE,
  );
  $service->operations['get_translations'] = array(
    'url' => 'translations/@sguid',
    'parameter' => array(
      'sguid' => array(),
      'lng' => array(),
      //'access_token' => array(),
    ),
  );
  // add the service
  $services[$service->name] = $service;

  return $services;
}
