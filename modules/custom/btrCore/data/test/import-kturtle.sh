#!/bin/bash -x

### go to the script directory
cd $(dirname $0)

### set drush alias
drush_alias=${1:-@btr}
drush="drush $drush_alias"

### set some variables
origin=test
project=kturtle
path=$(pwd)/po_files

### create the project
$drush btrp-add $origin $project $path/kturtle-fr.po

### import the PO files of each language
for lng in fr sq
do
    $drush btrp-import $origin $project $lng $path/kturtle-$lng.po
done
