#!/bin/bash

### get $data_root and $languages
. ../config.sh

### Files that are imported are assumed to be
### under the directory '$data_root/$origin/'.
### The path under $origin does not matter (can
### be any path that suits the project structure).
origin=test
project=kdeedu
po_dir="$data_root/$origin/$project"
rm -rf $po_dir/
mkdir -p $po_dir/
cp -a po_files/kdeedu-fr $po_dir/fr 
cp -a po_files/kdeedu-sq $po_dir/sq

### include function make-snapshot
. ../import/make-snapshot.sh

### make last snapshots before re-import
make-last-snapshot $origin $project fr
make-last-snapshot $origin $project sq

### import the POT files
pot_files=$(find $po_dir/fr -name '*\.po')
for pot_file in $pot_files
do
    pot_name=${pot_file#*/fr/}
    pot_name=${pot_name%.po}
    #echo $origin $project $pot_name $pot_file;  continue;  ## debug
    ../import/pot_import.php $origin $project $pot_name $pot_file
done

### import the PO files of each language
for lng in fr sq
do
    if [ ! -d $po_dir/$lng ]; then continue; fi

    ### import the PO files
    po_files=$(find $po_dir/$lng -name '*\.po')
    for po_file in $po_files
    do
	pot_name=${po_file#*/$lng/}
	pot_name=${pot_name%.po}
	#echo $origin $project $pot_name $lng $po_file;  continue;  ## debug
	../import/po_import.php $origin $project $pot_name $lng $po_file
    done

    ## make initial snapshot after (re)import
    make-snapshot $origin $project $lng $po_files
done
