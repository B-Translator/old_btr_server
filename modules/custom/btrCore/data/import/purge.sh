#!/bin/bash
### delete everything related to the given origin and project
### (but not the strings, translations, etc.)

### get the arguments
if [ "$1" = '' ]
then
    echo "Usage: $0 origin [project]"
    echo
    exit 1
fi
origin=$1
project=$2
sql_condition="origin = '$origin'"
if [ "$project" != '' ]
then
    sql_condition="$sql_condition AND project = '$project'"
fi

### go to the script directory
cd $(dirname $0)

### build the mysql command
dbname=${BTR_DATA:-btr_data}
mysql="mysql --defaults-file=/etc/mysql/debian.cnf -B --database=$dbname --skip-column-names"

### get a list of templates related to the projects of the given origin
sql="SELECT potid FROM btr_templates t
     LEFT JOIN btr_projects p ON (t.pguid = p.pguid)
     WHERE $sql_condition"
potid_list=$($mysql -e "$sql")

### purge the data of each template
for potid in $potid_list
do
    #echo $potid; continue;  ## debug

    ### decrement the count of the strings related to this template
    $mysql -e "
         UPDATE btr_strings AS s
         INNER JOIN (SELECT sguid FROM btr_locations WHERE potid = $potid) AS l
             ON (l.sguid = s.sguid)
         SET s.count = s.count - 1
    "

    ### delete the locations of this template
    $mysql -e "DELETE FROM btr_locations WHERE potid = $potid"

    ### delete the files related to this template
    $mysql -e "DELETE FROM btr_files WHERE potid = $potid"

    ### delete the template itself
    $mysql -e "DELETE FROM btr_templates WHERE potid = $potid"
done

### get a list of projects with this name
sql="SELECT pguid FROM btr_projects WHERE $sql_condition"
pguid_list=$($mysql -e "$sql")

### delete the diffs and snapshots of each project
for pguid in $pguid_list
do
    #echo $pguid;  continue;  # debug
    $mysql -e "DELETE FROM btr_diffs WHERE pguid = '$pguid'"
    $mysql -e "DELETE FROM btr_snapshots WHERE pguid = '$pguid'"
done

#exit # debug

### delete the projects themselves
$mysql -e "DELETE FROM btr_projects WHERE $sql_condition"


