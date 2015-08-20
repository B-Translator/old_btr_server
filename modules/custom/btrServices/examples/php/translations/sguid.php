<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');

// POST api/translations/get_random_sguid
$url = $base_url . '/api/translations/get_random_sguid';
$options = array(
  'method' => 'POST',
  'data' => array(
    'target' => 'random',
  ),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
  ),
);
$result = http_request($url, $options);

$options = array(
  'method' => 'POST',
  'data' => array(
    'target' => 'translated',
    'lng' => 'sq',
  ),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
  ),
);
$result = http_request($url, $options);

$options = array(
  'method' => 'POST',
  'data' => array(
    'target' => 'random',
    'scope' => 'vocabulary/ICT_sq',
  ),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
  ),
);
$result = http_request($url, $options);
