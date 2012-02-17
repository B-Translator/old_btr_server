#!/bin/bash

### get $data_root and $languages
. ../config.sh

### import the POT files from ubuntu
lng=fr

dir="$data_root/ubuntu/$lng/LC_MESSAGES"
for file in $(ls $dir)
do
    project=${file%%.po}
    pot_name=$project
    ../pot_import.php ubuntu $project $pot_name $dir/$file
done
