#!/bin/bash

echo "
===> Set the domain name (fqdn) of the server

This is the domain that you have registered
(or plan to register) for the B-Translator.

It will modify the files:
 1) /etc/hostname
 2) /etc/hosts
 3) /etc/nginx/sites-available/default
 4) /var/www/btranslator/sites/default/settings.php
"
FQDN='l10n.org.xx'
read -p "Enter the domain [$FQDN]: " input
FQDN=${input:-$FQDN}

echo $FQDN > /etc/hostname
sed -e "/^127.0.1.1/c 127.0.1.1 $FQDN btranslator" -i /etc/hosts

config_file=/etc/nginx/sites-available/default
sed -e "s/server_name .*\$/server_name $FQDN;/" -i $config_file

config_file=/var/www/btranslator/sites/default/settings.php
sed -e "/^\\\$base_url/c \$base_url = \"https://$FQDN\";" -i $config_file

