#!/bin/bash

mysql="mysql --defaults-file=/etc/mysql/debian.cnf -B"
db=btr_data
db1=btranslator_data
tables=$($mysql -D $db -e "SHOW TABLES" | grep '^btr_' )
for table in $tables
do
    table1=${table//btr_/l10n_feedback_}
    echo "$table1 --> $table"
    $mysql -e "
        TRUNCATE TABLE $db.$table;
        INSERT INTO $db.$table SELECT * FROM $db1.$table1;
    "
done

#        CREATE TABLE $db.$table LIKE $db1.$table1;
