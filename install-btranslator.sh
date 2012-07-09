#!/bin/bash

### get the directory name
output_dir=${1:-btranslator}

if [ -d $output_dir ]
then
  echo "Directory $output_dir already exists..."
  exit 1
fi

### get all the required files and modules
drush make --working-copy "https://raw.github.com/dashohoxha/B-Translator/master/distro.make" $output_dir
### for developing make files, comment the line above and use the following one
#drush make --working-copy /var/www/B-Translator/distro.make $output_dir

### install the profile btranslator
dbname=test1
dbuser=test1
dbpass=test1
echo
echo "===> Installing the profile btranslator."
echo
cd $output_dir
drush site-install btranslator  \
      --db-url="mysql://$dbuser:$dbpass@localhost/$dbname" \
      --site-name='B-Translator'  # --site-email=admin@example.com \
      # --account-name=admin --account-pass=admin --account-mail=admin@example.com

### set propper permissions
chown -R www-data: sites/default/files
chown -R www-data: cache/

### install some test data
echo
echo "===> Installing some test data (importing some test PO files)."
echo
profiles/btranslator/modules/l10n_feedback/data/install.sh
