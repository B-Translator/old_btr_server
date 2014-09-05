#!/bin/bash
### Import KDE projects and translations.

### go to the script directory
cd $(dirname $0)

### get config vars
. ../config.sh

### get the list of projects to be imported
pot_dir=$data_root/KDE/fr/messages
if [ $# -gt 0 ]
then
    projects="$@"
else
    projects=$(ls $pot_dir)
fi
#echo $projects;  exit;  ## debug

### import the PO files, using the fr PO file as template (POT)
origin=KDE
for project in $projects
do
    echo -e "\n==========> $origin $project"  # ;  continue;  ## debug
    if [ ! -d $pot_dir/$project ]
    then
	echo "Error: project '$project' not found."
	continue;
    fi

    ### create the project
    $drush btrp-add $origin $project $pot_dir/$project

    ### import the PO files of each language
    for lng in $languages
    do
	po_dir=$data_root/KDE/$lng/messages/$project
	if [ ! -d $po_dir ]; then continue; fi
	echo -e "\n----------> $origin $project $lng"  # ;  continue;  ## debug

	$drush btrp-import $origin $project $lng $po_dir
    done

    #exit 0  ## debug
done
