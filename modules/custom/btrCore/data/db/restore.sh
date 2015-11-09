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
backup_dir="/tmp/$(basename ${backup_file%.tgz})"

### execute the sql scripts of the backup
mysql='mysql --defaults-file=/etc/mysql/debian.cnf'
$mysql --database=bcl < $backup_dir/bcl.sql
$mysql --database=btr < $backup_dir/btr.sql
$mysql --database=btr_data < $backup_dir/btr_data.sql

### cleanup
rm -rf $backup_dir
