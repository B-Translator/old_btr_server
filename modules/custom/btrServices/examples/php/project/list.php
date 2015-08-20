<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');

// POST api/project/list
$url = $base_url . '/api/project/list';
$options = array(
  'method' => 'POST',
  'data' => array(),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
  ),
);
$result = http_request($url, $options);

// Filter list by origin.
$options['data'] = array('origin' => 't*');
$result = http_request($url, $options);

// Retrieve only a list of origins.
$options['data'] = array('project' => '-');
$result = http_request($url, $options);

// Filter list by origin.
$options['data'] = array('origin' => 'test', 'project' => 'p*');
$result = http_request($url, $options);
