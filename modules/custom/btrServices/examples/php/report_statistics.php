<?php
include_once(dirname(__FILE__) . '/config.php');
include_once(dirname(__FILE__) . '/http_request.php');

// GET public/btr/report/statistics
$url = $base_url . '/public/btr/report/statistics?lng=sq';
$result = http_request($url);

// GET public/btr/report/topcontrib
$url = $base_url . '/public/btr/report/topcontrib?lng=sq&period=week';
$result = http_request($url);

// POST public/btr/report/statistics
$url = $base_url . '/public/btr/report/statistics';
$options = array(
  'method' => 'POST',
  'data' => array('lng' => 'sq'),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
  ),
);
$result = http_request($url, $options);

// POST public/btr/report/topcontrib
$url = $base_url . '/public/btr/report/topcontrib';
$options = array(
  'method' => 'POST',
  'data' => array(
    'lng' => 'sq',
    'period' => 'week',
  ),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
  ),
);
$result = http_request($url, $options);
