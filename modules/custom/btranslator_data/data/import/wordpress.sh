#!/bin/bash

### get $data_root and $languages
. ../config.sh

### include function make-snapshot
. make-snapshot.sh

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

    ### make last snapshots before re-import
    make-last-snapshot $origin $project $lng


    ### import the POT and PO files
    po_files=$(find $po_dir -name '*\.po')
    for po_file in $po_files
    do
	pot_file=$po_file
	pot_name=${pot_file#*/$project/}
	pot_name=${pot_name%.po}
	#echo $origin $project $pot_name $lng $po_file;  continue;  ## debug
	./pot_import.php $origin $project $pot_name $pot_file
	./po_import.php $origin $project $pot_name $lng $po_file
    done

    ## make initial snapshot after (re)import
    make-snapshot $origin $project $lng $po_files
done
