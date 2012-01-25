#!/bin/bash

### get $data_root and $languages
. ../config.sh

### import the PO files from KDE
for lng in $languages
do
    dir="$data_root/KDE/$lng/messages"
    find $dir -name '*.po' > file_list.txt
    while read file
    do
	project=$(basename ${file%%.po})
	pot_name=$project
	../po_import.php KDE $project $pot_name $lng $file
    done < file_list.txt
done
rm file_list.txt
