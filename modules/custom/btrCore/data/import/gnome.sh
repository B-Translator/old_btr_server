#!/bin/bash
### Import GNOME projects and translations.

### go to the script directory
cd $(dirname $0)

### get config vars
. ../config.sh

### get the list of projects to be imported
pot_dir=$data_root/GNOME/fr
if [ $# -gt 0 ]
then
    for project in $@
    do
	pot_files="$pot_files $(ls $pot_dir/$project.*.fr.po)"
    done
else
    pot_files=$(ls $pot_dir/*.fr.po)
fi
#echo $pot_files;  exit;  ## debug

### create a temporary directory
tmpdir=$(mktemp -d)

### import the POT/PO files
origin=GNOME
for pot_file in $pot_files
do
    ### get the project name
    basename=$(basename $pot_file)
    project=${basename%.*.fr.po}
    echo -e "\n==========> $origin $project"  #; continue;  ## debug

    ### import the POT file
    rm -f $tmpdir/*
    cp $pot_file $tmpdir/$project.po
    $drush btrp-add $origin $project $tmpdir

    ### import the PO file of each language
    for lng in $languages
    do
	### get the PO filename
	po_file=${basename%.fr.po}.$lng.po
	po_file=$data_root/GNOME/$lng/$po_file
	if [ ! -f $po_file ]; then continue; fi
	echo -e "\n----------> $po_file"  #; continue;  ## debug

	### import the PO file
	rm -f $tmpdir/*
	cp $po_file $tmpdir/$project.po
	$drush btrp-import $origin $project $lng $tmpdir
    done

    #exit 0  ## debug
done

### cleanup the temp dir
rm -rf $tmpdir/
