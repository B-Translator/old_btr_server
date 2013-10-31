#!/bin/bash
### delete everything related to the given project
### (but not the strings, translations, etc.)

### get the arguments
if [ "$1" = '' ]
then
    echo "Usage: $0 project"
    echo
    exit 1
fi
project=$1

### go to the script directory
cd $(dirname $0)

### mysql command
dbname=${BTR_DATA:-btr_data}
mysql="mysql --defaults-file=/etc/mysql/debian.cnf -B --database=$dbname --skip-column-names"

### get a list of templates related to the project
sql="SELECT potid FROM btr_templates t
     LEFT JOIN btr_projects p ON (t.pguid = p.pguid)
     WHERE project = '$project'"
potid_list=$($mysql -e "$sql")

### purge the data of each template
for potid in $potid_list
do
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
sql="SELECT pguid FROM btr_projects WHERE project = '$project'"
pguid_list=$($mysql -e "$sql")

### delete the diffs and snapshots of each project
for pguid in $pguid_list
do
    $mysql -e "DELETE FROM btr_diffs WHERE pguid = '$pguid'"
    $mysql -e "DELETE FROM btr_snapshots WHERE pguid = '$pguid'"
done

### delete the project itself
$mysql -e "DELETE FROM btr_projects WHERE project = '$project'"
