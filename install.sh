#!/bin/bash

### get the directory name
output_dir=${1:-btranslator}

### get all the required files and modules
drush make --working-copy "https://raw.github.com/dashohoxha/B-Translator/master/distro.make" $output_dir
### for developing make files, comment the line above and use the following one
#drush make --working-copy /var/www/B-Translator/distro.make $output_dir

### install the profile btranslator
dbname=test1
dbuser=test1
dbpass=test1
echo "===> Installing the profile btranslator."
cd $output_dir
drush site-install btranslator  \
      --site-name='B-Translator'  \
      --db-url="mysql://$dbuser:$dbpass1@localhost/$dbname"

### set propper permissions
chown -R www-data: sites/default/files
chown -R www-data: cache/

### install some test data
echo "===> Installing some test data."
profiles/btranslator/modules/l10n_feedback/data/install.sh