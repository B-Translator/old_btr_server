#!/bin/bash
### Create a local clone of the main drupal
### application (/var/www/btr).

if [ $# -ne 2 ]
then
    echo " * Usage: $0 src dst

      Makes a clone from /var/www/<src> to /var/www/<dst>
      The database <src> will also be cloned to <dst>.
      <dst> can be something like 'btr_dev', 'btr_test', 'btr_01', etc.

      Note: Using something like 'btr-dev' is not suitable
      for the name of the database. 

      Caution: The root directory and the DB of the destination
      will be erased, if they exist.
"
    exit 1
fi
src=$1
dst=$2
src_dir=/var/www/$src
dst_dir=/var/www/$dst

### copy the root directory
rm -rf $dst_dir
cp -a $src_dir $dst_dir

### modify settings.php
domain=$(cat /etc/hostname)
hostname=${dst#*_}.$domain
sed -i $dst_dir/sites/default/settings.php \
    -e "/^\\\$databases = array/,+10  s/'database' => .*/'database' => '$dst',/" \
    -e "/^\\\$base_url/c \$base_url = \"https://$hostname\";" \
    -e "/^\\\$conf\['memcache_key_prefix'\]/c \$conf['memcache_key_prefix'] = '$dst';"

### add to /etc/hosts
sed -i /etc/hosts -e "/^127.0.0.1  $hostname/d"
echo "127.0.0.1  $hostname" >> /etc/hosts

### create a drush alias
sed -i /etc/drush/local.aliases.drushrc.php \
    -e "/^\\\$aliases\['$dst'\] = /,+5 d"
cat <<EOF >> /etc/drush/local.aliases.drushrc.php
\$aliases['$dst'] = array (
  'parent' => '@btr',
  'root' => '$dst_dir',
  'uri' => 'http://$hostname',
);

EOF

### create a new database
mysql --defaults-file=/etc/mysql/debian.cnf -e "
    DROP DATABASE IF EXISTS $dst;
    CREATE DATABASE $dst;
    GRANT ALL ON $dst.* TO btr@localhost;
"

### copy the database
drush --yes sql-sync @$src @$dst

### clear the cache
drush @$dst cc all

### copy and modify the configuration of nginx
rm -f /etc/nginx/sites-{available,enabled}/$dst
cp /etc/nginx/sites-available/{$src,$dst}
sed -i /etc/nginx/sites-available/$dst \
    -e "s/443 default ssl/443 ssl/" \
    -e "s/server_name .*;/server_name $hostname;/" \
    -e "s/$src/$dst/g"
ln -s /etc/nginx/sites-{available,enabled}/$dst

### copy and modify the configuration of apache2
rm -f /etc/apache2/sites-{available,enabled}/$dst{,-ssl}
cp /etc/apache2/sites-available/{$src,$dst}
cp /etc/apache2/sites-available/{$src-ssl,$dst-ssl}
sed -i /etc/apache2/sites-available/$dst \
    -e "s/ServerName .*/ServerName $hostname/" \
    -e "s/$src/$dst/g"
sed -i /etc/apache2/sites-available/$dst-ssl \
    -e "s/ServerName .*/ServerName $hostname/" \
    -e "s/$src/$dst/g"
a2ensite $dst $dst-ssl

### fix permissions
chown www-data: -R $dst_dir/sites/default/files/*
chown root: $dst_dir/sites/default/files/.htaccess

### restart services
#for SRV in php5-fpm memcached mysql nginx
for SRV in mysql apache2
do
    service $SRV restart
done
