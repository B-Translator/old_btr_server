#!/bin/bash

### go to the script directory
cd $(dirname $0)

### create the DB tables
mysql=$(drush sql-connect)
$mysql < db/btr_schema.sql

### import some PO files, just for testing/development
test "$development" != 'false' && test/update.sh

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
In order to import the real data, first of all edit:

    /var/www/data/config.sh

and then run:

    /var/www/data/get.sh
    tail -f /var/www/data/nohup-get.out

    /var/www/data/import.sh
    tail -f /var/www/data/nohup-import.out

Downloading and importing all the projects can take
a lot of time (many hours, maybe days).

"
