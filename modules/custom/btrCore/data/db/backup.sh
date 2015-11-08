#!/bin/bash
### Backup all the users, suggestions and votes.

### create the backup directory
date=$(date +%Y%m%d)
backup="btr-backup-$date"
backup_dir="/tmp/$backup"
mkdir -p $backup_dir/

### mysqldump options
mysqldump="mysqldump --defaults-file=/etc/mysql/debian.cnf --skip-add-drop-table --replace --databases btr_data"

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
$mysqldump --tables $table_list \
    >> $backup_dir/btr_data.sql

### fix 'CREATE TABLE' on the sql file
sed -i $backup_dir/btr_data.sql \
    -e 's/CREATE TABLE/CREATE TABLE IF NOT EXISTS/g'

### backup bcl tables
drush @bcl sql-dump --database=default --tables-list=users,users_roles \
    --result-file=$backup_dir/bcl.sql

### backup btr tables
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
table_list=$(echo $table_list | tr ' ' ,)
drush @btr sql-dump --database=default --tables-list=$table_list \
    --result-file=$backup_dir/btr.sql

### create an archive
cd /tmp
tar cfz $backup.tgz $backup/
rm -rf $backup
