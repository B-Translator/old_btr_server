<?php
include_once(dirname(__FILE__) . '/config.php');
include_once(dirname(__FILE__) . '/http_request.php');

/**
 * Get an access token with password authentication.
 */
function get_access_token($params) {
  $options = array(
    'method' => 'POST',
    'data' => array(
      'grant_type' => 'password',
      'username' => $params['username'],
      'password' => $params['password'],
      'scope' => $params['scope'],
    ),
    'headers' => array(
      'Content-type' => 'application/x-www-form-urlencoded',
      'Authorization' => 'Basic ' . base64_encode($params['client_id'] . ':' . $params['client_secret']),
    ),
  );
  $result = http_request($params['token_url'], $options);
  $result = json_decode($result);
  //print_r($result);
  return $result->access_token;
}

$access_token = get_access_token($auth);
print "\naccess_token = $access_token\n";
//print "\n===================================================\n";
