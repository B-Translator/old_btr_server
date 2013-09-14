#!/bin/bash
### Export user tables of btranslator and btranslator_data.

### mysqldump default options
mysqldump="mysqldump --defaults-file=/etc/mysql/debian.cnf"

### get database names
BTR=${BTRANSLATOR:-btranslator}
DATA=${BTRANSLATOR_DATA:-btranslator_data}

### get the dump file name
date=$(date +%Y%m%d)
dump_file=users-$date.sql

### dump all the users of 'btranslator_data'
$mysqldump --databases $DATA --tables btr_users > $dump_file

### dump all the drupal users of 'btranslator'
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
$mysqldump --databases $BTR --tables $table_list >> $dump_file

### compress the export file
gzip $dump_file
