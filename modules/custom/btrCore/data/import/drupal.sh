#!/bin/bash
## Import Drupal projects and translations.

### go to the script directory
cd $(dirname $0)

### get config vars
. ../config.sh

### set some variables
origin=Drupal
po_dir=$data_root/Drupal

### import PO files of each language
for lng in $languages
do
    echo -e "\n==========> $origin $lng "
    po_files=$(find $po_dir -name "*\.$lng\.po")
    for po_file in $po_files
    do
        filename=$(basename $po_file)
        project=${filename%%-*.$lng.po}
        echo -e "\n----------> $origin $project $lng "  # ;  continue;  ## debug
        ### import the template and the translation files
        $drush btrp-add $origin $project $po_file
        $drush btrp-import $origin $project $lng $po_file
    done
done
