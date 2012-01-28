#!/bin/bash

### get $data_root and $languages
. ../config.sh

### use the fr PO files as POT files
lng=fr

projects=$(ls $data_root/LibreOffice/$lng/)
for project in $projects
do
    po_files=$(find $data_root/LibreOffice/$lng/$project -name '*\.po')
    for file in $po_files
    do
	pot_name=${file#*/source/}
	pot_name=${pot_name%.po}
        #echo $project, $pot_name, $file;  continue;  ## debug
	../pot_import.php LibreOffice $project $pot_name $file
    done
done
