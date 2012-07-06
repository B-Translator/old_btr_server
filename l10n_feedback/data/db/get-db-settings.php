#!/usr/bin/env drush
<?php
$db = $GLOBALS['databases']['default']['default'];

$dbdriver = $db['driver'];
$dbhost = $db['host'];
$dbname = $db['database'];
$dbuser = $db['username'];
$dbpass = $db['password'];

print "<?php
\$dbdriver = '$dbdriver';
\$dbhost   = '$dbhost';
\$dbname   = '$dbname';
\$dbuser   = '$dbuser';
\$dbpass   = '$dbpass';
?>";

?>
