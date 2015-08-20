<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');

// GET api/translations
$url = $base_url . '/api/translations?lng=sq&words=file&page=2';
$result = http_request($url);
