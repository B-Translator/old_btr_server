#!/bin/bash
### set passwords for the mysql users
### btranslator and btranslator_data

cwd=$(dirname $0)
. $cwd/set_mysql_passwd.sh

service mysql start

echo "
===> MySQL Password of Drupal Database

Please enter new password for the MySQL 'btranslator' account.
"
stty -echo
read -p "Enter password: " drupal_passwd
stty echo
echo

echo "
===> MySQL Password of the Translations Database

Please enter new password for the MySQL 'btranslator_data' account.
"
stty -echo
read -p "Enter password: " data_passwd
stty echo
echo

### set passwords
set_mysql_passwd btranslator $drupal_passwd
set_mysql_passwd btranslator_data $data_passwd

### modify the configuration file of Drupal (settings.php)
sed -i /var/www/btranslator/sites/default/settings.php \
    -e "/^\\\$databases = array/,+10  s/'password' => .*/'password' => '$drupal_passwd',/" \
    -e "/^\\\$databases\\['l10n_feedback_db/,+5  s/'password' => .*/'password' => '$data_passwd',/"

### modify also the connection settings on btranslator_data
sed -i /var/www/btranslator_data/db/settings.php \
    -e "/^\\\$dbpass/ s/= .*/= '$data_passwd';/"
