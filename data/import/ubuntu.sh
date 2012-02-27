#!/bin/bash

### get $data_root and $languages
. ../config.sh

### include function make-snapshot
. make-snapshot.sh

### get the list of projects to be imported
pot_dir="$data_root/ubuntu/fr/LC_MESSAGES"
if [ $# -gt 0 ]
then
    projects="$@"
else
    for file in $(ls $pot_dir/*.po)
    do
	file=$(basename $file)
	project=${file%%.po}
	projects="$projects $project"
    done
fi
#echo $projects;  exit;  ## debug

### import the POT/PO files
for project in $projects
do
    echo -e "\n==========> ubuntu $project"  #; continue;  ## debug
    pot_file="$pot_dir/$project.po"
    if [ ! -f $pot_file ]
    then
	echo "Error: template '$pot_file' not found."
	continue;
    fi

    ### import the POT file
    pot_name=$project
    ./pot_import.php ubuntu $project $pot_name $pot_file

    ### import the PO file of each language
    for lng in $languages
    do
	### get the PO filename
	po_file="$data_root/ubuntu/$lng/LC_MESSAGES/$project.po"
	if [ ! -f $po_file ]; then continue; fi
	echo -e "\n----------> $po_file"  #; continue;  ## debug

	### import the PO file
	./po_import.php ubuntu $project $pot_name $lng $po_file

	## make initial snapshot
	make-snapshot ubuntu $project $lng $po_file
    done

    #exit 0  ## debug
done
