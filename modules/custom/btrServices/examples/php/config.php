<?php
if (php_sapi_name() != "cli") {
  highlight_file($_SERVER["SCRIPT_FILENAME"]);
  flush();
}

define('DEBUG', TRUE);

$base_url = 'http://dev.btranslator.org';
//$base_url = 'https://dev.btr.example.org';

$auth = array(
  'token_url' => $base_url . '/oauth2/token',
  'client_id' => 'test1',
  'client_secret' => '12345',
  'username' => 'user1',
  'password' => 'pass1',
  'scope' => 'user_profile',
);
