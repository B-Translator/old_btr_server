#!/bin/bash -x

### get config settings from a file
if [ "$1" != '' ]
then
    settings=$1
    set -a
    source  $settings
    set +a
fi

### install dirs of the btr_server and btr_client
btr=/usr/local/src/btr_server/install
bcl=/usr/local/src/btr_client/install

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

### configurations for oauth2 login
$btr/config/oauth2_login.sh @bcl @btr

### configure languages
$bcl/config/translation_lng.sh
$btr/config/languages.sh

### update sites.inc
$btr/config/update_sites.sh $translation_lng https://$bcl_domain

### regenerate ssh keys
$btr/config/ssh_keys.sh

### make clones btr_dev and bcl_dev
if [ "$development" = 'true' ]
then
    $btr/../dev/make-dev-clone.sh
    $bcl/../dev/make-dev-clone.sh
    $btr/config/oauth2_login.sh @bcl_dev @btr_dev
fi

### drush may create some css/js files with wrong permissions
chown www-data: -R /var/www/{btr,bcl}*/sites/default/files/{css,js}

### stop mysql
$btr/config/mysqld.sh stop
