#!/bin/bash
### create the database

### get the directory of the installation scripts
scripts=$(dirname $0)

### get the DB connection settings
. $scripts/config.sh

### confirm/modify the settings
echo "Give db_name, db_user and db_pass."
read -p "db_name [$db_name]: " dbname
dbname=${dbname:-$db_name}
read -p "db_user [$db_user]: " dbuser
dbuser=${dbuser:-$db_user}
read -p "db_pass [$db_pass]: " dbpass
dbpass=${dbpass:-$db_pass}

### save DB settings to the configuration file
db_name=$dbname
db_user=$dbuser
db_pass=$dbpass
. $scripts/save.sh

### create the database and user
mysql_commands="
    DROP DATABASE IF EXISTS $dbname;
    CREATE DATABASE $dbname;
    GRANT ALL ON $dbname.* TO $dbuser@localhost IDENTIFIED BY '$dbpass';
"
echo "$mysql_commands"
echo "Enter the mysql root password below."
echo "$mysql_commands" | mysql -u root -p
