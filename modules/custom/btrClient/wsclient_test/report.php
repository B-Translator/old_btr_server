#!/usr/bin/drush php-script
<?php
$btr = wsclient_service_load('public_btr');

//$result = $btr->report_statistics('sq');
$result = $btr->report_topcontrib('sq', 'week', 5);
//$result = $btr->report_statistics_1(array('lng' => 'sq'));
//$params = array('lng'=>'sq', 'period'=>'week', 'size'=>5);
//$result = $btr->report_topcontrib_1($params);

print_r($result);
