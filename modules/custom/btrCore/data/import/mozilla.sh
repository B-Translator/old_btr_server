#!/bin/bash
### Import Mozilla projects and translations.

### go to the script directory
cd $(dirname $0)

### get config vars
. ../config.sh

### get the list of projects to be imported
pot_dir=$data_root/Mozilla/po/en-GB
if [ $# -gt 0 ]
then
    projects="$@"
else
    projects=$(ls $pot_dir)
fi
#echo $projects;  exit;  ## debug

### import the PO files, using the en-GB files as templates
for project in $(ls $pot_dir)
do
    echo -e "\n==========> Mozilla $project"  # ;  continue;  ## debug
    if [ ! -d $pot_dir/$project ]
    then
	echo "Error: project '$project' not found."
	continue;
    fi

    ### create the project
    $drush btrp-add Mozilla $project $pot_dir/$project

    ### import the PO files of each language
    for lng in $languages
    do
	po_dir=$data_root/Mozilla/po/$lng/$project
	if [ ! -d $po_dir ]; then continue; fi
	echo -e "\n----------> Mozilla $project $lng"  # ;  continue;  ## debug

	$drush btrp-import Mozilla $project $lng $po_dir
    done

    #exit 0  ## debug
done
