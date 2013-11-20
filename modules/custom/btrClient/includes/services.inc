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

  $server_url = variable_get('btrClient_server_url', 'https://dev.l10n.org.xx');
  $client_id = variable_get('btrClient_client_id', 'test1');
  $client_secret = variable_get('btrClient_client_secret', 'test1');
  $skip_ssl_check = variable_get('btrClient_skip_ssl_check', TRUE);

  // public services
  $service = new WSClientServiceDescription();
  $service->name = 'public_btr';
  $service->label = 'Public B-Translator Services';
  $service->type = 'rest';
  $service->url = $server_url . '/public/btr/';

  // skip checking the SSL certificate, for testing
  if ($skip_ssl_check) {
    $service->settings['curl options'] = array(
      CURLOPT_SSL_VERIFYPEER => FALSE,
      CURLOPT_SSL_VERIFYHOST => FALSE,
    );
  }

  $service->operations['report_statistics'] = array(
    'label' => 'report_statistics',
    'url' => 'report/statistics',
    'parameter' => array(
      'lng' => array('type' => 'text'),
    ),
  );
  $service->operations['report_topcontrib'] = array(
    'label' => 'report_topcontrib',
    'url' => 'report/topcontrib',
    'parameter' => array(
      'lng' => array('type' => 'text'),
      'period' => array('type' => 'text'),
      'size' => array('type' => 'integer'),
    ),
  );
  $service->operations['report_statistics_1'] = array(
    'label' => 'report_statistics',
    'url' => 'report/statistics',
    'type' => 'POST',
    'data' => 'params',
    'parameter' => array(
      'params' => array(),
    ),
  );
  $service->operations['report_topcontrib_1'] = array(
    'label' => 'report_topcontrib_1',
    'url' => 'report/topcontrib',
    'type' => 'POST',
    'data' => 'params',
    'parameter' => array(
      'params' => array(),
    ),
  );
  $service->operations['get_translations'] = array(
    'label' => 'get_translations',
    'url' => 'translations/@sguid',
    'parameter' => array(
      'sguid' => array(),
      'lng' => array(),
    ),
  );
  // add the service
  $services[$service->name] = $service;

  // authenticated services
  $token_endpoint = $server_url . '/oauth2/token';
  $authorization_endpoint = $server_url . '/oauth2/authorize';
  $redirect_uri = url('/oauth2/authorized', array('absolute' => TRUE));

  $service = new WSClientServiceDescription();
  $service->name = 'btr';
  $service->label = 'Authenticated B-Translator Services';
  $service->type = 'rest';
  $service->url = $server_url . '/btr/';

  // skip checking the SSL certificate, for testing
  if ($skip_ssl_check) {
    $service->settings['curl options'] = array(
      CURLOPT_SSL_VERIFYPEER => FALSE,
      CURLOPT_SSL_VERIFYHOST => FALSE,
    );
  }

  $service->settings['authentication']['oauth2'] = array(
    'token_endpoint' => $token_endpoint,
    // auth_flow can be: server-side | client-credentials | user-password
    'auth_flow' => 'user-password',
    'client_id' => $client_id,
    'client_secret' => $client_secret,
    'username' => 'user1',
    'password' => 'user1',
    //'redirect_uri' => $redirect_uri,
    //'authorization_endpoint' => $authorization_endpoint,
    //'scope' => '',
    //'query_auth' => TRUE,
  );
  $service->operations['get_translations'] = array(
    'label' => 'get_translations',
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
