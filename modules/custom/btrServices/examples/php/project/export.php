<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');
include_once($path . '/get_access_token.php');

// Get an access  token.
$access_token = get_access_token($auth);

// POST api/project/export
$url = $base_url . '/api/project/export';
$options = array(
  'method' => 'POST',
  'data' => array(
    'origin' => 'test',
    'project' => 'kturtle',
    //'export_mode' => 'preferred_by_me',
  ),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
    'Authorization' => 'Bearer ' . $access_token,
  ),
);
$result = http_request($url, $options);
