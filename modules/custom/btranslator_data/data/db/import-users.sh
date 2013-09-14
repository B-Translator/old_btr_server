#!/bin/bash
### Import the users which are exported with 'export-users.sh'

function usage {
    echo -e "
 * Usage: $0 file.sql.gz
"
    exit 1
}

### get the argument
if [ "$1" = '' ]; then usage; fi
file_gz=$1

### mysqldump options
mysql="mysql --defaults-file=/etc/mysql/debian.cnf"

### create a temporary database
$mysql -e "
    DROP DATABASE IF EXISTS user_import;
    CREATE DATABASE user_import;
"

### import data to the temp DB
gunzip $file_gz
file_sql=${file_gz%.gz}
$mysql -D user_import < $file_sql

### get the name of database
BTR=${BTRANSLATOR:-btranslator}
DATA=${BTRANSLATOR_DATA:-btranslator_data}

### copy all drupal tables
table_list="
    users
    users_roles
    field_data_field_auxiliary_languages
    field_data_field_data_sequential
    field_data_field_feedback_channels
    field_data_field_order_of_strings
    field_data_field_preferred_projects
    field_data_field_translations_per_day
    field_revision_field_auxiliary_languages
    field_revision_field_data_sequential
    field_revision_field_feedback_channels
    field_revision_field_order_of_strings
    field_revision_field_preferred_projects
    field_revision_field_translations_per_day
"
for table in $table_list
do
    $mysql -e "
        TRUNCATE TABLE $BTR.$table;
        INSERT INTO $BTR.$table SELECT * FROM user_import.$table;
    "
done

### copy btranslator_data table
$mysql -e "
    TRUNCATE TABLE $DATA.btr_users;
    INSERT INTO $DATA.btr_users
        SELECT * FROM user_import.btr_users;
"

### delete the temp DB
$mysql -e "DROP DATABASE user_import;"