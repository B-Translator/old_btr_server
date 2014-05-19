#!/bin/bash

echo "===> Making configurations for OAuth2 Login"

### get the domain name of btr_client and btr_server
btrclient=$(grep ' localhost' /etc/hosts | head -n 1 | cut -d' ' -f2)
btrserver=$(grep ' localhost' /etc/hosts | head -n 1 | cut -d' ' -f3)

### configuration variables
server_url=https://$btrserver
client_id='local_client'
client_secret=$(mcookie)
redirect_url=https://$btrclient/oauth2/authorized
skip_ssl=1

### register an oauth2 client on btr_server
btr=/var/www/code/btr_server/install/config
$btr/mysqld.sh start
drush --yes @btr php-script --script-path=$btr register_oauth2_client.php  \
    "$client_id" "$client_secret" "$redirect_url"
drush @btr cc all

### setup oauth2 login on btr_client
bcl=/var/www/code/btr_client/install/config
#$bcl/mysqld.sh start
drush --yes @bcl php-script --script-path=$bcl oauth2_login.php  \
    "$server_url" "$client_id" "$client_secret" "$skip_ssl"
drush @bcl cc all

### drush may create css/js files with wrong(root) permissions
rm -rf /var/www/{btr,bcl}/sites/default/files/*
