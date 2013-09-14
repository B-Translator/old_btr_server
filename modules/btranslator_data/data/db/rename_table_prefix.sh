#!/bin/bash
### change the old prefix of the tables to the new one

### what are the old and new prefices
old='l10n_suggestions_'
new='btr_'

### list of all the tables
tables="diffs snapshots files projects templates locations strings translations votes users"

dbname=${BTRANSLATOR_DATA:-btranslator_data}
mysql="mysql --defaults-file=/etc/mysql/debian.cnf -B --database=$dbname"

### rename each table
for table in $tables
do
    old_table=$old$table
    new_table=$new$table
    echo -e "$old_table \t--> $new_table"
    #continue;  ##debug

    $mysql -e "
      drop table if exists $new_table;
      create table $new_table like $old_table;
      alter table $new_table disable keys;
      insert into $new_table select * from $old_table;
      alter table $new_table enable keys;
    "
done

#      drop table $old_table;
