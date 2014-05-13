#!/bin/bash

btr=/var/www/btr/profiles/btr_server/install
bcl=/var/www/bcl/profiles/btr_client/install

$btr/config/domain.sh

$btr/config/mysql_passwords.sh
$bcl/config/mysql_btrclient.sh
$btr/config/mysql_btrserver.sh

$btr/config/gmailsmtp.sh

$bcl/config/drupalpass.sh
$btr/config/drupalpass.sh

$bcl/config/languages.sh
$btr/config/languages.sh

### drush may create some css/js files with wrong permissions
### clean them up
rm -rf /var/www/btr/sites/default/files/*

$btr/../dev/make-dev-clone.sh
$bcl/../dev/make-dev-clone.sh

$btr/config/mysqld.sh stop
