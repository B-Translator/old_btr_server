#!/bin/bash

### get $data_root and $languages
. ./config.sh

### import the PO files from GNOME
for lng in $languages
do
    find "$data_root/GNOME" -name $lng\.po > file_list.txt
    while read file
    do
	project=$(basename $(dirname $file))
	./po_import.php $project $lng GNOME $file
    done < file_list.txt
done
rm file_list.txt