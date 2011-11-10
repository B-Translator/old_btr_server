#!/bin/bash
### dump the tables of the module l10n_suggestions

### get the DB name
if [ "$1" != "" ]
then
  db_name=$1
else
  echo "Usage: $0 db_name"
  exit 1
fi

### make this 'true' for a full dump of the database
dump='false'


### dump only the schema of the database
mysqldump --user=root --password --no-data --compact \
          --database $db_name --tables \
          l10n_suggestions_phrases l10n_suggestions_locations \
          l10n_suggestions_translations l10n_suggestions_votes \
          l10n_suggestions_users > l10n_suggestions_schema.sql

### fix a little bit the file
sed -e '/^SET /d' -i l10n_suggestions_schema.sql

### make a full dump of the database
if [ "$dump" = 'true' ]
then
  date=$(date +%Y%m%d)
  dump_file=l10n_suggestions_dump_$date.sql

  mysqldump --user=root --password --opt --hex-blob  \
            --database $db_name --tables \
            l10n_suggestions_phrases l10n_suggestions_locations \
            l10n_suggestions_translations l10n_suggestions_votes \
            l10n_suggestions_users > $dump_file

  gzip $dump_file
fi

