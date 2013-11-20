#!/usr/bin/drush php-script
<?php
//$btr = wsclient_service_load('public_btr');

//$sguid = '5aa37d12b93b15ea4bbf49b5eb234d70154710ab';
//$result = $btr->get_translations($sguid, 'sq');
//$result = $btr->get_translations('next', 'sq');
//$result = $btr->get_translations('translated', 'sq');
//$result = $btr->get_translations('untranslated', 'sq');
//print_r($result);

$btr = wsclient_service_load('btr');

$sguid = '5aa37d12b93b15ea4bbf49b5eb234d70154710ab';
$result = $btr->get_translations($sguid, 'sq');
//$result = $btr->get_translations('next', 'sq');
//$result = $btr->get_translations('translated', 'sq');
//$result = $btr->get_translations('untranslated', 'sq');
print_r($result);
