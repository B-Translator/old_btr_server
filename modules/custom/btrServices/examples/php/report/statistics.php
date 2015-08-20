<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');

// GET btr/report/statistics
$url = $base_url . '/btr/report/statistics?lng=sq';
$result = http_request($url);

// POST btr/report/statistics
$url = $base_url . '/btr/report/statistics';
$options = array(
  'method' => 'POST',
  'data' => array('lng' => 'sq'),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
  ),
);
$result = http_request($url, $options);
