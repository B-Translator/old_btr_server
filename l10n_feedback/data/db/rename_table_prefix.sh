#!/bin/bash
### change the old prefix of the tables to the new one

### what are the old and new prefices
old='l10n_suggestions_'
new='l10n_feedback_'

### list of all the tables
tables="diffs snapshots files projects templates locations strings translations votes users"

### get the mysql command
mysql="$(drush sql-connect)"
#echo $mysql;  exit 0;  ## debug

### rename each table
for table in $tables
do
    old_table=$old$table
    new_table=$new$table 
    echo -e "$old_table \t--> $new_table"
    #continue;  ##debug

    mysql_commands="
      drop table if exists $new_table;
      create table $new_table like $old_table;
      alter table $new_table disable keys;
      insert into $new_table select * from $old_table;
      alter table $new_table enable keys;"
    echo "$mysql_commands" | $mysql
done

#      drop table $old_table;
