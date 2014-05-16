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

if [ -z "${bcl_domain+xxx}" -o "$bcl_domain" = '' ]
then
    bcl_domain='example.org'
    read -p "Enter the domain name for btr_client [$bcl_domain]: " input
    bcl_domain=${input:-$bcl_domain}
fi

if [ -z "${btr_domain+xxx}" -o "$btr_domain" = '' ]
then
    btr_domain='btr.example.org'
    read -p "Enter the domain name for btr_server [$btr_domain]: " input
    btr_domain=${input:-$btr_domain}
fi

echo $bcl_domain > /etc/hostname
sed -i /etc/hosts \
    -e "/ localhost/c 127.0.0.1 $bcl_domain $btr_domain localhost"

### change config files for the client
for file in $(ls /etc/nginx/sites-available/bcl*)
do
    sed -i $file -e "s/server_name .*\$/server_name $bcl_domain;/"
done
for file in $(ls /etc/apache2/sites-available/bcl*)
do
    sed -i $file -e "s/ServerName .*\$/ServerName $bcl_domain/"
done
for file in $(ls /var/www/bcl*/sites/default/settings.php)
do
    sed -i $file -e "/^\\\$base_url/c \$base_url = \"https://$bcl_domain\";"
done

### change config files for the server
for file in $(ls /etc/nginx/sites-available/btr*)
do
    sed -i $file -e "s/server_name .*\$/server_name $btr_domain;/"
done
for file in $(ls /etc/apache2/sites-available/btr*)
do
    sed -i $file -e "s/ServerName .*\$/ServerName $btr_domain/"
done
for file in $(ls /var/www/btr*/sites/default/settings.php)
do
    sed -i $file -e "/^\\\$base_url/c \$base_url = \"https://$btr_domain\";"
done
