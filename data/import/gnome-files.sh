#!/bin/bash

### get $data_root and $languages
. ../config.sh

### include function make-snapshot
. make-snapshot.sh

### import the PO files from GNOME
for lng in $languages
do
    for file in $(ls $data_root/GNOME/$lng/*.$lng.po)
    do
	basename=$(basename $file)
	project=${basename%.*.$lng.po}
	pot_name=$project
	#echo $file;  echo $project;  continue;  ## debug
	../po_import.php GNOME $project $pot_name $lng $file

	## make initial snapshots
	make-snapshot GNOME $project $lng $file
    done
done
