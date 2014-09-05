#!/bin/bash
### Import ubuntu projects and translations.

### go to the script directory
cd $(dirname $0)

### get config vars
. ../config.sh

### get the list of projects to be imported
pot_dir="$data_root/ubuntu/fr/LC_MESSAGES"
if [ $# -gt 0 ]
then
    projects="$@"
else
    projects=$(ls $pot_dir/ | grep '.po' | sed -e 's/\.po$//')
fi
#echo $projects;  exit;  ## debug

### create a temporary directory
tmpdir=$(mktemp -d)

### import the POT/PO files
origin=ubuntu
for project in $projects
do
    echo -e "\n==========> ubuntu $project"  #; continue;  ## debug
    pot_file="$pot_dir/$project.po"
    if [ ! -f $pot_file ]
    then
	echo "Error: template '$pot_file' not found."
	continue;
    fi

    ### import the POT file
    rm -f $tmpdir/*
    cp $pot_file $tmpdir/
    $drush btrp-add $origin $project $tmpdir

    ### import the PO file of each language
    for lng in $languages
    do
	### get the PO filename
	po_file="$data_root/ubuntu/$lng/LC_MESSAGES/$project.po"
	if [ ! -f $po_file ]; then continue; fi
	echo -e "\n----------> $po_file"  #; continue;  ## debug

	### import the PO file
	rm -f $tmpdir/*
	cp $po_file $tmpdir/
	$drush btrp-import $origin $project $lng $tmpdir
    done

    #exit 0  ## debug
done

### cleanup the temp dir
rm -rf $tmpdir/