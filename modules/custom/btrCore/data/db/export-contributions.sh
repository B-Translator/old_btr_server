#!/bin/bash
### Export contributions from users (translations and votes)
### since a certain date.

### get the arguments
from_date=${1:-'0000-00-00'}    # in format YYYY-MM-DD

### mysqldump default options
dbname=${BTR_DATA:-btr_data}
mysqldump="mysqldump --defaults-file=/etc/mysql/debian.cnf --databases $dbname"

### get the dump filename
date1=${from_date//-/}
date2=$(date +%Y%m%d)
dump_file=contributions-$date1-$date2.sql

### dump translations and votes
$mysqldump --tables btr_translations \
    --where="time > '$from_date' AND umail != ''" > $dump_file
$mysqldump --tables btr_votes \
    --where="time > '$from_date'" >> $dump_file

### dump also deleted translations and votes
$mysqldump --tables btr_translations_trash \
    --where="d_time > '$from_date'" >> $dump_file
$mysqldump --tables btr_votes_trash \
    --where="d_time > '$from_date'" >> $dump_file

### compress the dump file
gzip $dump_file
