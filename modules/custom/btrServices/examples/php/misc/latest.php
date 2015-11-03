<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');

// Get the latest translations as a list in JSON format.
http_request('https://btranslator.org/latest/sq');
//http_request('https://btranslator.org/latest/sq/KDE');
//http_request('https://btranslator.org/latest/sq/KDE/kdeedu');
