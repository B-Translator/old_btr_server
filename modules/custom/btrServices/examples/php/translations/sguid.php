<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');

// POST public/btr/translations/get_random_sguid
$url = $base_url . '/public/btr/translations/get_random_sguid';
$options = array(
  'method' => 'POST',
  'data' => array(
    'target' => 'next',
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
    'target' => 'translated',
    'lng' => 'sq',
    'last_sguid' => 'c7ac448a01c566680d8ffb00430a55ffc779f24b',
  ),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
  ),
);
$result = http_request($url, $options);

$options = array(
  'method' => 'POST',
  'data' => array(
    'target' => 'next',
    'last_sguid' => 'c7ac448a01c566680d8ffb00430a55ffc779f24b',
  ),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
  ),
);
$result = http_request($url, $options);
