<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');

// GET project/list/all
http_request($base_url . '/project/list/all');
