#!/bin/bash
### Backup all the users, suggestions and votes.

### create the backup directory
date=$(date +%Y%m%d)
backup="btr-backup-$date"
backup_dir="/tmp/$backup"
mkdir -p $backup_dir/

### set mysqldump options
sql_connect=$(drush @btr sql-connect --database=btr_db | sed -e 's/^mysql //' -e 's/--database=/--databases /')
mysqldump="mysqldump $sql_connect --skip-add-drop-table --replace"

### backup translations
$mysqldump --tables btr_translations --where="umail != ''" \
    > $backup_dir/btr_data.sql

### backup other tables of btr_data
table_list="
    btr_votes
    btr_translations_trash
    btr_votes_trash
    btr_users
    btr_user_project_roles
    btr_languages
"
$mysqldump --tables $table_list >> $backup_dir/btr_data.sql

### fix 'CREATE TABLE' on the sql file
sed -i $backup_dir/btr_data.sql \
    -e 's/CREATE TABLE/CREATE TABLE IF NOT EXISTS/g'

### backup bcl tables
mysqldump=$(drush @bcl sql-connect | sed -e 's/^mysql/mysqldump/' -e 's/--database=/--databases /')
table_list="users users_roles"
$mysqldump --tables $table_list > $backup_dir/bcl.sql

### backup btr tables
mysqldump=$(drush @btr sql-connect | sed -e 's/^mysql/mysqldump/' -e 's/--database=/--databases /')
table_list="
    translation_projects
    btr_languages
    users
    users_roles
    field_data_field_auxiliary_languages
    field_data_field_projects
    field_data_field_translation_lng
    field_revision_field_auxiliary_languages
    field_revision_field_projects
    field_revision_field_translation_lng
    hybridauth_identity
    hybridauth_session
"
$mysqldump --tables $table_list > $backup_dir/btr.sql

### create an archive
cd /tmp
rm -f $backup.tgz
tar cfz $backup.tgz $backup/
rm -rf $backup
