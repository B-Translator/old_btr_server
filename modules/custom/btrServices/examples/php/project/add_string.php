<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');
include_once($path . '/get_access_token.php');

// Get an access  token.
$access_token = get_access_token($auth);

// POST btr/project/add_string
$url = $base_url . '/btr/project/add_string';
$options = array(
  'method' => 'POST',
  'data' => array(
    'origin' => 'test',
    'project' => 'pingus',
    'string' => 'Test string ' . rand(1, 10),
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
$sguid = $result['sguid'];

// Retrive the string.
$url = $base_url . "/public/btr/translations/$sguid?lng=sq";
$result = http_request($url);

// Delete the string that was added above.
$url = $base_url . '/btr/project/del_string';
$options = array(
  'method' => 'POST',
  'data' => array('sguid' => $sguid),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
    'Authorization' => 'Bearer ' . $access_token,
  ),
);
$result = http_request($url, $options);
