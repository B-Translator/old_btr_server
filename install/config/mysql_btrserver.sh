#!/bin/bash
### set passwords for the mysql users btr and btr_data

cwd=$(dirname $0)
. $cwd/set_mysql_passwd.sh

$cwd/mysqld.sh start

### get a new password for the mysql user 'btr'
if [ "$mysql_passwd_btr" = 'random' ]
then
    mysql_passwd_btr=$(mcookie | head -c 16)
elif [ -z ${mysql_passwd_btr+xxx} -o "$mysql_passwd_btr" = '' ]
then
    echo
    echo "===> Please enter new password for the MySQL 'btr' account."
    echo
    mysql_passwd_btr=$(mcookie | head -c 16)
    stty -echo
    read -p "Enter password [$mysql_passwd_btr]: " passwd
    stty echo
    echo
    mysql_passwd_btr=${passwd:-$mysql_passwd_btr}
fi

### get a new password for the mysql user 'btr_data'
if [ "$mysql_passwd_btr_data" = 'random' ]
then
    mysql_passwd_btr_data=$(mcookie | head -c 16)
elif [ -z ${mysql_passwd_btr_data+xxx} -o "$mysql_passwd_btr_data" = '' ]
then
    echo
    echo "===> Please enter new password for the MySQL 'btr_data' account."
    echo
    mysql_passwd_btr_data=$(mcookie | head -c 16)
    stty -echo
    read -p "Enter password [$mysql_passwd_btr_data]: " passwd
    stty echo
    echo
    mysql_passwd_btr_data=${passwd:-$mysql_passwd_btr_data}
fi

### set passwords
set_mysql_passwd btr $mysql_passwd_btr
set_mysql_passwd btr_data $mysql_passwd_btr_data

### modify the configuration file of Drupal (settings.php)
for file in $(ls /var/www/btr*/sites/default/settings.php)
do
    sed -i $file \
	-e "/^\\\$databases = array/,+10  s/'password' => .*/'password' => '$mysql_passwd_btr',/" \
	-e "/^\\\$databases\\['btr_db/,+5  s/'password' => .*/'password' => '$mysql_passwd_btr_data',/"
done

### modify also the connection settings on /var/www/data
sed -i /var/www/data/db/settings.php \
    -e "/^\\\$dbpass/ s/= .*/= '$mysql_passwd_btr_data';/"
