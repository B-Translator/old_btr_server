<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');
include_once($path . '/get_access_token.php');

// Get an access  token.
$access_token = get_access_token($auth);

// POST api/project/import
$url = $base_url . '/api/project/import';

$ch = curl_init($url);
curl_setopt_array($ch, array(
    CURLOPT_POST => TRUE,
    CURLOPT_POSTFIELDS => array(
      'origin' => 'test1',
      'project' => 'pingus',
      'file' => '@'.dirname(__FILE__).'/pingus-sq.po;filename=test-pingus-sq.po',
    ),
    CURLOPT_HTTPHEADER => array(
      'Content-Type: multipart/form-data',
      'Authorization: Bearer ' . $access_token,
      'Accept: application/json',
    ),
    CURLOPT_RETURNTRANSFER => TRUE,
    CURLOPT_SSL_VERIFYPEER => FALSE,
    CURLOPT_SSL_VERIFYHOST => 0,
  )
);
$result = curl_exec($ch);

print "===> RESULT\n";

// Check for any errors and get the result.
if (curl_errno($ch)) {
  $result .= "\n\nError: " . curl_error($ch);
}
else {
  $result = json_decode($result, TRUE);
}
print '<xmp>';
print_r($result);
print '</xmp>';

curl_close($ch);
