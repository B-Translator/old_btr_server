#!/bin/bash -x
### Reinstall the Drupal profile 'btr_server' and its features.
### This script touches only the database of Drupal (btr)
### and nothing else. Useful for testing the features.
###
### Usually, when features are un-installed, things are not undone
### properly. To leave out a feature, it should not be installed
### since the beginning. So, it is important to test them.

### get the alias of the site to be reinstalled
if [ "$1" = '' ]
then
    echo "Usage: $0 @alias"
    exit 1
fi
alias=$1

### start mysqld manually, if it is not running
if test -z "$(ps ax | grep [m]ysqld)"
then
    nohup mysqld --user mysql >/dev/null 2>/dev/null &
    sleep 5  # give time mysqld to start
fi

### go to the directory of the site to be reinstalled
drupal_dir=$(drush $alias drupal-directory)
cd $drupal_dir

### settings for the database and the drupal site
db_name=$(drush sql-connect | tr ' ' "\n" | grep -e '--database=' | cut -d= -f2)
db_user=$(drush sql-connect | tr ' ' "\n" | grep -e '--user=' | cut -d= -f2)
db_pass=$(drush sql-connect | tr ' ' "\n" | grep -e '--password=' | cut -d= -f2)
site_name=$(drush vget site_name --format=string)
site_mail=$(drush vget site_mail --format=string)
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

### start site installation
sed -e '/memory_limit/ c memory_limit = -1' -i /etc/php5/cli/php.ini
cd $drupal_dir
drush site-install --verbose --yes btr_server \
      --db-url="mysql://$db_user:$db_pass@localhost/$db_name" \
      --site-name="$site_name" --site-mail="$site_mail" \
      --account-name="$account_name" --account-pass="$account_pass" --account-mail="$account_mail"

### install btrClient
drush --yes pm-enable btrClient
drush --yes pm-enable btrVocabulary
#drush --yes pm-enable bcl_disqus
#drush --yes features-revert bcl_disqus

### install features
drush --yes pm-enable btr_btrServices
drush --yes features-revert btr_btrServices

drush --yes pm-enable btr_btr
drush --yes features-revert btr_btr

drush --yes pm-enable btr_misc
drush --yes features-revert btr_misc

drush --yes pm-enable btr_layout
drush --yes features-revert btr_layout

drush --yes pm-enable btr_hybridauth
drush --yes features-revert btr_hybridauth

#drush --yes pm-enable btr_captcha
#drush --yes features-revert btr_captcha

drush --yes pm-enable btr_permissions
drush --yes features-revert btr_permissions

### add languages
drush --yes pm-enable l10n_update
source /var/www/data/config.sh
for lng in $languages
do
    drush language-add $lng
done
drush --yes l10n-update

### update to the latest version of core and modules
#drush --yes pm-update

### install some test translation projecs
if [ "$development" = 'true' ]
then
    $drupal_dir/profiles/btr_server/modules/custom/btrCore/data/install.sh
fi
