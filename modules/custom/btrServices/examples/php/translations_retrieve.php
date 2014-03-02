<?php
include_once(dirname(__FILE__) . '/config.php');
include_once(dirname(__FILE__) . '/http_request.php');

// GET public/btr/translations
$url = $base_url . '/public/btr/translations/ed685775fa0608fa42e20b3d28454c63972f62cd?lng=sq';
$result = http_request($url);
$url = $base_url . '/public/btr/translations/next?lng=sq';
$result = http_request($url);
$url = $base_url . '/public/btr/translations/translated?lng=sq';
$result = http_request($url);
$url = $base_url . '/public/btr/translations/untranslated?lng=sq';
$result = http_request($url);

