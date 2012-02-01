#!/bin/bash

### get $data_root and $languages
. ../config.sh

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
    done
done

exit 0

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
