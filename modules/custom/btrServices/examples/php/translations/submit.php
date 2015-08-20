<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');
include_once($path . '/get_access_token.php');

// Get an access  token.
$access_token = get_access_token($auth);

// Actions that will be submitted.
$actions = array(
  array(
    'action' => 'add',
    'params' => array(
      'sguid' => 'd66b0fc286b887e9242ee1e6b777522f067f92af',
      'lng' => 'sq',
      'translation' => 'Test translation.',
    ),
  ),
  array(
    'action' => 'vote',
    'params' => array('tguid' => '40af5f58a7d1211c0cb5950d0b36b21c06cf50e6'),
  ),
  array(
    'action' => 'del',
    'params' => array('tguid' => 'test-f58a7d1211c0cb5950d0b36b21c06cf50e6'),
  ),
  array(
    'action' => 'del_vote',
    'params' => array('tguid' => 'test-f58a7d1211c0cb5950d0b36b21c06cf50e6'),
  ),
  array(
    'action' => 'add',
    'params' => array(
      'sguid' => 'd68b68585ee36d0bcda3dd3fd6eb4ebc2cdcbcbd',
      'lng' => 'sq',
      'translation' => '',
    ),
  ),
);

// POST api/translations/submit
$url = $base_url . '/api/translations/submit';
$options = array(
  'method' => 'POST',
  'data' => $actions,
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
    'Authorization' => 'Bearer ' . $access_token,
  ),
);
$result = http_request($url, $options);
