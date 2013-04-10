#!/bin/bash

cwd=$(dirname $0)

$cwd/config/domain.sh
$cwd/config/mysql_passwords.sh
$cwd/config/mysql_btranslator.sh
$cwd/config/gmailsmtp.sh
$cwd/config/drupalpass.sh
$cwd/config/languages.sh

rm -rf /var/www/btranslator/sites/default/files/css/

service mysql stop