#!/bin/bash
### set passwords for the mysql users
### btranslator and btranslator_data

cwd=$(dirname $0)
. $cwd/set_mysql_passwd.sh

$cwd/mysqld.sh start

echo "
===> MySQL Password of Drupal Database

Please enter new password for the MySQL 'btranslator' account.
"
random_passwd=$(mcookie | head -c 16)
stty -echo
read -p "Enter password [$random_passwd]: " passwd
stty echo
echo
drupal_passwd=${passwd:-$random_passwd}

echo "
===> MySQL Password of the Translations Database

Please enter new password for the MySQL 'btranslator_data' account.
"
random_passwd=$(mcookie | head -c 16)
stty -echo
read -p "Enter password [$random_passwd]: " passwd
stty echo
echo
data_passwd=${passwd:-$random_passwd}

### set passwords
set_mysql_passwd btranslator $drupal_passwd
set_mysql_passwd btranslator_data $data_passwd

### modify the configuration file of Drupal (settings.php)
for file in $(ls /var/www/btranslator*/sites/default/settings.php)
do
    sed -i $file \
	-e "/^\\\$databases = array/,+10  s/'password' => .*/'password' => '$drupal_passwd',/" \
	-e "/^\\\$databases\\['btr_db/,+5  s/'password' => .*/'password' => '$data_passwd',/"
done

### modify also the connection settings on btranslator_data
sed -i /var/www/btranslator_data/db/settings.php \
    -e "/^\\\$dbpass/ s/= .*/= '$data_passwd';/"
