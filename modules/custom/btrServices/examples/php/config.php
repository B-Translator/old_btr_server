<?php

define('DEBUG', TRUE);

$base_url = 'https://dev.l10n.org.al';

$auth = array(
  'token_url' => $base_url . '/oauth2/token',
  'client_id' => 'emberjs',
  'client_secret' => '123456',
  'username' => 'user1',
  'password' => 'pass1',
  'scope' => 'user_profile',
);
