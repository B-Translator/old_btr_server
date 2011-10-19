#!/bin/bash
### restore the tables of the module l10n_suggestions

### check the parameters
if [ $# -ne 2 ]
then
  echo "Usage: $0 db_name dump_file.sql"
  echo
  exit 1
fi

### get the DB name and the dump file
db_name=$1
sql_file=$2

### restore the tables
mysql -p -D $db_name < $sql_file

