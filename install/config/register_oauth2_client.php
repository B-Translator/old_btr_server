<?php
/**
 * Register an OAuth2 client.
 * Takes these arguments:
 *   client_key, client_secret, redirect_uri
 */

$client_key = drush_shift();
$client_secret = drush_shift();
$redirect_uri = drush_shift();

// Delete the client if already exists.
$query = new EntityFieldQuery();
$clients = $query->entityCondition('entity_type', 'oauth2_server_client')
  ->propertyCondition('server', 'oauth2')
  ->propertyCondition('client_key',  $client_key)
  ->execute();
if (isset($clients['oauth2_server_client'])) {
  $cids = array_keys($clients['oauth2_server_client']);
  foreach ($cids as $cid) {
    entity_delete('oauth2_server_client', $cid);
  }
}

// Register a client on the oauth2 server.
$client = entity_create('oauth2_server_client', array());
$client->server = 'oauth2';
$client->label = $client_key;
$client->client_key = $client_key;
$client->client_secret = $client_secret;
$client->redirect_uri = $redirect_uri;
$client->automatic_authorization = TRUE;
$client->save();
