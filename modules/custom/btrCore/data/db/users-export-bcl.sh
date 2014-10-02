#!/bin/bash
### Export table of users and all related tables.

### get the dump file name
date=$(date +%Y%m%d)
dump_file=$(pwd)/users-bcl-$date.sql

### specify the site to be backed-up by setting its alias
alias=${1:-@bcl}
drush="drush $alias"

### dump all the users
$drush sql-dump --database=default --tables-list=users,users_roles --result-file=$dump_file --gzip

