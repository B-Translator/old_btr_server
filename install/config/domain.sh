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
sed -i /etc/hosts \
    -e "/^127.0.1.1/c 127.0.1.1 $FQDN btranslator"

sed -i /etc/nginx/sites-available/default \
    -e "s/server_name .*\$/server_name $FQDN;/"

sed -i /var/www/btranslator/sites/default/settings.php \
    -e "/^\\\$base_url/c \$base_url = \"https://$FQDN\";"

sed -i /etc/apache2/sites-available/default \
    -e "s/ServerName .*\$/ServerName $FQDN/"

sed -i /etc/apache2/sites-available/default-ssl \
    -e "s/ServerName .*\$/ServerName $FQDN/"
