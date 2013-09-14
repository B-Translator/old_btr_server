#!/bin/bash
### Import the translations of the documentation of kdeedu/kturtle.

### go to the script directory
cd $(dirname $0)

### get $data_root
. ../config.sh

### include snapshot functions
. make-snapshot.sh

origin=KDE
project=doc_kdeedu_kturtle
languages="fr sq"

### make last snapshots before re-import
for lng in $languages
do
    make-last-snapshot $origin $project $lng
done

### import the templates
pot_files=$(ls $data_root/$origin/fr/docmessages/kdeedu/kturtle*)
for pot_file in $pot_files
do
    pot_name=${pot_file#*/fr/}
    pot_name=${pot_name%.po}
    ./pot_import.php $origin $project $pot_name $pot_file
done

### import the PO files of each language
for lng in $languages
do
    po_files=$(ls $data_root/$origin/$lng/docmessages/kdeedu/kturtle*)
    for po_file in $po_files
    do
	pot_name=${po_file#*/$lng/}
	pot_name=${pot_name%.po}
	#echo $origin $project $pot_name $lng $po_file;  continue;  ## debug
	./po_import.php $origin $project $pot_name $lng $po_file
    done

    ## make initial snapshot after (re)import
    make-snapshot $origin $project $lng $po_files
done

