#!/bin/bash
### dump the tables of the module l10n_feedback

function usage {
    echo -e " Usage: $0 (schema|data|user|db) \n"
    exit 1
}

### get the arguments
if [ "$1" = '' ]; then usage; fi
dump_mode=$1

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
mysqldump="mysqldump --defaults-file=/etc/mysql/debian.cnf --database=$dbname"

### make the required dump
case "$dump_mode" in

    schema )
        ### dump only the schema of the database
	$mysqldump --no-data --compact --add-drop-table \
            --tables $all_tables > l10n_feedback_schema.sql

        ### fix a little bit the file
	sed -e '/^SET /d' -i l10n_feedback_schema.sql
	;;

    data )
	date=$(date +%Y%m%d)
	dump_file=l10n_feedback_dump_$date.sql

        ### make a full dump of the database
	$mysqldump --opt --tables $all_tables > $dump_file

	gzip $dump_file
	;;

    user )
	date=$(date +%Y%m%d)
	dump_file=l10n_feedback_user_$date.sql

	$mysqldump --no-create-info --tables l10n_feedback_translations \
            --where="uid>1" > $dump_file
	$mysqldump --opt --tables l10n_feedback_users >> $dump_file
	$mysqldump --opt --tables l10n_feedback_votes >> $dump_file

	gzip $dump_file
	;;

    db )
	date=$(date +%Y%m%d)
	dump_file=$dbname-$date.sql
	$mysqldump --opt > $dump_file
	gzip $dump_file
	;;

    * )
        usage
	;;
esac
