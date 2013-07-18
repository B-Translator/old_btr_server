#!/bin/bash
### save the schema of the module l10n_feedback

### go to the script directory
cd $(dirname $0)

### list of all the tables
all_tables="
    l10n_feedback_diffs
    l10n_feedback_snapshots
    l10n_feedback_files
    l10n_feedback_projects
    l10n_feedback_templates
    l10n_feedback_locations
    l10n_feedback_strings
    l10n_feedback_translations
    l10n_feedback_translations_trash
    l10n_feedback_votes
    l10n_feedback_votes_trash
    l10n_feedback_users
"

### mysqldump default options
dbname=${BTRANSLATOR_DATA:-btranslator_data}
mysqldump="mysqldump --defaults-file=/etc/mysql/debian.cnf --databases $dbname"

### dump only the schema of the database
$mysqldump --no-data --compact --add-drop-table \
    --tables $all_tables > l10n_feedback_schema.sql

### fix a little bit the file
sed -e '/^SET /d' -i l10n_feedback_schema.sql

echo "
Schema saved to:
  $(pwd)/l10n_feedback_schema.sql
"