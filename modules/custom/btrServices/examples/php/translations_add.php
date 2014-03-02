<?php
include_once(dirname(__FILE__) . '/config.php');
include_once(dirname(__FILE__) . '/get_access_token.php');
include_once(dirname(__FILE__) . '/http_request.php');

$sguid = '2a12b39f41bbd1ac78fdf456c25a480d2060c06b';

// Get an access  token.
$access_token = get_access_token($auth);

// POST btr/translations/add
$url = $base_url . '/btr/translations/add';
$options = array(
  'method' => 'POST',
  'data' => array(
    'sguid' => $sguid,
    'lng' => 'sq',
    'translation' => 'test-translation-' . rand(1, 10),
  ),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
    'Authorization' => 'Bearer ' . $access_token,
  ),
);
$result = http_request($url, $options);
$tguid = $result->tguid;

// Retrive the string and check that the new translation has been added.
$url = $base_url . "/public/btr/translations/$sguid?lng=sq";
$result = http_request($url);

// Delete the translation that was added above.
$url = $base_url . '/btr/translations/del';
$options = array(
  'method' => 'POST',
  'data' => array('tguid' => $tguid),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
    'Authorization' => 'Bearer ' . $access_token,
  ),
);
$result = http_request($url, $options);
