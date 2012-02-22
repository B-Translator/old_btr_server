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

### make this 'full' for a full dump of the database
### or 'user' for dumping only user suggestions and votes
dump='false'
#dump='full'
#dump='user'

### dump only the schema of the database
mysqldump --user=root --password --no-data --compact --add-drop-table \
          --database $db_name \
          --tables l10n_suggestions_snapshots \
          l10n_suggestions_templates l10n_suggestions_diffs \
          l10n_suggestions_projects l10n_suggestions_files \
          l10n_suggestions_strings l10n_suggestions_locations \
          l10n_suggestions_translations l10n_suggestions_votes \
          l10n_suggestions_users > l10n_suggestions_schema.sql

### fix a little bit the file
sed -e '/^SET /d' -i l10n_suggestions_schema.sql

### make a full dump of the database
if [ "$dump" = 'full' ]
then
  date=$(date +%Y%m%d)
  dump_file=l10n_suggestions_dump_$date.sql

  mysqldump --user=root --password --opt \
            --database $db_name \
            --tables l10n_suggestions_snapshots \
            l10n_suggestions_templates l10n_suggestions_diffs \
            l10n_suggestions_projects l10n_suggestions_files \
            l10n_suggestions_strings l10n_suggestions_locations \
            l10n_suggestions_translations l10n_suggestions_votes \
            l10n_suggestions_users > $dump_file

  gzip $dump_file
fi

### dump only user suggestions and votes
if [ "$dump" = 'user' ]
then
  date=$(date +%Y%m%d)
  dump_file=l10n_suggestions_user_$date.sql

  mysqldump --user=root --password --opt --database $db_name \
            --tables l10n_suggestions_translations \
            --where="uid>1" > $dump_file
  mysqldump --user=root --password --opt --database $db_name \
            --tables l10n_suggestions_users >> $dump_file
  mysqldump --user=root --password --opt --database $db_name \
            --tables l10n_suggestions_votes >> $dump_file

  gzip $dump_file
fi

