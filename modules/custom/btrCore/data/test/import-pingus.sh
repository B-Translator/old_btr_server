#!/bin/bash -x

### go to the script directory
cd $(dirname $0)

### set drush root
drush="drush --root=/var/www/btr"

### set some variables
origin=test
project=pingus
path=$(pwd)/po_files

### create the project
$drush btrp-add $origin $project $path/pingus-fr.po

### import the PO files of each language
for lng in fr sq
do
    $drush btrp-import $origin $project $lng $path/pingus-$lng.po
done
