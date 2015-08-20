#!/usr/bin/drush php-script
<?php

///////////////////////////////////////////////////
// get translations from the public endpoint
// (no need for authentication or token)

$url = "https://dev.btr.example.org/api/translations/5aa37d12b93b15ea4bbf49b5eb234d70154710ab?lng=sq";
$response = drupal_http_request($url);
print "\n\n===================================================\n\n";
print_r($response);

$url = "https://dev.btr.example.org/api/translations/random?lng=sq";
$response = drupal_http_request($url);
print "\n\n===================================================\n\n";
print_r($response);

$url = "https://dev.btr.example.org/api/translations/translated?lng=sq";
$response = drupal_http_request($url);
print "\n\n===================================================\n\n";
print_r($response);

$url = "https://dev.btr.example.org/api/translations/untranslated?lng=sq";
$response = drupal_http_request($url);
print "\n\n===================================================\n\n";
print_r($response);


///////////////////////////////////////////////////////////////
// get an access token with password authentication

$token_url = 'https://dev.btr.example.org/oauth2/token';
//$token_url = url('oauth2/token', array('absolute' => TRUE));
$data = array(
  'grant_type' => 'password',
  'username' => 'user1',
  'password' => 'user1',
  //'scope' => 'basic',
);
$options = array(
  'method' => 'POST',
  'data' => http_build_query($data),
  'headers' => array(
    'Content-Type' => 'application/x-www-form-urlencoded',
    'Authorization' => 'Basic ' . base64_encode('test1:test1'),
  ),
  'max_redirects' => 0,
);
$result = drupal_http_request($token_url, $options);
$response = json_decode($result->data);
$access_token = $response->access_token;
print "\n\n===================================================\n\n";
print "access_token = $access_token\n\n";


//////////////////////////////////////////////////////////////////
// get translations from the endpoint with oauth2 authentication
// sending the access token in the query string

$url = "https://dev.btr.example.org/api/translations/random?lng=sq&access_token=$access_token";
$response = drupal_http_request($url);
print "\n\n===================================================\n\n";
print_r($response);


//////////////////////////////////////////////////////////////////
// get translations from the endpoint with oauth2 authentication
// sending the access token in the 'Authorization' header

$url = 'https://dev.btr.example.org/api/translations/random?lng=sq';
$options = array(
  'headers' => array(
    //'Accept' => 'application/xml',
    'Authorization' => 'Bearer ' . $access_token,
  ),
);
$response = drupal_http_request($url, $options);
print "\n\n===================================================\n\n";
print_r($response);
