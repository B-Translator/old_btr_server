#!/bin/bash
### Export contributions from users (translations and votes)
### since a certain date.

### get the arguments
from_date=${1:-'0000-00-00'}    # in format YYYY-MM-DD

### mysqldump default options
dbname=${BTRANSLATOR_DATA:-btranslator_data}
mysqldump="mysqldump --defaults-file=/etc/mysql/debian.cnf --database=$dbname"

### get the dump filename
date1=${from_date//-/}
date2=$(date +%Y%m%d)
dump_file=contributions-$date1-$date2.sql

### dump translations and votes
not_admin="umail NOT IN ('admin@example.com')"
$mysqldump --tables l10n_feedback_translations \
    --where="time > '$from_date' AND $not_admin" > $dump_file
$mysqldump --tables l10n_feedback_votes \
    --where="time > '$from_date'" >> $dump_file

### dump also deleted translations and votes
$mysqldump --tables l10n_feedback_translations_trash \
    --where="d_time > '$from_date'" >> $dump_file
$mysqldump --tables l10n_feedback_votes_trash \
    --where="d_time > '$from_date'" >> $dump_file

### compress the dump file
gzip $dump_file 