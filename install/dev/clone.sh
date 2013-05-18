#!/bin/bash
### Create a local clone of the main drupal
### application (/var/www/btranslator).

if [ $# -ne 1 ]
then
    echo " * Usage: $0 variant

      Creates a local clone of the main drupal application.
      <variant> can be something like 'dev', 'test', '01', etc.
      It will create a new application with root
      /var/www/btranslator_<variant> and with DB named
      btranslator_<variant>

      Caution: The root directory and the DB will be erased,
      if they exist.
"
    exit 1
fi
var=$1
root_dir=/var/www/btranslator_$var
db_name=btranslator_$var

### copy the root directory
rm -rf $root_dir
cp -a /var/www/btranslator $root_dir

### modify settings.php
domain=$(cat /etc/hostname)
sed -i $root_dir/sites/default/settings.php \
    -e "/^\\\$databases = array/,+10  s/'database' => .*/'database' => '$db_name',/" \
    -e "/^\\\$base_url/c \$base_url = \"https://$var.$domain\";" \
    -e "/^\\\$conf\['memcache_key_prefix'\]/c \$conf['memcache_key_prefix'] = 'btranslator_$var';"

### create a drush alias
sed -i /etc/drush/local.aliases.drushrc.php \
    -e "/^\\\$aliases\['$var'\] = /,+5 d"
cat <<EOF >> /etc/drush/local.aliases.drushrc.php
\$aliases['$var'] = array (
  'parent' => '@main',
  'root' => '/var/www/btranslator_$var',
  'uri' => 'http://$var.l10n.org.xx',
);

EOF

### create a new database
mysql --defaults-file=/etc/mysql/debian.cnf -e "
    DROP DATABASE IF EXISTS $db_name;
    CREATE DATABASE $db_name;
    GRANT ALL ON $db_name.* TO btranslator@localhost;
"

### copy the database
drush sql-sync @self @$var

### clear the cache
drush @$var cc all

### copy and modify the configuration of nginx
rm -f /etc/nginx/sites-{available,enabled}/$var
cp /etc/nginx/sites-available/{default,$var}
sed -i /etc/nginx/sites-available/$var \
    -e "s/443 default ssl/443 ssl/" \
    -e "s/server_name \(.*\);/server_name $var.\\1;/" \
    -e "s/btranslator/btranslator_$var/g"
ln -s /etc/nginx/sites-{available,enabled}/$var

### restart services
for SRV in php5-fpm memcached mysql nginx
do
    service $SRV restart
done
