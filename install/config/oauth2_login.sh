#!/bin/bash

### get the aliases for the client and for the server
if [ $# -ne 2 ]
then
    echo "Usage: $0 @bcl_alias @btr_alias"
    exit 1
fi
bcl_alias=$1
btr_alias=$2

echo "===> Making configurations for OAuth2 Login"

### get client url and server url
bcl_url=$(drush $bcl_alias php-eval 'print $GLOBALS["base_url"]')
btr_url=$(drush $btr_alias php-eval 'print $GLOBALS["base_url"]')

### configuration variables
server_url=$btr_url
client_id='localclient'
client_secret=$(mcookie)
redirect_url=$bcl_url/oauth2/authorized
skip_ssl=1

### register an oauth2 client on btr_server
btr=/usr/local/src/btr_server/install/config
drush --yes $btr_alias \
    php-script --script-path=$btr register_oauth2_client.php  \
    "$client_id" "$client_secret" "$redirect_url"
drush $btr_alias cc all

### setup oauth2 login on btr_client
bcl=/usr/local/src/btr_client/install/config
drush --yes $bcl_alias \
    php-script --script-path=$bcl oauth2_login.php  \
    "$server_url" "$client_id" "$client_secret" "$skip_ssl"
drush $bcl_alias cc all

### set the variable btr_client of the server
drush --yes $btr_alias vset btr_client "$bcl_url"
