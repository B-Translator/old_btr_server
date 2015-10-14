#!/bin/bash
### Materialized views are used to speed-up
### term autocompletion of vocabularies.
### Update all the mv tables.

### go to the script directory
cd $(dirname $0)

### mysql and mysqldump options
dbname=${BTR_DATA:-btr_data}
mysql="mysql --defaults-file=/etc/mysql/debian.cnf --database=$dbname -B"

### drop all 'btr_mv_*' tables (except 'btr_mv_sample')
tables=$($mysql -e "SHOW TABLES" | grep '^btr_mv_' | sed -e '/btr_mv_sample/d')
for table in $tables
do
    $mysql -e "DROP TABLE IF EXISTS $table"
done

### for each vocabulary create a mv table
vocabularies=$(drush btr-vocabulary-list | gawk '{print $2 "_" $1}')
for vocabulary in $vocabularies
do
    table="btr_mv_${vocabulary,,}"
    $mysql -e "CREATE TABLE $table LIKE btr_mv_sample"
    $mysql -e "INSERT INTO $table
	SELECT DISTINCT s.string FROM btr_strings s
	JOIN btr_locations l ON (l.sguid = s.sguid)
	JOIN btr_templates t ON (t.potid = l.potid)
	JOIN btr_projects  p ON (p.pguid = t.pguid)
	WHERE p.project = '$vocabulary'
	  AND p.origin = 'vocabulary'
	ORDER BY s.string"
done
