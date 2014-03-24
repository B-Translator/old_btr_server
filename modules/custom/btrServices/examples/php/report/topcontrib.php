<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');

// GET public/btr/report/topcontrib
$url = $base_url . '/public/btr/report/topcontrib?lng=sq&period=week';
$result = http_request($url);

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
