#!/bin/bash

### go to the script directory
cd $(dirname $0)

### create the DB tables
mysql=$(drush sql-connect)
$mysql < db/btr_schema.sql

### import the vocabulary projects
import/vocabulary.sh

### import some PO files, just for testing/development
test/update.sh

### In order to import the real data, first of all check/modify
### 'config.sh', and then run 'update.sh'.
### Importing all the data can take a lot of time (many hours,
### maybe days), so it is a good idea to run the update script
### like this:
###   nohup nice ./update.sh &
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
    nohup nice $dir/update.sh &

Then you can check the progress at any time by:
    tail -f nohup.out

"
