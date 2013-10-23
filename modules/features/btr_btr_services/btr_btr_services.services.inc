<?php
/**
 * @file
 * btr_btr_services.services.inc
 */

/**
 * Implements hook_default_services_endpoint().
 */
function btr_btr_services_default_services_endpoint() {
  $export = array();

  $endpoint = new stdClass();
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'btranslator';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'btr';
  $endpoint->authentication = array(
    'oauth2_server' => array(
      'server' => 'oauth2_btr',
    ),
  );
  $endpoint->server_settings = array(
    'formatters' => array(
      'bencode' => TRUE,
      'json' => TRUE,
      'jsonp' => TRUE,
      'php' => TRUE,
      'xml' => TRUE,
    ),
    'parsers' => array(
      'application/json' => TRUE,
      'application/vnd.php.serialized' => TRUE,
      'application/x-www-form-urlencoded' => TRUE,
      'application/xml' => TRUE,
      'multipart/form-data' => TRUE,
      'text/xml' => TRUE,
    ),
  );
  $endpoint->resources = array(
    'report' => array(
      'operations' => array(
        'retrieve' => array(
          'enabled' => '1',
          'settings' => array(
            'oauth2_server' => array(
              'scope' => '',
              'require_authentication' => NULL,
            ),
          ),
        ),
      ),
      'actions' => array(
        'statistics' => array(
          'enabled' => '1',
          'settings' => array(
            'oauth2_server' => array(
              'scope' => '',
              'require_authentication' => NULL,
            ),
          ),
        ),
        'topcontrib' => array(
          'enabled' => '1',
          'settings' => array(
            'oauth2_server' => array(
              'scope' => '',
              'require_authentication' => NULL,
            ),
          ),
        ),
      ),
    ),
  );
  $endpoint->debug = 1;
  $export['btranslator'] = $endpoint;

  return $export;
}
