<?php
@include_once(dirname(__FILE__).'/settings.php');
$db = $databases['default']['default'];

$dbdriver = $db['driver'];
$dbhost = $db['host'];
$dbname = $db['database'];  //$dbname = 'l10nsq_test';  //debug
$dbuser = $db['username'];
$dbpass = $db['password'];

if (isset($argv[1]) && $argv[1] == 'bash')
  {
    if ($dbdriver == 'mysql') {
      print "--host=$dbhost --database=$dbname --user=$dbuser --password=$dbpass";
    }
  }
?>
