#!/bin/bash

cwd=$(dirname $0)

$cwd/config/domain.sh
$cwd/config/mysql_passwords.sh
$cwd/config/mysql_btranslator.sh
$cwd/config/gmailsmtp.sh
$cwd/config/drupalpass.sh
$cwd/config/languages.sh

$cwd/config/mysqld.sh stop

rm -rf /var/www/btr/sites/default/files/css/
rm -rf /var/www/btr/sites/default/files/js/
