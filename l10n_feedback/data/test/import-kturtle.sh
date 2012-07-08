#!/bin/bash
### Used for testing.

### go to the script directory
cd $(dirname $0)

### get $data_root
. ../config.sh

### Files that are imported are assumed to be
### under the directory '$data_root/$origin/'.
### The path under $origin does not matter (can
### be any path that suits the project structure).
origin=test
project=kturtle
po_dir="$data_root/$origin/$project"
rm -rf $po_dir/
mkdir -p $po_dir/
cp po_files/kturtle-fr.po $po_dir/ 
cp po_files/kturtle-sq.po $po_dir/ 

### include snapshot functions
. ../import/make-snapshot.sh

### make last snapshots before re-import
make-last-snapshot $origin $project fr
make-last-snapshot $origin $project sq

### import the template
potemplate=kturtle
../import/pot_import.php $origin $project $potemplate $po_dir/kturtle-fr.po

### import the PO files
../import/po_import.php $origin $project $potemplate fr $po_dir/kturtle-fr.po
../import/po_import.php $origin $project $potemplate sq $po_dir/kturtle-sq.po

## make initial snapshots after (re)import
make-snapshot $origin $project fr $po_dir/kturtle-fr.po
make-snapshot $origin $project sq $po_dir/kturtle-sq.po

