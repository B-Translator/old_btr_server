#!/bin/bash
### importing translation files of Drupal

### get $data_root and $languages
. ../config.sh

### include function make-snapshot
. make-snapshot.sh

languages="sq" ### for the time being import only the Albanian translations
origin=Drupal
po_dir=$data_root/Drupal

for lng in $languages
do
    echo -e "\n==========> $origin $lng "

    po_files=$(find $po_dir -name "*\.$lng\.po")
    for po_file in $po_files
    do
	filename=$(basename $po_file)
	project=${filename%%-*.$lng.po}
	echo -e "\n----------> $origin $project $lng "  # ;  continue;  ## debug

        ### make last snapshots before re-import
        make-last-snapshot $origin $project $lng

	### import the template and the translation files
	pot_name=$project
	pot_file=$po_file
	#echo import $origin $project $pot_name $lng $po_file;  continue;  ## debug
	./pot_import.php $origin $project $pot_name $pot_file
	./po_import.php $origin $project $pot_name $lng $po_file

        ## make initial snapshot after (re)import
	make-snapshot $origin $project $lng $po_file
    done
done
