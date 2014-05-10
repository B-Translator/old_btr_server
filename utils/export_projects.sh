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

### suppress verbose output during exports
export QUIET=true

### go to the script directory
cd $(dirname $0)

### export each project that is on the list
while read line
do
    origin=$(echo $line | cut -d'/' -f1)
    project=$(echo $line | cut -d'/' -f2)
    lng=$(echo $line | cut -d'/' -f3)
    #echo ./export_tgz.sh $origin $project $lng ; continue  ## debug
    if [ "$project" = '' ]; then continue; fi
    ../modules/custom/btrCore/data/export/export_tgz.sh $origin $project $lng
    filename=$origin-$project-$lng
    mv -f /tmp/$filename.tgz $output_dir/$filename.tgz
done < $project_list

