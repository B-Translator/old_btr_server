#!/bin/bash

### get $data_root and $languages
. ../config.sh

### include function make-snapshot
. make-snapshot.sh

### import the PO files from ubuntu
### using the fr PO file as template (POT)
pot_dir="$data_root/ubuntu/fr/LC_MESSAGES"
for file in $(ls $pot_dir)
do
    ### get the project name
    project=${file%%.po}
    pot_name=$project
    echo -e "\n==========> ubuntu $project $pot_name"
    #continue;  ## debug

    ### import the POT file
    ./pot_import.php ubuntu $project $pot_name $pot_dir/$file

    ### import the PO file of each language
    for lng in $languages
    do
	### get the PO filename
	po_file="$data_root/ubuntu/$lng/LC_MESSAGES/$file"
	if [ ! -f $po_file ]; then continue; fi
	echo -e "\n----------> $po_file";
	#continue;  ## debug

	### import the PO file
	./po_import.php ubuntu $project $pot_name $lng $po_file

	## make initial snapshot
	make-snapshot ubuntu $project $lng $po_file
    done
    #exit 0  ## debug
done
