<?php
/**
 * Define web services.
 */

/**
 * Implements hook_default_wsclient_service().
 *
 * Defines web service descriptions (one public and one private).
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
  module_load_include('inc', 'btrClient', 'services/public');
  module_load_include('inc', 'btrClient', 'services/authenticated');

  $services['public_btr'] = _btrClient_services_public_service('public_btr');
  $services['btr'] = _btrClient_services_authenticated_service('btr');
  return $services;
}

/**
 * Set curl options for development, testing and debug.
 */
function _btrClient_services_dev_settings() {
  $skipssl = variable_get('oauth2_login_skipssl', TRUE);
  $proxy = variable_get('oauth2_login_proxy', '');

  $dev_settings = array();
  if ($skipssl) {
    // skip checking the SSL certificate, for testing
    $dev_settings['curl options'] = array(
      CURLOPT_SSL_VERIFYPEER => FALSE,
      CURLOPT_SSL_VERIFYHOST => FALSE,
    );
  }
  if ($proxy) {
    $dev_settings['curl options'][CURLOPT_PROXY] = $proxy;
  }
  return $dev_settings;
}
