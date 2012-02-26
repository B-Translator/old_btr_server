#!/bin/bash

### get $data_root and $languages
. ../config.sh

### include function make-snapshot
. make-snapshot.sh

### import the PO files, using the fr PO file as template (POT)
pot_dir=$data_root/KDE/fr/messages
for project in $(ls $pot_dir)
do
    echo -e "\n==========> KDE $project"  # ;  continue;  ## debug

    ### import the POT files
    pot_files=$(find $pot_dir/$project -name '*\.po')
    for pot_file in $pot_files
    do
	pot_name=${pot_file#*/$project/}
	pot_name=${pot_name%.po}
        #echo KDE $project $pot_name $pot_file;  continue;  ## debug
	./pot_import.php KDE $project $pot_name $pot_file
    done

    ### import the PO files of each language
    for lng in $languages
    do
	po_dir=$data_root/KDE/$lng/messages/$project
	if [ ! -d $po_dir ]; then continue; fi
	echo -e "\n----------> KDE $project $lng"  # ;  continue;  ## debug

	### import the PO files
	po_files=$(find $po_dir -name '*\.po')
	for po_file in $po_files
	do
	    pot_name=${po_file#*/$project/}
	    pot_name=${pot_name%.po}
            #echo KDE $project $pot_name $lng $po_file;  continue;  ## debug
	    ./po_import.php KDE $project $pot_name $lng $po_file
	done

	## make initial snapshot
	make-snapshot KDE $project $lng $po_files
    done

    #exit 0  ## debug
done
