<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');

// GET btr/translations
$url = $base_url . '/btr/translations/ed685775fa0608fa42e20b3d28454c63972f62cd?lng=sq';
$result = http_request($url);
$url = $base_url . '/btr/translations/random?lng=sq';
$result = http_request($url);
$url = $base_url . '/btr/translations/translated?lng=sq';
$result = http_request($url);
$url = $base_url . '/btr/translations/untranslated?lng=sq';
$result = http_request($url);
