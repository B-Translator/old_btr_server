#!/bin/bash -x

### make sure that we have the right git branch on the make file
makefile="$code_dir/build-btrserver.make"
sed -i $makefile \
    -e "/btr_server..download..branch/ c projects[btr_server][download][branch] = $btr_git_branch"

### retrieve all the projects/modules and build the application directory
rm -rf $drupal_dir
drush make --prepare-install --force-complete \
           --contrib-destination=profiles/btr_server \
           $makefile $drupal_dir

### fix some things on the application directory
cd $drupal_dir/profiles/btr_server/
cp -a libraries/bootstrap themes/contrib/bootstrap/
cd $drupal_dir/profiles/btr_server/libraries/hybridauth/
cp additional-providers/hybridauth-github/Providers/GitHub.php \
   hybridauth/Hybrid/Providers/

### replace the profile btr_server with a version
### that is a git clone, so that any updates
### can be retrieved easily (without having to
### reinstall the whole application).
cd $drupal_dir/profiles/
mv btr_server btr_server-bak
cp -a $code_dir .
### copy contrib libraries and modules
cp -a btr_server-bak/libraries/ btr_server/
cp -a btr_server-bak/modules/contrib/ btr_server/modules/
cp -a btr_server-bak/themes/contrib/ btr_server/themes/
### copy db connection file
cp {btr_server-bak,btr_server}/modules/custom/btrCore/data/db/settings.php
### cleanup
rm -rf btr_server-bak/

### get a clone of btrclient from github
if [ "$development" = 'true' ]
then
    cd $drupal_dir/profiles/btr_server/modules/contrib/btrclient
    git clone https://github.com/B-Translator/btrclient.git
    cp -a btrclient/.git .
    rm -rf btrclient/
fi

### create the directory of PO files
mkdir -p /var/www/PO_files
chown www-data: /var/www/PO_files

### create the downloads and exports dirs
mkdir -p /var/www/downloads/
chown www-data: /var/www/downloads/
mkdir -p /var/www/exports/
chown www-data: /var/www/exports/
mkdir -p /var/www/uploads/
chown www-data: /var/www/uploads/

### start mysqld manually, if it is not running
if test -z "$(ps ax | grep [m]ysqld)"
then
    nohup mysqld --user mysql >/dev/null 2>/dev/null &
    sleep 5  # give time mysqld to start
fi

### settings for the database and the drupal site
db_name=btr
db_user=btr
db_pass=btr
site_name="B-Translator"
site_mail="admin@example.com"
account_name=admin
account_pass=admin
account_mail="admin@example.com"

### create the database and user
mysql='mysql --defaults-file=/etc/mysql/debian.cnf'
$mysql -e "
    DROP DATABASE IF EXISTS $db_name;
    CREATE DATABASE $db_name;
    GRANT ALL ON $db_name.* TO $db_user@localhost IDENTIFIED BY '$db_pass';
"

### site installation
sed -e '/memory_limit/ c memory_limit = -1' -i /etc/php5/cli/php.ini
cd $drupal_dir
drush site-install --verbose --yes btr_server \
      --db-url="mysql://$db_user:$db_pass@localhost/$db_name" \
      --site-name="$site_name" --site-mail="$site_mail" \
      --account-name="$account_name" --account-pass="$account_pass" --account-mail="$account_mail"

### set propper directory permissions
mkdir -p sites/default/files/
chown -R www-data: sites/default/files/
mkdir -p cache/
chown -R www-data: cache/
