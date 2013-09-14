#!/bin/bash
### save the schema of the module btranslator_data

### go to the script directory
cd $(dirname $0)

### list of all the tables
all_tables="
    btr_diffs
    btr_snapshots
    btr_files
    btr_projects
    btr_templates
    btr_locations
    btr_strings
    btr_translations
    btr_translations_trash
    btr_votes
    btr_votes_trash
    btr_users
"

### mysqldump default options
dbname=${BTRANSLATOR_DATA:-btranslator_data}
mysqldump="mysqldump --defaults-file=/etc/mysql/debian.cnf --databases $dbname"

### dump only the schema of the database
$mysqldump --no-data --compact --add-drop-table \
    --tables $all_tables > btr_schema.sql

### fix a little bit the file
sed -e '/^SET /d' -i btr_schema.sql

echo "
Schema saved to:
  $(pwd)/btr_schema.sql
"