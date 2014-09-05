#!/bin/bash
### Import WordPress projects and translations.

### go to the script directory
cd $(dirname $0)

### get config vars
. ../config.sh

origin=WordPress
for lng in $languages
do
    project="wp-$lng"

    echo -e "\n==========> $origin $project "  # ;  continue;  ## debug
    po_dir=$data_root/$origin/$project
    if [ ! -d $po_dir ]
    then
	echo "Error: project '$project' not found."
	continue;
    fi

    ### import the project
    $drush btrp-add $origin $project $po_dir
    $drush btrp-import $origin $project $lng $po_dir
done
