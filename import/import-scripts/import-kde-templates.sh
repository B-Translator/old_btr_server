#!/bin/bash

### get $data_root and $languages
. ../config.sh

### import the POT files from KDE
lng=fr

projects=$(ls $data_root/KDE/$lng/messages)
for project in $projects
do
    po_files=$(find $data_root/KDE/$lng/messages/$project -name '*\.po')
    for file in $po_files
    do
	pot_name=${file#*/$project/}
	pot_name=${pot_name%.po}
        #echo $project, $pot_name, $file;  continue;  ## debug
	../pot_import.php KDE $project $pot_name $file
    done
done

exit 0

dir="$data_root/KDE/$lng/messages"
find $dir -name '*.po' > file_list.txt
while read file
do
    project=$(basename ${file%%.po})
    pot_name=$project
    ../pot_import.php KDE $project $pot_name $file
done < file_list.txt

rm file_list.txt
