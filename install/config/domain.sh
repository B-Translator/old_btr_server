#!/bin/bash

echo "
===> Set the domain names (fqdn)

These are the domains that you have (or plan to get)
for the btr_server and for the btr_client.

It will modify the files:
 1) /etc/hostname
 2) /etc/hosts
 3) /etc/nginx/sites-available/bcl*
 4) /etc/nginx/sites-available/btr*
 5) /etc/apache2/sites-available/bcl*
 6) /etc/apache2/sites-available/btr*
 7) /var/www/bcl*/sites/default/settings.php
 8) /var/www/btr*/sites/default/settings.php
"

FQDN1='example.org'
read -p "Enter the domain name for btr_client [$FQDN1]: " input
FQDN1=${input:-$FQDN1}

FQDN2='btr.example.org'
read -p "Enter the domain name for btr_server [$FQDN2]: " input
FQDN2=${input:-$FQDN2}

echo $FQDN1 > /etc/hostname
sed -i /etc/hosts \
    -e "/localhost/c 127.0.0.1 $FQDN1 $FQDN2 localhost"

### change config files for the client
for file in $(ls /etc/nginx/sites-available/bcl*)
do
    sed -i $file -e "s/server_name .*\$/server_name $FQDN1;/"
done
for file in $(ls /etc/apache2/sites-available/bcl*)
do
    sed -i $file -e "s/ServerName .*\$/ServerName $FQDN1/"
done
for file in $(ls /var/www/bcl*/sites/default/settings.php)
do
    sed -i $file -e "/^\\\$base_url/c \$base_url = \"https://$FQDN1\";"
done

### change config files for the server
for file in $(ls /etc/nginx/sites-available/btr*)
do
    sed -i $file -e "s/server_name .*\$/server_name $FQDN2;/"
done
for file in $(ls /etc/apache2/sites-available/btr*)
do
    sed -i $file -e "s/ServerName .*\$/ServerName $FQDN2/"
done
for file in $(ls /var/www/btr*/sites/default/settings.php)
do
    sed -i $file -e "/^\\\$base_url/c \$base_url = \"https://$FQDN2\";"
done
