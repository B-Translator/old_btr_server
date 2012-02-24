#!/bin/bash

### get $data_root and $languages
. ../config.sh

### include function make-snapshot
. make-snapshot.sh

### import the PO files
for lng in $languages
do
    projects=$(ls $data_root/Mozilla/po/$lng/)
    for project in $projects
    do
	po_files=$(find $data_root/Mozilla/po/$lng/$project -name '*\.po')
	for file in $po_files
	do
	    pot_name=${file#*/$project/}
	    pot_name=${pot_name%.po}
            #echo $lng, $project, $pot_name, $file;  continue;  ## debug
	    ./po_import.php Mozilla $project $pot_name $lng $file
	done

	## make initial snapshots
	make-snapshot Mozilla $project $lng $po_files
    done
done
