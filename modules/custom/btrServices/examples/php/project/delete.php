<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');
include_once($path . '/get_access_token.php');

// Get an access  token.
$access_token = get_access_token($auth);

// POST api/project/delete
$url = $base_url . '/api/project/delete';
$options = [
  'method' => 'POST',
  'data' => [
    'origin' => 'test1',
    'project' => 'kturtle',
  ],
  'headers' => [
    'Content-type' => 'application/x-www-form-urlencoded',
    'Authorization' => 'Bearer ' . $access_token,
  ],
];
$result = http_request($url, $options);

// Try to delete project 'test/kturtle'.
$options['data']['origin'] = 'test';
$result = http_request($url, $options);
