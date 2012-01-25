#!/bin/bash

### get $data_root and $languages
. ../config.sh

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
    done
done
