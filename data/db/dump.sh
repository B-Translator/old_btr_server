#!/bin/bash
### dump the tables of the module l10n_suggestions

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
connection="$($(which php) get-connection.php bash)"
connection=$(echo $connection | sed -e 's/--database=/--database /')
#echo $connection;  exit 0;  ## debug

### list of all the tables
all_tables="
    l10n_suggestions_diffs
    l10n_suggestions_snapshots 
    l10n_suggestions_files
    l10n_suggestions_projects
    l10n_suggestions_templates
    l10n_suggestions_locations
    l10n_suggestions_strings
    l10n_suggestions_translations
    l10n_suggestions_votes
    l10n_suggestions_users
"

### make the required dump
case "$dump_mode" in

    schema )
        ### dump only the schema of the database
	mysqldump $connection \
            --no-data --compact --add-drop-table \
            --tables $all_tables > l10n_suggestions_schema.sql

        ### fix a little bit the file
	sed -e '/^SET /d' -i l10n_suggestions_schema.sql
	;;

    data )
	date=$(date +%Y%m%d)
	dump_file=l10n_suggestions_dump_$date.sql

        ### make a full dump of the database
	mysqldump $connection --opt --tables $all_tables > $dump_file

	gzip $dump_file
	;;

    user )
	date=$(date +%Y%m%d)
	dump_file=l10n_suggestions_user_$date.sql

	mysqldump $connection --no-create-info \
            --tables l10n_suggestions_translations --where="uid>1" > $dump_file
	mysqldump $connection --opt --tables l10n_suggestions_users >> $dump_file
	mysqldump $connection --opt --tables l10n_suggestions_votes >> $dump_file

	gzip $dump_file
	;;

    * )
	echo -e "Usage: $0 (schema|data|user)\n"
	exit 1	
	;;

esac
