#!/bin/bash
### Export user table of btr_data.

### get the dump file name
date=$(date +%Y%m%d)
dump_file=$(pwd)/users-data-$date.sql

### specify the site to be backed-up by setting its alias
alias=${1:-@btr}
drush="drush $alias"

### dump all the users of 'btr_data'
$drush sql-dump --database=btr_db --tables-list=btr_users --result-file=$dump_file --gzip
