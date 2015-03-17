#!/bin/bash
### Save the schema of the database btr_data.

### go to the script directory
cd $(dirname $0)

### mysql and mysqldump options
dbname=${BTR_DATA:-btr_data}
mysql="mysql --defaults-file=/etc/mysql/debian.cnf --database=$dbname -B"
mysqldump="mysqldump --defaults-file=/etc/mysql/debian.cnf --databases $dbname"

### get the list of the tables
tables=$($mysql -e "SHOW TABLES" | grep '^btr_' )

### dump only the schema of the database
$mysqldump --no-data --compact --add-drop-table \
    --tables $tables > btr_schema.sql

### fix a little bit the file
sed -e '/^SET /d' -i btr_schema.sql

echo "
Schema saved to:
  $(pwd)/btr_schema.sql
"
