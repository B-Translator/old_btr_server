#!/bin/bash -x

### retrieve all the projects/modules and build the application directory
makefile="https://raw.github.com/dashohoxha/B-Translator/master/build-btranslator.make"
appdir="/var/www/btranslator"
rm -rf $appdir
drush make --prepare-install --force-complete \
           --contrib-destination=profiles/btranslator \
           $makefile $appdir

### settings for the database and the drupal site
db_name=btranslator
db_user=btranslator
db_pass=btranslator
site_name="B-Translator"
site_mail="admin@example.com"
account_name=admin
account_pass=admin
account_mail="admin@example.com"

### create the database and user
mysql_commands="
    DROP DATABASE IF EXISTS $db_name;
    CREATE DATABASE $db_name;
    GRANT ALL ON $db_name.* TO $db_user@localhost IDENTIFIED BY '$db_pass';
"
echo "$mysql_commands" | mysql -u root

### start site installation
sed -e '/memory_limit/ c memory_limit = -1' -i /etc/php5/cli/php.ini
cd $appdir
drush site-install --verbose --yes btranslator \
      --db-url="mysql://$db_user:$db_pass@localhost/$db_name" \
      --site-name="$site_name" --site-mail="$site_mail" \
      --account-name="$account_name" --account-pass="$account_pass" --account-mail="$account_mail"

### update to the latest version of core and modules
drush --yes pm-update

### install also multi-language support
drush --yes pm-enable l10n_client l10n_update

### install features modules
drush --yes pm-enable btranslator_misc_config
drush --yes pm-enable btranslator_content
drush --yes pm-enable btranslator_block_settings
drush --yes pm-enable btranslator_variables
#drush --yes pm-enable btranslator_permissions

### set propper directory permissions
mkdir -p sites/default/files/
chown -R www-data: sites/default/files/
mkdir -p sites/all/translations
chown -R www-data: sites/all/translations
mkdir -p cache/
chown -R www-data: cache/

### create the downloads and exports dirs
mkdir -p /var/www/downloads/
chown www-data /var/www/downloads/
mkdir -p /var/www/exports/
chown www-data /var/www/exports/

### move the directory of the PO files to /var/www/ and put a link to it
PO_files=/var/www/PO_files
l10n_feedback=/var/www/btranslator/profiles/btranslator/modules/l10n_feedback
rm -rf $PO_files
mv $l10n_feedback/data/PO_files $PO_files
rm -rf $l10n_feedback/data/get/PO_files
rm -rf $l10n_feedback/data/import/PO_files
ln -s $PO_files $l10n_feedback/data/get/PO_files
ln -s $PO_files $l10n_feedback/data/import/PO_files
