#!/bin/bash

### get $data_root and $languages
. ./config.sh

### import the PO files from ubuntu
for lng in $languages
do
    dir="$data_root/ubuntu/rosetta-oneiric/$lng/LC_MESSAGES"
    for file in $(ls $dir)
    do
	project=${file%%.po}
	./po_import.php $project $lng ubuntu $dir/$file
    done
done
