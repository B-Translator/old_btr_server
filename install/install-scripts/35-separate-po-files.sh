#!/bin/bash -ex
### Move the directory of the PO files
### to /var/www/ and put links to it.

PO_files=/var/www/PO_files
data=/var/www/btranslator_data

rm -rf $PO_files
mv $data/PO_files $PO_files

ln -sf $PO_files $data/get/
ln -sf $PO_files $data/import/
