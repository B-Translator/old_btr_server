#!/bin/bash

### go to the script directory
cd $(dirname $0)

### store database settings on db/settings.php and db/sql-connect.txt
drush php-script db/get-db-settings.php > db/settings.php
drush sql-connect > db/sql-connect.txt
#drush -l l10n.org.al php-script db/get-db-settings.php > db/settings.php
#drush -l l10n.org.al sql-connect > db/sql-connect.txt

### create the DB tables
mysql=$(cat db/sql-connect.txt)
#echo $mysql;  exit;  ## debug
$mysql < db/l10n_feedback_schema.sql

### import some PO files, just for testing/development
./update_test.sh

### In order to import the real data, first of all check/modify
### 'config.sh', and then run 'update.sh'.
### Importing all the data can take a lot of time (many hours,
### maybe days), so it is a good idea to run the update script
### like this:
###   nohup ./update.sh &
### Then you can check the progress at any time by:
###   tail -f nohup.out

echo "
  In order to import the real data, first of all check/modify
  'config.sh', and then run 'update.sh'.
  Importing all the data can take a lot of time (many hours,
  maybe days), so it is a good idea to run the update script
  like this:
    nohup ./update.sh &
  Then you can check the progress at any time by:
    tail -f nohup.out

"


