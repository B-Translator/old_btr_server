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

for file in $(ls /etc/nginx/sites-available/*)
do
    sed -i $file -e "s/server_name .*\$/server_name $FQDN;/"
done

for file in $(ls /var/www/btranslator*/sites/default/settings.php)
do
    sed -i $file -e "/^\\\$base_url/c \$base_url = \"https://$FQDN\";"
done

for file in $(ls /etc/apache2/sites-available/*)
do
    sed -i $file -e "s/ServerName .*\$/ServerName $FQDN/"
done
