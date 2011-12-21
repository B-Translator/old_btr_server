#!/bin/bash

### get $data_root and $languages
. ./config.sh

### import the POT files from KDE
lng=fr

dir="$data_root/KDE/$lng/messages"
find $dir -name '*.po' > file_list.txt
while read file
do
    project=$(basename ${file%%.po})
    ./pot_import.php KDE $project $file
done < file_list.txt

rm file_list.txt
