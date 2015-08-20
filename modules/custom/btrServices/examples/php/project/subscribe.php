<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');
include_once($path . '/get_access_token.php');

// Get an access  token.
$access_token = get_access_token($auth);

// POST api/project/subscribe
$url = $base_url . '/api/project/subscribe';
$options = array(
  'method' => 'POST',
  'data' => array(
    'origin' => 'test',
    'project' => 'pingus',
  ),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
    'Authorization' => 'Bearer ' . $access_token,
  ),
);
try {
  $result = http_request($url, $options);
}
catch (Exception $e) {
  print '<xmp>';
  print $e->getMessage();
  print '</xmp>';
}

// POST api/project/subscriptions
$url = $base_url . '/api/project/subscriptions';
$options = array(
  'method' => 'POST',
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
    'Authorization' => 'Bearer ' . $access_token,
  ),
);
try {
  $result = http_request($url, $options);
}
catch (Exception $e) {
  print '<xmp>';
  print $e->getMessage();
  print '</xmp>';
}

// POST api/project/unsubscribe
$url = $base_url . '/api/project/unsubscribe';
$options = array(
  'method' => 'POST',
  'data' => array(
    'origin' => 'test',
    'project' => 'pingus',
  ),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
    'Authorization' => 'Bearer ' . $access_token,
  ),
);
try {
  $result = http_request($url, $options);
}
catch (Exception $e) {
  print '<xmp>';
  print $e->getMessage();
  print '</xmp>';
}

// POST api/project/subscriptions
$url = $base_url . '/api/project/subscriptions';
$options = array(
  'method' => 'POST',
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
    'Authorization' => 'Bearer ' . $access_token,
  ),
);
try {
  $result = http_request($url, $options);
}
catch (Exception $e) {
  print '<xmp>';
  print $e->getMessage();
  print '</xmp>';
}
