#!/bin/bash
## Import Drupal projects and translations.

### go to the script directory
cd $(dirname $0)

### get config vars
. ../config.sh

### create a temporary directory
tmpdir=$(mktemp -d)

### set some variables
origin=Drupal
po_dir=$data_root/Drupal

languages="sq" ### for the time being import only the Albanian translations
for lng in $languages
do
    echo -e "\n==========> $origin $lng "

    po_files=$(find $po_dir -name "*\.$lng\.po")
    for po_file in $po_files
    do
	filename=$(basename $po_file)
	project=${filename%%-*.$lng.po}
	echo -e "\n----------> $origin $project $lng "  # ;  continue;  ## debug

	### import the template and the translation files
	rm -f $tmpdir/*
	cp $po_file $tmpdir/$project.po
        $drush btrp-add $origin $project $tmpdir
	$drush btrp-import $origin $project $lng $tmpdir
    done
done

### cleanup the temp dir
rm -rf $tmpdir/
