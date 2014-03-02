<?php
include_once(dirname(__FILE__) . '/config.php');

/**
 * Function for making http requests.
 */
function http_request($url, $options =array()) {
  if (defined('DEBUG')) {
    if (php_sapi_name() != "cli")  print '<xmp>';
    print "\n--------------- start http_request ----------------------------\n";
    print "===> URL: $url\n";
    print "===> OPTIONS\n";
    print_r($options);
    flush();
  }

  // get the headers
  $header = '';
  if (isset($options['headers']) and is_array($options['headers'])) {
    foreach ($options['headers'] as $name => $value) {
      $header .= "$name: $value\r\n";
    }
  }

  // create the context options
  if (isset($options['method']) and ($options['method'] == 'POST')) {
    $data = $options['data'];
    if (is_array($data))  $data = http_build_query($data);
    $header .= "Content-Length: " . strlen($data) . "\r\n";

    $context_options = array (
      'http' => array (
        'method' => 'POST',
        'header'=> $header,
        'content' => $data,
      ));
  }
  else {
    $context_options = array (
      'http' => array (
        'method' => 'GET',
        'header'=> $header,
      ));
  }

  // make the request and get the result
  $context = stream_context_create($context_options);
  $result = file_get_contents($url, false, $context);
  $result = json_decode($result, true);

  if (defined('DEBUG')) {
    print "===> RESULT\n";
    print_r($result);
    print "--------------- end http_request ------------------------------\n";
    if (php_sapi_name() != "cli")  print '</xmp>';
    flush();
  }

  return $result;
}