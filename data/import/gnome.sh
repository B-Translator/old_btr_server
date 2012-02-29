#!/bin/bash

### get $data_root and $languages
. ../config.sh

### include function make-snapshot
. make-snapshot.sh

### get the list of projects to be imported
pot_dir=$data_root/GNOME/fr
if [ $# -gt 0 ]
then
    for project in $@
    do
	pot_files="$pot_files $(ls $pot_dir/$project.*.fr.po)"
    done
else
    pot_files=$(ls $pot_dir/*.fr.po)
fi
#echo $pot_files;  exit;  ## debug

### import the POt/PO files
for pot_file in $pot_files
do
    ### get the project name
    basename=$(basename $pot_file)
    project=${basename%.*.fr.po}
    pot_name=$project
    echo -e "\n==========> GNOME $project"  #; continue;  ## debug

    ### make last snapshots before re-import
    for lng in $languages
    do
	make-last-snapshot GNOME $project $lng
    done

    ### import the POT file
    ./pot_import.php GNOME $project $pot_name $pot_file

    ### import the PO file of each language
    for lng in $languages
    do
	### get the PO filename
	po_file=${basename%.fr.po}.$lng.po
	po_file=$data_root/GNOME/$lng/$po_file
	if [ ! -f $po_file ]; then continue; fi
	echo -e "\n----------> $po_file"  #; continue;  ## debug

	### import the PO file
	./po_import.php GNOME $project $pot_name $lng $po_file
	
	## make an initial snapshot after (re)import
	make-snapshot GNOME $project $lng $po_file
    done

    #exit 0  ## debug
done
