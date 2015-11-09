#!/bin/bash
### Restore the backup made with backup.sh

### get the backup file
if [ $# -ne 1 ]
then
    echo "Usage: $0 backup-file.tgz"
    exit 1
fi

backup_file=$1
if ! test -f $backup_file
then
    echo "File '$backup_file' does not exist"
    exit 2
fi

### extract the backup file on /tmp
tar xz -C /tmp/ -f $backup_file
backup_dir=$(ls -dt /tmp/btr-backup-*/ | head -n 1)

### execute the sql scripts of the backup
drush @bcl sql-query --file=$backup_dir/bcl.sql
drush @btr sql-query --file=$backup_dir/btr.sql
$(drush @btr sql-connect --database=btr_db) < $backup_dir/btr_data.sql

### cleanup
rm -rf $backup_dir
