#!/bin/bash

### get $data_root and $languages
. ../config.sh

projects=$(ls $data_root/Mozilla/po/en-GB/)
for project in $projects
do
    pot_files=$(find $data_root/Mozilla/po/en-GB/$project -name '*\.pot')
    for file in $pot_files
    do
	pot_name=${file#*/$project/}
	pot_name=${pot_name%.pot}
        #echo $project, $pot_name, $file;  continue;  ## debug
	./pot_import.php Mozilla $project $pot_name $file
    done
done
