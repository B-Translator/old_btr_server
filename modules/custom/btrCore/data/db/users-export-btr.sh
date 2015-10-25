#!/bin/bash
### Export table of users and all related tables.

### get the dump file name
date=$(date +%Y%m%d)
dump_file=$(pwd)/users-btr-$date.sql

### specify the site to be backed-up by setting its alias
alias=${1:-@btr}
drush="drush $alias"

### list of tables related to users
table_list="
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

### dump all the users
$drush sql-dump --database=default --tables-list=$table_list --result-file=$dump_file --gzip

