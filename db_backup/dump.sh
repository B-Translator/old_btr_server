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

### make a full dump of the database
mysqldump --user=root --extended-insert=false --comments=false \
          --single-transaction --password --database $db_name \
          --tables \
          l10n_suggestions_phrases l10n_suggestions_words \
          l10n_suggestions_wordphrases l10n_suggestions_locations \
          l10n_suggestions_translations l10n_suggestions_votes \
          l10n_suggestions_users > l10n_suggestions_dump.sql

### dump only the structure (tables) of the database
mysqldump --user=root --no-data --compact --password --database $db_name \
          --tables \
          l10n_suggestions_phrases l10n_suggestions_words \
          l10n_suggestions_wordphrases l10n_suggestions_locations \
          l10n_suggestions_translations l10n_suggestions_votes \
          l10n_suggestions_users > l10n_suggestions_structure.sql

### fix a little bit the dump files
sed -e '/^SET /d' -i l10n_suggestions_dump.sql
sed -e '/^SET /d' -i l10n_suggestions_structure.sql

### zip the backup
gzip l10n_suggestions_dump.sql

