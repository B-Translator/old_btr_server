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
$mysql -D $DATA -e "
    INSERT INTO l10n_feedback_translations_trash
        SELECT T1.* FROM data_import.l10n_feedback_translations_trash T1
        LEFT JOIN l10n_feedback_translations_trash T2
                  ON (T1.tguid = T2.tguid AND T1.time = T2.time)
        WHERE T2.tguid IS NULL;

    INSERT INTO l10n_feedback_votes_trash
        SELECT T1.* FROM data_import.l10n_feedback_votes_trash T1
        LEFT JOIN l10n_feedback_votes_trash T2
                  ON (T1.tguid = T2.tguid 
                      AND T1.umail = T2.umail 
                      AND T1.ulng = T2.ulng
                      AND T1.time = T2.time)
        WHERE T2.tguid IS NULL;
"

### delete translations and votes that have been removed
$mysql -D data_import -e "
    DELETE $DATA.l10n_feedback_translations
    FROM l10n_feedback_translations_trash
    INNER JOIN $DATA.l10n_feedback_translations
        ON (l10n_feedback_translations_trash.tguid = $DATA.l10n_feedback_translations.tguid 
            AND l10n_feedback_translations_trash.time = $DATA.l10n_feedback_translations.time);

    DELETE $DATA.l10n_feedback_votes
    FROM l10n_feedback_votes_trash
    INNER JOIN $DATA.l10n_feedback_votes
        ON ( l10n_feedback_votes_trash.tguid = $DATA.l10n_feedback_votes.tguid 
             AND l10n_feedback_votes_trash.umail = $DATA.l10n_feedback_votes.umail 
             AND l10n_feedback_votes_trash.ulng = $DATA.l10n_feedback_votes.ulng
             AND l10n_feedback_votes_trash.time = $DATA.l10n_feedback_votes.time );
"

### delete any dangling vote (that might have remained 
### after deleting the translations above)
$mysql -D $DATA -e "
    INSERT INTO l10n_feedback_votes_trash
        SELECT T2.*, NOW() FROM data_import.l10n_feedback_translations_trash T1
        INNER JOIN l10n_feedback_votes T2 ON (T1.tguid = T2.tguid) 
        LEFT JOIN l10n_feedback_votes_trash T3
                  ON (T3.tguid = T2.tguid 
                      AND T3.umail = T2.umail 
                      AND T3.ulng = T2.ulng)
        WHERE T3.tguid IS NULL;
"

### insert any new translations and votes that are not already there
### translations suggested by users should replace those that are
### imported from PO files
$mysql -D $DATA -e "
    DELETE $DATA.l10n_feedback_translations
    FROM data_import.l10n_feedback_translations
    INNER JOIN $DATA.l10n_feedback_translations
        ON (data_import.l10n_feedback_translations.tguid = $DATA.l10n_feedback_translations.tguid)
    WHERE $DATA.l10n_feedback_translations.umail = 'admin@example.com';

    INSERT INTO l10n_feedback_translations
        SELECT T1.* FROM data_import.l10n_feedback_translations T1
        LEFT JOIN l10n_feedback_translations T2
                  ON (T1.tguid = T2.tguid)
        WHERE T2.tguid IS NULL;

    INSERT INTO l10n_feedback_votes (tguid, umail, ulng, time, active)
        SELECT T1.tguid, T1.umail, T1.ulng, T1.time, T1.active 
        FROM data_import.l10n_feedback_votes T1
        LEFT JOIN l10n_feedback_votes T2
                  ON (T1.tguid = T2.tguid 
                      AND T1.umail = T2.umail 
                      AND T1.ulng = T2.ulng)
        WHERE T2.tguid IS NULL;
"

### for translations on which votes are added or removed
### recalculate (recount) the number of votes
$mysql -D data_import -e "
    CREATE TEMPORARY TABLE tmp_translations AS (
        SELECT * FROM (
            SELECT tguid FROM l10n_feedback_votes
            UNION 
            SELECT tguid FROM l10n_feedback_votes_trash
        ) AS T
    );

    CREATE TEMPORARY TABLE tmp_counts AS (
        SELECT T1.tguid, count(*) AS count
        FROM $DATA.l10n_feedback_translations T1
        INNER JOIN tmp_translations T2 ON (T1.tguid = T2.tguid)
        INNER JOIN $DATA.l10n_feedback_votes T3 ON (T2.tguid = T3.tguid)
        GROUP BY T1.tguid
    );

    UPDATE $DATA.l10n_feedback_translations T1
    INNER JOIN tmp_counts T2 ON (T1.tguid = T2.tguid)
    SET T1.count = T2.count;
"

### delete the temp DB
$mysql -e "DROP DATABASE data_import;"