<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');
include_once($path . '/get_access_token.php');

// Get a random translated string.
$url = $base_url . '/api/translations/translated?lng=sq';
$result = http_request($url);

// Get the sguid and the tguid of the first translation.
$sguid = $result['string']['sguid'];
$tguid = $result['string']['translations'][0]['tguid'];

// Get an access  token.
$access_token = get_access_token($auth);

// POST api/translations/vote
$url = $base_url . '/api/translations/vote';
$options = array(
  'method' => 'POST',
  'data' => array('tguid' => $tguid),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
    'Authorization' => 'Bearer ' . $access_token,
  ),
);
$result = http_request($url, $options);

// Retrive the string and check that the translation has been voted.
$url = $base_url . "/api/translations/$sguid?lng=sq";
$result = http_request($url);

// POST api/translations/del_vote
$url = $base_url . '/api/translations/del_vote';
$options = array(
  'method' => 'POST',
  'data' => array('tguid' => $tguid),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
    'Authorization' => 'Bearer ' . $access_token,
  ),
);
$result = http_request($url, $options);
