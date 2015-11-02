<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');

// GET vocabulary/list
$url = $base_url . '/vocabulary/list';
http_request($url);
http_request('https://btranslator.org/vocabulary/list');
