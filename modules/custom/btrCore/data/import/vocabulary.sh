#!/bin/bash -x
### Import the vocabulary projects.

### go to the script directory
cd $(dirname $0)

### get the drush alias from the first argument
drush_alias=${1:-@btr_dev}
drush="drush $drush_alias"

### create a temporary directory
tmpdir=$(mktemp -d)

origin='vocabulary'
for file in $(ls vocabulary/*.po)
do
    ### get project and lng from the name of the PO file
    filename=$(basename $file)
    project=${filename%.po}
    lng=${project##*_}

    ### copy the PO file to tmpdir
    rm -f $tmpdir/*
    cp $file $tmpdir/

    ### create a project and import translations
    $drush btrp-add $origin $project $tmpdir
    $drush btrp-import $origin $project $lng $tmpdir
done

### cleanup the temp dir
rm -rf $tmpdir/
