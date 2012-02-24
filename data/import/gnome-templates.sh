#!/bin/bash

### get $data_root and $languages
. ../config.sh

### use the fr PO files as POT files
lng=fr

for file in $(ls $data_root/GNOME/$lng/*.$lng.po)
do
    basename=$(basename $file)
    project=${basename%.*.$lng.po}
    pot_name=$project
    #echo $file;  echo $project;  continue;  ## debug
    ./pot_import.php GNOME $project $pot_name $file
done
