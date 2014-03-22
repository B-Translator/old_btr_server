<?php
include_once(dirname(__FILE__) . '/config.php');
include_once(dirname(__FILE__) . '/get_access_token.php');
include_once(dirname(__FILE__) . '/http_request.php');

// Get an access  token.
$access_token = get_access_token($auth);

// POST btr/project/export
$url = $base_url . '/btr/project/export';
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
