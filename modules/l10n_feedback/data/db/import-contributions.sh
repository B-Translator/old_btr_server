#!/bin/bash
### Import the contributions from users (translations and votes)
### which are exported with 'export-contributions.sh'

function usage {
    echo -e "
 * Usage: $0 file.sql.gz
"
    exit 1
}

### get the argument
if [ "$1" = '' ]; then usage; fi
file_gz=$1

### mysqldump options
mysql="mysql --defaults-file=/etc/mysql/debian.cnf"

### create a temporary database
$mysql -e "
    DROP DATABASE IF EXISTS data_import;
    CREATE DATABASE data_import;
"

### import data to the temp DB
gunzip $file_gz
file_sql=${file_gz%.gz}
$mysql -D data_import < $file_sql

### get the name of database
DATA=${BTRANSLATOR_DATA:-btranslator_data}

### append to the trash tables the records that are not already there
$mysql -e "
    INSERT INTO $DATA.l10n_feedback_translations_trash
        SELECT T1.* FROM data_import.l10n_feedback_translations_trash T1
        LEFT JOIN $DATA.l10n_feedback_translations_trash T2
                  ON (T1.tguid = T2.tguid AND T1.time = T2.time)
        WHERE T2.tguid IS NULL;

    INSERT INTO $DATA.l10n_feedback_votes_trash
        SELECT T1.* FROM data_import.l10n_feedback_votes_trash T1
        LEFT JOIN $DATA.l10n_feedback_votes_trash T2
                  ON (T1.tguid = T2.tguid 
                      AND T1.umail = T2.umail 
                      AND T1.ulng = T2.ulng
                      AND T1.time = T2.time)
        WHERE T2.tguid IS NULL;
"

### delete translations and votes that have been removed
$mysql -e "
    DELETE $DATA.l10n_feedback_translations
    FROM data_import.l10n_feedback_translations_trash
    INNER JOIN $DATA.l10n_feedback_translations
        ON (data_import.l10n_feedback_translations_trash.tguid = $DATA.l10n_feedback_translations.tguid 
            AND data_import.l10n_feedback_translations_trash.time = $DATA.l10n_feedback_translations.time);

    DELETE $DATA.l10n_feedback_votes
    FROM data_import.l10n_feedback_votes_trash
    INNER JOIN $DATA.l10n_feedback_votes
        ON ( data_import.l10n_feedback_votes_trash.tguid = $DATA.l10n_feedback_votes.tguid 
             AND data_import.l10n_feedback_votes_trash.umail = $DATA.l10n_feedback_votes.umail 
             AND data_import.l10n_feedback_votes_trash.ulng = $DATA.l10n_feedback_votes.ulng
             AND data_import.l10n_feedback_votes_trash.time = $DATA.l10n_feedback_votes.time );
"

### insert any new translations and votes that are not already there
$mysql -e "
    INSERT INTO $DATA.l10n_feedback_translations
        SELECT T1.* FROM data_import.l10n_feedback_translations T1
        LEFT JOIN $DATA.l10n_feedback_translations T2
                  ON (T1.tguid = T2.tguid)
        WHERE T2.tguid IS NULL;

    INSERT INTO $DATA.l10n_feedback_votes
        SELECT T1.* FROM data_import.l10n_feedback_votes T1
        LEFT JOIN $DATA.l10n_feedback_votes T2
                  ON (T1.tguid = T2.tguid 
                      AND T1.umail = T2.umail 
                      AND T1.ulng = T2.ulng)
        WHERE T2.tguid IS NULL;
"

### delete the temp DB
$mysql -e "DROP DATABASE data_import;"