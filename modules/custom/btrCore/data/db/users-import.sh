#!/bin/bash

function usage {
    echo -e "
 * Usage: $0 @drush_alias \$(pwd)/file.sql.gz [db_key]
"
    exit 1
}

### get the arguments
if [ $# -ne 2 ]; then usage; fi
alias=$1
file_gz=$2
db_key=${3:-default}

### import data to the DB
gunzip $file_gz
file_sql=${file_gz%.gz}
drush $alias sql-query --database=$db_key --file=$file_sql
