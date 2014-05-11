#!/bin/bash

btr=/var/www/btr/install
bcl=/var/www/bcl/install

$btr/config/domain.sh
$bcl/config/domain.sh

$btr/config/mysql_passwords.sh
$bcl/config/mysql_passwords.sh

$btr/config/mysql_btrserver.sh
$bcl/config/mysql_btrserver.sh

$btr/config/gmailsmtp.sh

$btr/config/drupalpass.sh
$btr/config/drupalpass.sh

$btr/config/languages.sh

### drush may create some css/js files with wrong permissions
### clean them up
rm -rf /var/www/btr/sites/default/files/*

$btr/../dev/make-dev-clone.sh

$btr/config/mysqld.sh stop
