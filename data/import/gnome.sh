#!/bin/bash

### get $data_root and $languages
. ../config.sh

### include function make-snapshot
. make-snapshot.sh

### import the PO files from GNOME
### using the fr PO file as template (POT)
for pot_file in $(ls $data_root/GNOME/fr/*.fr.po)
do
    ### get the project name
    basename=$(basename $pot_file)
    project=${basename%.*.fr.po}
    pot_name=$project
    echo -e "\n==========> GNOME $project $pot_name"
    #continue;  ## debug

    ### import the POT file
    ./pot_import.php GNOME $project $pot_name $pot_file

    ### import the PO file of each language
    for lng in $languages
    do
	### get the PO filename
	po_file=${basename%.fr.po}.$lng.po
	po_file=$data_root/GNOME/$lng/$po_file
	if [ ! -f $po_file ]; then continue; fi
	echo -e "\n----------> $po_file";
	#continue;  ## debug

	### import the PO file
	./po_import.php GNOME $project $pot_name $lng $po_file
	
	## make an initial snapshot
	make-snapshot GNOME $project $lng $po_file
    done
    #exit 0  ## debug
done
