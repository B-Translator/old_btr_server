#!/bin/bash

### go to the script directory
cd $(dirname $0)

### set drush root
drush="drush --root=/var/www/btr"

### set some variables
origin=test
project=kdeadmin
path=$(pwd)/po_files

### create the project
$drush btrp-add $origin $project $path/kdeadmin-fr/

### import the PO files of each language
for lng in fr sq
do
    $drush btrp-import $origin $project $lng $path/kdeadmin-$lng/
done
