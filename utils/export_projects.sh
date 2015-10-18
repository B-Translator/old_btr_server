#!/bin/bash
### Export all the projects that are listed in a file.
### Usually called by cron. It can be called by cron like this:
###
###     0 2 * * * nice \
###         /var/www/btr_dev/profiles/btr_server/utils/export_projects.sh \
###         /var/www/downloads/exports/ \
###         /var/www/downloads/exports/projects.txt


### get the parameters
if [ $# -lt 2 ]
then
    echo "Usage: $0 output_dir project_list.txt
project_list.txt contains lines of the form origin/project/lng
(where project can also be 'all')
"
    echo ""
    exit 1
fi
output_dir=$1
project_list=$2

### export each project that is on the list
while read line
do
    origin=$(echo $line | cut -d'/' -f1)
    project=$(echo $line | cut -d'/' -f2)
    lng=$(echo $line | cut -d'/' -f3)
    if [ "$project" = '' ]; then continue; fi

    cd /tmp
    filename=$origin-$project-$lng
    rm -rf $filename/
    mkdir -p $filename/
    drush @btr btrp-export $origin $project $lng /tmp/$filename/
    tar cfz $filename.tgz $filename/
    mv -f $filename.tgz $output_dir/$filename.tgz
done < $project_list

