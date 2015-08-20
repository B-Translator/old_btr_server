#!/usr/bin/drush php-script
<?php

$url = 'https://dev.btr.example.org/api/report/topcontrib.json';
$params = array(
  'lng' => 'sq',
  'period' => 'week',
  'size' => 10,
);
$options = array(
  'method' => 'POST',
  'data' => http_build_query($params),
);

$response = drupal_http_request($url, $options);
print_r($response);
