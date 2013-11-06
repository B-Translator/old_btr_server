#!/usr/bin/drush php-script
<?php

// general contribution statistics
$url = 'https://dev.l10n.org.xx/public/btr/report/statistics?lng=sq';
$response = drupal_http_request($url);
print_r($response);

// top contributors
$url = 'https://dev.l10n.org.xx/public/btr/report/topcontrib'
  . '?lng=sq&period=week&size=5';
$options = array(
  'headers' => array('Accept' => 'application/xml'),
);
$response = drupal_http_request($url, $options);
print_r($response);
