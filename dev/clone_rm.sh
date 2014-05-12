#!/bin/bash
### Erase a local clone created by clone.sh

if [ $# -ne 1 ]
then
    echo " * Usage: $0 target

   Deletes the application with root /var/www/<target>
   and with DB named <target>.
"
    exit 1
fi
target=$1

### remove the root directory
rm -rf /var/www/$target

### delete the drush alias
sed -i /etc/drush/local.aliases.drushrc.php \
    -e "/^\\\$aliases\['$target'\] = /,+5 d"

### drop the database
mysql --defaults-file=/etc/mysql/debian.cnf \
      -e "DROP DATABASE IF EXISTS $target;"

### remove the configuration of nginx
rm -f /etc/nginx/sites-{available,enabled}/$target

### remove the configuration of apache2
rm -f /etc/apache2/sites-{available,enabled}/$target{,-ssl}

### remove from /etc/hosts
subdomain=${target#*_}
sed -i /etc/hosts -e "/^127.0.0.1  $subdomain\./d"

### restart services
#for SRV in php5-fpm memcached mysql nginx
for SRV in mysql apache2
do
    service $SRV restart
done
