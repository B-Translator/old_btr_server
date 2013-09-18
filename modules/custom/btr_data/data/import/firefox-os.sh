#!/bin/bash

origin=FirefoxOS
project=Gaia
echo -e "\n==========> $origin $project"

### get $data_root and $languages
. ../config.sh

### include function make-snapshot
. make-snapshot.sh

### make last snapshots before re-import
for lng in $languages
do
    make-last-snapshot $origin $project $lng
done

### import the POT files (using the en-US files as templates)
pot_dir=$data_root/$origin/$project/po/en-US
pot_files=$(find $pot_dir -name '*\.pot')
for pot_file in $pot_files
do
    pot_name=${pot_file#*/en-US/}
    pot_name=${pot_name%.pot}
    #echo $origin $project $pot_name $pot_file;  continue;  ## debug
    ./pot_import.php $origin $project $pot_name $pot_file
done

### import the PO files of each language
for lng in $languages
do
    po_dir=$data_root/$origin/$project/po/$lng
    echo -e "\n----------> $origin $project $lng"  # ;  continue;  ## debug

    ### import the PO files
    po_files=$(find $po_dir -name '*\.po')
    for po_file in $po_files
    do
	pot_name=${po_file#*/$lng/}
	pot_name=${pot_name%.po}
	#echo $origin $project $pot_name $lng $po_file;  continue;  ## debug
	./po_import.php $origin $project $pot_name $lng $po_file
    done

    ## make initial snapshots after (re)import
    make-snapshot $origin $project $lng $po_files
done
