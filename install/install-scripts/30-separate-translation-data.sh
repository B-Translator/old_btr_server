#!/bin/bash
### Create another database for the translation data
### and copy to it the relevant tables (of module btr_data).

### database and user settings
db_name=btr_data
db_user=btr_data
db_pass=btr_data

### create the database and user
mysql="mysql --defaults-file=/etc/mysql/debian.cnf -B"
$mysql -e "
    DROP DATABASE IF EXISTS $db_name;
    CREATE DATABASE $db_name;
    GRANT ALL ON $db_name.* TO $db_user@localhost IDENTIFIED BY '$db_pass';
"

### copy the tables of btr_data to the new database
tables=$($mysql -D btr -e "SHOW TABLES" | grep 'btr_' )
for table in $tables
do
    echo "Copy: $table"
    $mysql -e "
        CREATE TABLE $db_name.$table LIKE btr.$table;
        INSERT INTO $db_name.$table SELECT * FROM btr.$table;
    "
done

### put a link to the data directory on /var/www/data
rm -f /var/www/data
ln -s /var/www/btr/profiles/btranslator/modules/custom/btr_data/data /var/www/data

### modify also the DB settings on /var/www/data/db/
cat <<EOF > /var/www/data/db/settings.php
<?php
\$dbdriver = 'mysql';
\$dbhost   = 'localhost';
\$dbname   = '$db_name';
\$dbuser   = '$db_user';
\$dbpass   = '$db_pass';
?>
EOF

# modify Drupal settings
drupal_settings=/var/www/btr/sites/default/settings.php
sed -e '/===== APPENDED BY INSTALLATION SCRIPTS =====/,$ d' -i $drupal_settings
cat << EOF >> $drupal_settings
//===== APPENDED BY INSTALLATION SCRIPTS =====

/**
 * Use a separate database for the translation data.
 * This provides more flexibility. For example the
 * drupal site and the translation data can be backuped
 * and restored separately. Or a test drupal site
 * (testing new drupal features) can connect to the
 * same translation database.
 */
\$databases['btr_db']['default'] = array (
    'database' => '$db_name',
    'username' => '$db_user',
    'password' => '$db_pass',
    'host' => 'localhost',
    'port' => '',
    'driver' => 'mysql',
    'prefix' => '',
);

EOF

