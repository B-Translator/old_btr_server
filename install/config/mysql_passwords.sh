#!/bin/bash
### regenerate mysql and phpmyadmin secrets

cwd=$(dirname $0)
. $cwd/set_mysql_passwd.sh

service mysql start

### to remove the current password do: 
### mysqladmin -u root -pcurrent_password password

### regenerate the password of debian-sys-maint
PASSWD=$(mcookie | head -c 16)
DEBIAN_CNF=/etc/mysql/debian.cnf
sed -e "/^password/c password = $PASSWD" -i $DEBIAN_CNF
query="SET PASSWORD FOR 'debian-sys-maint'@'localhost' = PASSWORD('$PASSWD');"
echo $query | mysql

# regenerate phpmyadmin pmadb password
PASSWD=$(mcookie)
CONF=/etc/phpmyadmin/config-db.php
sed -i "/^\$dbpass/ c \$dbpass='$PASSWD';" $CONF
set_mysql_passwd phpmyadmin $PASSWD

### set a new password for the root user of mysql
echo "
===> Set a new password for the 'root' user of MySQL
"
stty -echo
read -p "Enter root password: " passwd
stty echo
echo
set_mysql_passwd root $passwd

