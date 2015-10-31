#!/bin/bash
## Import Drupal projects and translations.

### go to the script directory
cd $(dirname $0)

### get config vars
. ../config.sh

### set some variables
origin=Drupal
po_dir=$data_root/Drupal

### import POT files
pot_files=$(find $po_dir -name "*\.fr\.po")
for pot_file in $pot_files
do
    filename=$(basename $pot_file)
    project=${filename%%-*.fr.po}
    $drush btrp-add $origin $project $pot_file
done

### import PO files of each language
for lng in $languages
do
    po_files=$(find $po_dir -name "*\.$lng\.po")
    for po_file in $po_files
    do
        filename=$(basename $po_file)
        project=${filename%%-*.$lng.po}
        echo -e "\n----------> $origin $project $lng "  # ;  continue;  ## debug
        $drush btrp-import $origin $project $lng $po_file
    done
done
