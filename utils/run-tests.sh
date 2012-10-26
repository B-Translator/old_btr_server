#!/bin/bash
### Although the test script backups and restores the DB, it is better
### to run it only on a test installation of B-Translator.
### The output of the tests will be on the 'tests/' under
### the root drupal directory.

### enable the module simpletest (in case it is not enabled)
drush pm-enable simpletest

### go to the drupal directory
cd $(dirname $0)
drupal_dir=$(drush drupal-directory)
cd $drupal_dir

btranslator_dir="$drupal_dir/profiles/btranslator"
data_dir="$btranslator_dir/modules/l10n_feedback/data"

timestamp=$(date +%s)
dump_file="tests/backup_$timestamp.sql"
output_file="tests/output_$timestamp.txt"
mkdir -p tests/

### make a backup of the database
connection="$(drush sql-connect | sed -e s/\'//g | sed -e 's/^mysql //' | sed -e 's/--database=/--database /')"
mysqldump $connection --opt > $dump_file

### run the test scripts
php scripts/run-tests.sh --verbose B-Translator > $output_file

### restore the database
mysql=$(drush sql-connect | sed -e s/\'//g )
$mysql < $dump_file
