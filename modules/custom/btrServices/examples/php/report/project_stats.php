<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');

// GET btr/report/project_stats
$url = $base_url . '/btr/report/project_stats?origin=vocabulary&project=ICT_sq&lng=sq';
$result = http_request($url);

// POST btr/report/project_stats
$url = $base_url . '/btr/report/project_stats';
$options = array(
  'method' => 'POST',
  'data' => array(
    'origin' => 'vocabulary',
    'project' => 'ICT_sq',
    'lng' => 'sq',
  ),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
  ),
);
$result = http_request($url, $options);
