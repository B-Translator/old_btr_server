#!/bin/bash

### get $data_root and $languages
. ../config.sh

### include function make-snapshot
. make-snapshot.sh

### import the PO files
for lng in $languages
do
    projects=$(ls $data_root/KDE/$lng/messages)
    for project in $projects
    do
	po_files=$(find $data_root/KDE/$lng/messages/$project -name '*\.po')
	for file in $po_files
	do
	    pot_name=${file#*/$project/}
	    pot_name=${pot_name%.po}
            #echo $project, $pot_name, $lng, $file;  continue;  ## debug
	    ../po_import.php KDE $project $pot_name $lng $file
	done
	
	## make initial snapshots
	make-snapshot KDE $project $lng $po_files
    done
done
