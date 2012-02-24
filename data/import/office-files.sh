#!/bin/bash

### get $data_root and $languages
. ../config.sh

### include function make-snapshot
. make-snapshot.sh

### import the PO files from GNOME
for lng in $languages
do
    projects=$(ls $data_root/LibreOffice/$lng/)
    for project in $projects
    do
	po_files=$(find $data_root/LibreOffice/$lng/$project -name '*\.po')
	for file in $po_files
	do
	    pot_name=${file#*/$project/}
	    pot_name=${pot_name%.po}
            #echo $lng, $project, $pot_name, $file;  continue;  ## debug
	    ./po_import.php LibreOffice $project $pot_name $lng $file
	done

	## make initial snapshots
	make-snapshot LibreOffice $project $lng $po_files
    done
done
