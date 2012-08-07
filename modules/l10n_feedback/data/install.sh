#!/bin/bash

### go to the script directory
cd $(dirname $0)

### store database settings on db/settings.php and db/sql-connect.txt
drush php-script db/get-db-settings.php > db/settings.php
drush sql-connect | sed "s/'//g" > db/sql-connect.txt

### create the DB tables
mysql=$(cat db/sql-connect.txt)
#echo $mysql;  exit;  ## debug
$mysql < db/l10n_feedback_schema.sql

### import some PO files, just for testing/development
test/update.sh

### In order to import the real data, first of all check/modify
### 'config.sh', and then run 'update.sh'.
### Importing all the data can take a lot of time (many hours,
### maybe days), so it is a good idea to run the update script
### like this:
###   nohup ./update.sh &
### Then you can check the progress at any time by:
###   tail -f nohup.out

dir=$(dirname $0)
echo "
In order to import the real data, first of all check/modify
    $dir/config.sh
and then run
    $dir/update.sh

Importing all the data can take a lot of time (many hours,
maybe days), so it is a good idea to run the update script
like this:
    nohup $dir/update.sh &

Then you can check the progress at any time by:
    tail -f nohup.out

"


