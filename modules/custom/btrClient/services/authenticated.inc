<?php
/**
 * Define authenticated web services.
 */

/**
 * Create and return the authenticated service.
 */
function _btrClient_services_authenticated_service($service_name) {
  $server_url = variable_get('oauth2_login_oauth2_server', '');

  $service = new WSClientServiceDescription();
  $service->name = $service_name;
  $service->label = 'Authenticated B-Translator Services';
  $service->type = 'rest';
  $service->url = $server_url . '/btr/';

  $service->settings += _btrClient_services_dev_settings();
  $service->settings += _btrClient_services_authentication();

  $service->operations += _btrClient_services_authenticated_translations();
  $service->operations += _btrClient_services_authenticated_projects();

  return $service;
}

/**
 * Return authentication settings.
 */
function _btrClient_services_authentication() {
  $server_url = variable_get('oauth2_login_oauth2_server', '');
  $client_id = variable_get('oauth2_login_client_id', '');
  $client_secret = variable_get('oauth2_login_client_secret', '');

  $token_endpoint = $server_url . '/oauth2/token';
  $authorization_endpoint = $server_url . '/oauth2/authorize';
  $redirect_uri = url('oauth2/authorized', array('absolute' => TRUE));

  $auth_settings['authentication']['oauth2'] = array(
    'token_endpoint' => $token_endpoint,
    'auth_flow' => 'server-side',
    'client_id' => $client_id,
    'client_secret' => $client_secret,
    'redirect_uri' => $redirect_uri,
    'authorization_endpoint' => $authorization_endpoint,
    'scope' => 'user_profile',
  );

  return $auth_settings;
}

/**
 * Return definitions for operations about translations.
 */
function _btrClient_services_authenticated_translations() {
  $operations['get_translations'] = array(
    'label' => 'get_translations',
    'url' => 'translations/@sguid',
    'parameter' => array(
      'sguid' => array('type' => 'text'),
      'lng' => array('type' => 'text'),
    ),
  );

  $POST_operations = array(
    'search' => 'translations/search',
    'get_random_sguid' => 'translations/get_random_sguid',
    'add_translation' => 'translations/add',
    'add_vote' => 'translations/vote',
    'del_translation' => 'translations/del',
    'del_vote' => 'translations/del_vote',
    'submit' => 'translations/submit',
    //'import_translations' => 'translations/import',
  );
  foreach($POST_operations as $name  => $url) {
    $operations[$name] = array(
      'label' => $name,
      'url' => $url,
      'type' => 'POST',
      'data' => 'params',
      'parameter' => array(
        'params' => array('type' => 'array'),
      ),
    );
  }

  return $operations;
}

/**
 * Return definitions for operations about projects.
 */
function _btrClient_services_authenticated_projects() {
  $POST_operations = array(
    'export_projects' => 'project/export',
    'add_string' => 'project/add_string',
    'del_string' => 'project/del_string',
  );
  foreach($POST_operations as $name  => $url) {
    $operations[$name] = array(
      'label' => $name,
      'url' => $url,
      'type' => 'POST',
      'data' => 'params',
      'parameter' => array(
        'params' => array('type' => 'array'),
      ),
    );
  }

  return $operations;
}