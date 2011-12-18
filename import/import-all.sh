#!/bin/bash

### get the DB connection parameters
mysql_params="$($(which php) db_params.php bash)"
#echo $mysql_params  ## debug

### add the column 'imported' to the table of files
sql="ALTER TABLE l10n_suggestions_files
     ADD COLUMN imported TINYINT(1) DEFAULT 0"
echo $sql | mysql $mysql_params

### import all PO files
#./import-ubuntu.sh
./import-gnome.sh
./import-kde.sh

### drop column 'imported'
sql="ALTER TABLE l10n_suggestions_files DROP COLUMN imported"
echo $sql | mysql $mysql_params

### update the string count (in how many projects a string occurs)
sql="UPDATE l10n_suggestions_strings s
     SET s.count = (SELECT count(*)
                    FROM l10n_suggestions_locations l
                    WHERE l.sguid = s.sguid)"
echo $sql | mysql $mysql_params
