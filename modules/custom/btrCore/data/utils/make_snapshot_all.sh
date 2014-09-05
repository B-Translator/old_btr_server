#!/bin/bash
### Make a snapshot of all the projects.

### go to the script directory
cd $(dirname $0)

### get the variable $languages
. ../config.sh

### get a list of all the projects
$drush btrp-ls > project_list.txt

### make a snapshot for each project and for each language
comment="make_snapshot_all.sh"
while read line
do
    origin=$(echo $line | cut -d'/' -f1)
    project=$(echo $line | cut -d'/' -f2)
    for lng in $languages
    do
        echo $drush btrp-snapshot $origin $project $lng "$comment"
	$drush btrp-snapshot $origin $project $lng "$comment"
    done
done < project_list.txt

### clean up
rm project_list.txt

