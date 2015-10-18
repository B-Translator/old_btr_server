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
A=data_import
$mysql -e "
    DROP DATABASE IF EXISTS $A;
    CREATE DATABASE $A;
"

### import data to the temp DB
gunzip $file_gz
file_sql=${file_gz%.gz}
$mysql -D $A < $file_sql

### get the name of database
B=${BTR_DATA:-btr_data}

### Find multiple votes on both A_votes and B_votes and append to
### A_votes_trash all of them except for the latest vote.
$mysql -e "
    CREATE TEMPORARY TABLE $A.tmp_tguid AS (
        SELECT DISTINCT tguid FROM $A.btr_votes
    );

    CREATE TEMPORARY TABLE $A.tmp_all_votes AS (
        SELECT * FROM (
            SELECT * FROM $A.btr_votes
            UNION ALL
            SELECT T1.* FROM $B.btr_votes T1
                INNER JOIN $A.tmp_tguid T2 ON (T1.tguid = T2.tguid)
        ) AS T
    );

    CREATE TEMPORARY TABLE $A.tmp_latest_votes AS (
        SELECT tguid, umail, ulng, max(time) AS max_time
        FROM $A.tmp_all_votes
        GROUP by tguid, umail, ulng
        HAVING count(*) > 1
    );

    INSERT INTO $A.btr_votes_trash
        SELECT T1.*, NOW()
        FROM $A.btr_votes T1
        LEFT JOIN $A.tmp_latest_votes T2
            ON (T1.tguid = T2.tguid AND T1.umail = T2.umail
                AND T1.ulng = T2.ulng AND T1.time < T2.max_time);

    INSERT INTO $A.btr_votes_trash
        SELECT T1.*, NOW()
        FROM $B.btr_votes T1
        INNER JOIN $A.tmp_tguid T2 ON (T1.tguid = T2.tguid)
        LEFT JOIN $A.tmp_latest_votes T3
            ON (T1.tguid = T3.tguid AND T1.umail = T3.umail
                AND T1.ulng = T3.ulng AND T1.time < T3.max_time);
"

### Find any votes on B_votes that belong to translations that are
### deleted on *A* (A_translations_trash) and append them to
### A_votes_trash.
$mysql -e "
    INSERT INTO $A.btr_votes_trash
        SELECT T1.*, NOW()
        FROM $B.btr_votes T1
        INNER JOIN $A.btr_translations_trash T2
                  ON (T1.tguid = T2.tguid)
        LEFT JOIN $A.btr_votes_trash T3
                  ON (T3.tguid = T1.tguid AND T3.umail = T1.umail
                      AND T3.ulng = T1.ulng)
        WHERE T3.tguid IS NULL;
"


### append to the trash tables the records that are not already there
$mysql -e "
    INSERT INTO $B.btr_translations_trash
        SELECT T1.* FROM $A.btr_translations_trash T1
        LEFT JOIN $B.btr_translations_trash T2
                  ON (T1.tguid = T2.tguid AND T1.time = T2.time)
        WHERE T2.tguid IS NULL;

    INSERT INTO $B.btr_votes_trash
        SELECT T1.* FROM $A.btr_votes_trash T1
        LEFT JOIN $B.btr_votes_trash T2
                  ON (T1.tguid = T2.tguid
                      AND T1.umail = T2.umail
                      AND T1.ulng = T2.ulng
                      AND T1.time = T2.time)
        WHERE T2.tguid IS NULL;
"


### insert any new translations and votes that are not already there
### translations suggested by users should replace those that are
### imported from PO files
$mysql -e "
    DELETE $B.btr_translations
    FROM $A.btr_translations
    INNER JOIN $B.btr_translations
        ON ($A.btr_translations.tguid = $B.btr_translations.tguid)
    WHERE $B.btr_translations.umail = '';

    INSERT INTO $B.btr_translations
        SELECT T1.* FROM $A.btr_translations T1
        LEFT JOIN $B.btr_translations T2
                  ON (T1.tguid = T2.tguid)
        WHERE T2.tguid IS NULL;

    INSERT INTO $B.btr_votes (tguid, umail, ulng, time, active)
        SELECT T1.tguid, T1.umail, T1.ulng, T1.time, T1.active
        FROM $A.btr_votes T1
        LEFT JOIN $B.btr_votes T2
                  ON (T1.tguid = T2.tguid
                      AND T1.umail = T2.umail
                      AND T1.ulng = T2.ulng)
        WHERE T2.tguid IS NULL;
"


### Remove from B_translations the records that are on
### A_translations_trash and from B_votes the records that are on
### B_votes_trash.
$mysql -e "
    DELETE $B.btr_translations
    FROM $A.btr_translations_trash
    INNER JOIN $B.btr_translations
        ON ($A.btr_translations_trash.tguid = $B.btr_translations.tguid
            AND $A.btr_translations_trash.time = $B.btr_translations.time);

    DELETE $B.btr_votes
    FROM $A.btr_votes_trash
    INNER JOIN $B.btr_votes
        ON ( $A.btr_votes_trash.tguid = $B.btr_votes.tguid
             AND $A.btr_votes_trash.umail = $B.btr_votes.umail
             AND $A.btr_votes_trash.ulng = $B.btr_votes.ulng
             AND $A.btr_votes_trash.time = $B.btr_votes.time );
"


### for translations on which votes are added or removed
### recalculate (recount) the number of votes
$mysql -e "
    CREATE TEMPORARY TABLE $A.tmp_translations AS (
        SELECT * FROM (
            SELECT tguid FROM $A.btr_votes
            UNION
            SELECT tguid FROM $A.btr_votes_trash
        ) AS T
    );

    CREATE TEMPORARY TABLE $A.tmp_counts AS (
        SELECT T1.tguid, count(*) AS count
        FROM $B.btr_translations T1
        INNER JOIN $A.tmp_translations T2 ON (T1.tguid = T2.tguid)
        INNER JOIN $B.btr_votes T3 ON (T2.tguid = T3.tguid)
        GROUP BY T1.tguid
    );

    UPDATE $B.btr_translations T1
    INNER JOIN $A.tmp_counts T2 ON (T1.tguid = T2.tguid)
    SET T1.count = T2.count;
"

### delete the temp DB
$mysql -e "DROP DATABASE $A;"
