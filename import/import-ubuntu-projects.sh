#!/bin/bash

### get $data_root and $languages
. ./config.sh

### import the POT files from ubuntu
lng=fr

dir="$data_root/ubuntu/rosetta-oneiric/$lng/LC_MESSAGES"
for file in $(ls $dir)
do
    project=${file%%.po}
    ./pot_import.php ubuntu $project $dir/$file
done
