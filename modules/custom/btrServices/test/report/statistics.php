#!/usr/bin/drush php-script
<?php

$url = 'https://dev.l10n.org.xx/public/btr/report/statistics.json';
$options = array(
  'method' => 'POST',
  'data' => 'lng=sq',
);
$response = drupal_http_request($url, $options);
print_r($response);
