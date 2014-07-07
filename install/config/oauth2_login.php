<?php
/**
 * Set drupal variables and configurations related
 * to OAuth2 Login and to B-Translator Server.
 * Takes these arguments:
 *   server_url, client_id, client_secret, skip_ssl
 */

$server_url = drush_shift();
$client_id = drush_shift();
$client_secret = drush_shift();
$skip_ssl = drush_shift();

// Set configuration variables of oauth2_login.
variable_set('oauth2_login_oauth2_server', $server_url);
variable_set('oauth2_login_client_id', $client_id);
variable_set('oauth2_login_client_secret', $client_secret);
variable_set('oauth2_login_skipssl', $skip_ssl);

// Set the B-Translator API server
variable_set('btrClient_server', $server_url);

// Enable the oauth2 login link and set the settings to hybridauth.
variable_set('oauth2_login_enabled', TRUE);
module_load_include('inc', 'oauth2_login', 'oauth2_login.admin');
oauth2_login_admin_set_settings();
oauth2_login_call_hook_enabled();
