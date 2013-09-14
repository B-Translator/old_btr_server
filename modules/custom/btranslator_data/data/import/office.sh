#!/bin/bash

### get $data_root and $languages
. ../config.sh

### include function make-snapshot
. make-snapshot.sh

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
for project in $(ls $pot_dir)
do
    echo -e "\n==========> LibreOffice $project"  # ;  continue;  ## debug
    if [ ! -d $pot_dir/$project ]
    then
	echo "Error: project '$project' not found."
	continue;
    fi

    ### make last snapshots before re-import
    for lng in $languages
    do
	make-last-snapshot LibreOffice $project $lng
    done

    ### import the POT files
    pot_files=$(find $pot_dir/$project -name '*\.po')
    for pot_file in $pot_files
    do
	pot_name=${pot_file#*/$project/}
	pot_name=${pot_name%.po}
        #echo LibreOffice $project $pot_name $pot_file;  continue;  ## debug
	./pot_import.php LibreOffice $project $pot_name $pot_file
    done

    ### import the PO files of each language
    for lng in $languages
    do
	po_dir=$data_root/LibreOffice/$lng/$project
	if [ ! -d $po_dir ]; then continue; fi
	echo -e "\n----------> LibreOffice $project $lng"  # ;  continue;  ## debug

	### import the PO files
	po_files=$(find $po_dir -name '*\.po')
	for po_file in $po_files
	do
	    pot_name=${po_file#*/$project/}
	    pot_name=${pot_name%.po}
            #echo LibreOffice $project $pot_name $lng $po_file;  continue;  ## debug
	    ./po_import.php LibreOffice $project $pot_name $lng $po_file
	done

	## make initial snapshots after (re)import
	make-snapshot LibreOffice $project $lng $po_files
    done

    #exit 0  ## debug
done
