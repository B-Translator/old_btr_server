#!/bin/bash
### Execute the given sql script.

### check the parameters
if [ $# -ne 2 ]
then
  echo "Usage: $0 db_name file.sql"
  echo
  exit 1
fi

### get the DB name and the sql file
db_name=$1
sql_file=$2

### execute
mysql --defaults-file=/etc/mysql/debian.cnf \
      --database=$db_name < $sql_file

