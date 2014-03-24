<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');

// POST public/btr/translations/get
$url = $base_url . '/public/btr/translations/get';
$options = array(
  'method' => 'POST',
  'data' => array(
    'sguid' => 'ed685775fa0608fa42e20b3d28454c63972f62cd',
    'lng' => 'sq',
  ),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
  ),
);
$result = http_request($url, $options);

$options['data']['sguid'] = 'next';
$result = http_request($url, $options);

$options['data']['sguid'] = 'translated';
$result = http_request($url, $options);

$options['data']['sguid'] = 'untranslated';
$result = http_request($url, $options);
