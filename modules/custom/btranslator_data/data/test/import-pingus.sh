#!/bin/bash
### The PO files of Pingus are synchronized with Launchpad:
### https://translations.launchpad.net/pingus/trunk/+pots/pingus/fr/+translate
### https://translations.launchpad.net/pingus/trunk/+pots/pingus/sq/+translate

### go to the script directory
cd $(dirname $0)

### get $data_root
. ../config.sh

### Files that are imported are assumed to be
### under the directory '$data_root/$origin/'.
### The path under $origin does not matter (can
### be any path that suits the project structure).
origin=test
project=pingus
po_dir="$data_root/$origin/$project"
rm -rf $po_dir/
mkdir -p $po_dir/
cp po_files/pingus-fr.po $po_dir/ 
cp po_files/pingus-sq.po $po_dir/ 

### include snapshot functions
. ../import/make-snapshot.sh

### make last snapshots before re-import
make-last-snapshot $origin $project fr
make-last-snapshot $origin $project sq

### import the template
potemplate=pingus
../import/pot_import.php $origin $project $potemplate $po_dir/pingus-fr.po

### import the PO files
../import/po_import.php $origin $project $potemplate fr $po_dir/pingus-fr.po
../import/po_import.php $origin $project $potemplate sq $po_dir/pingus-sq.po

## make initial snapshots after (re)import
make-snapshot $origin $project fr $po_dir/pingus-fr.po
make-snapshot $origin $project sq $po_dir/pingus-sq.po

