#!/bin/bash

### get config settings from a file
if [ "$1" != '' ]
then
    settings=$1
    set -a
    source  $settings
    set +a
fi

### install dirs of the btr_server and btr_client
btr=/var/www/btr/profiles/btr_server/install
bcl=/var/www/bcl/profiles/btr_client/install

### configure domains
$btr/config/domain.sh

### set new passwords for mysql users
$btr/config/mysql_passwords.sh
$bcl/config/mysql_btrclient.sh
$btr/config/mysql_btrserver.sh

### setup SMTP through a gmail account
$btr/config/gmailsmtp.sh

### set new password for drupal user 'admin'
### on btr_server and btr_client
$bcl/config/drupalpass.sh
$btr/config/drupalpass.sh

### set the translation language for B-Translator Client
$bcl/config/languages.sh

### configurations for oauth2 login
$btr/config/oauth2_login.sh

### drush may create some css/js files with wrong permissions
### clean them up
rm -rf /var/www/btr/sites/default/files/*
rm -rf /var/www/bcl/sites/default/files/*

### make clones btr_dev and bcl_dev
$btr/../dev/make-dev-clone.sh
$bcl/../dev/make-dev-clone.sh

$btr/config/mysqld.sh stop
