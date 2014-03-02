<?php
include_once(dirname(__FILE__) . '/config.php');
include_once(dirname(__FILE__) . '/http_request.php');

// GET public/btr/translations
$url = $base_url . '/public/btr/translations?lng=sq&words=file&page=2';
$result = http_request($url);
