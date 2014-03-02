<?php
include_once(dirname(__FILE__) . '/config.php');
include_once(dirname(__FILE__) . '/get_access_token.php');
include_once(dirname(__FILE__) . '/http_request.php');

// Get a random translated string.
$url = $base_url . '/public/btr/translations/translated?lng=sq';
$result = http_request($url);

// Get the tguid of the first translation.
foreach ($result as $sguid => $string) {
  foreach ($string['translations'] as $tguid => $translation) {
    break;
  }
  break;
}

// Get an access  token.
$access_token = get_access_token($auth);

// POST btr/translations/vote
$url = $base_url . '/btr/translations/vote';
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
$url = $base_url . "/public/btr/translations/$sguid?lng=sq";
$result = http_request($url);

// POST btr/translations/del_vote
$url = $base_url . '/btr/translations/del_vote';
$options = array(
  'method' => 'POST',
  'data' => array('tguid' => $tguid),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
    'Authorization' => 'Bearer ' . $access_token,
  ),
);
$result = http_request($url, $options);
