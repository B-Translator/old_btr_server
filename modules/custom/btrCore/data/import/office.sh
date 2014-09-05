#!/bin/bash
### Import LibreOffice projects and translations.

### go to the script directory
cd $(dirname $0)

### get config vars
. ../config.sh

### get the list of projects to be imported
pot_dir=$data_root/LibreOffice/fr
if [ $# -gt 0 ]
then
    projects="$@"
else
    projects=$(ls $pot_dir)
fi
#echo $projects;  exit;  ## debug

### import the PO files, using the fr PO file as template (POT)
for project in $projects
do
    echo -e "\n==========> LibreOffice $project"  # ;  continue;  ## debug
    if [ ! -d $pot_dir/$project ]
    then
	echo "Error: project '$project' not found."
	continue;
    fi

    ### create the project
    $drush btrp-add LibreOffice $project $pot_dir/$project

    ### import the PO files of each language
    for lng in $languages
    do
	po_dir=$data_root/LibreOffice/$lng/$project
	if [ ! -d $po_dir ]; then continue; fi
	echo -e "\n----------> LibreOffice $project $lng"  # ;  continue;  ## debug
	$drush btrp-import LibreOffice $project $lng $po_dir
    done

    #exit 0  ## debug
done
