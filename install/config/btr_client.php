<?php
$client_secret = drush_shift();

// delete the client if already exists
$query = new EntityFieldQuery();
$clients = $query->entityCondition('entity_type', 'oauth2_server_client')
  ->propertyCondition('server', 'oauth2_btr')
  ->propertyCondition('label',  'btrClient')
  ->propertyCondition('client_key',  'btrClient')
  ->execute();
if (isset($clients['oauth2_server_client'])) {
  $cids = array_keys($clients['oauth2_server_client']);
  foreach ($cids as $cid) {
    entity_delete('oauth2_server_client', $cid);
  }
}

// register a client on the 'oauth2_btr' server
$client = entity_create('oauth2_server_client', array());
$client->server = 'oauth2_btr';
$client->label = 'btrClient';
$client->client_key = 'btrClient';
$client->client_secret = $client_secret;
$client->redirect_uri = url('oauth2/authorized', array('absolute' => TRUE));
$client->automatic_authorization = TRUE;
$client->save();

// set btrClient variables
global $base_url;
variable_set('btrClient_server_url', $base_url);
variable_set('btrClient_client_id', 'btrClient');
variable_set('btrClient_client_secret', $client_secret);
variable_set('btrClient_skip_ssl_check', TRUE);
?>