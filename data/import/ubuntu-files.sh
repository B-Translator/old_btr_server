#!/bin/bash

### get $data_root and $languages
. ../config.sh

### include function make-snapshot
. make-snapshot.sh

### import the PO files from ubuntu
for lng in $languages
do
    dir="$data_root/ubuntu/$lng/LC_MESSAGES"
    for file in $(ls $dir)
    do
	project=${file%%.po}
	pot_name=$project
	./po_import.php ubuntu $project $pot_name $lng $dir/$file

	## make initial snapshots
	make-snapshot ubuntu $project $lng $dir/$file
    done
done
