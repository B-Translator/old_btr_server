#!/bin/bash
### dump the tables of the module l10n_feedback

### get the dump mode
if [ "$1" = '' ]
then
    echo -e "Usage: $0 (schema|data|user)\n"
    exit 1
fi
dump_mode=$1

### go to the script directory
cd $(dirname $0)

### get the DB connection parameters
mysql_command="$(drush sql-connect)"
connection=$(echo $mysql_command | sed -e 's/^mysql //' | sed -e 's/--database=/--database /')
#echo $connection;  exit 0;  ## debug

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
    l10n_feedback_votes
    l10n_feedback_users
"

### make the required dump
case "$dump_mode" in

    schema )
        ### dump only the schema of the database
	mysqldump $connection \
            --no-data --compact --add-drop-table \
            --tables $all_tables > l10n_feedback_schema.sql

        ### fix a little bit the file
	sed -e '/^SET /d' -i l10n_feedback_schema.sql
	;;

    data )
	date=$(date +%Y%m%d)
	dump_file=l10n_feedback_dump_$date.sql

        ### make a full dump of the database
	mysqldump $connection --opt --tables $all_tables > $dump_file

	gzip $dump_file
	;;

    user )
	date=$(date +%Y%m%d)
	dump_file=l10n_feedback_user_$date.sql

	mysqldump $connection --no-create-info \
            --tables l10n_feedback_translations --where="uid>1" > $dump_file
	mysqldump $connection --opt --tables l10n_feedback_users >> $dump_file
	mysqldump $connection --opt --tables l10n_feedback_votes >> $dump_file

	gzip $dump_file
	;;

    * )
	echo -e "Usage: $0 (schema|data|user)\n"
	exit 1	
	;;

esac
