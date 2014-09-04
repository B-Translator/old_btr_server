#!/bin/bash -x
### The PO files of Pingus are synchronized with Launchpad:
### https://translations.launchpad.net/pingus/trunk/+pots/pingus/fr/+translate
### https://translations.launchpad.net/pingus/trunk/+pots/pingus/sq/+translate

### go to the script directory
cd $(dirname $0)

### get the drush alias from the first argument
drush_alias=${1:-@btr_dev}

### set some variables
drush="drush $drush_alias"
origin=misc
project=pingus
path=$(pwd)/pingus

### create the project
$drush btrp-add $origin $project $path/fr

### import the PO files of each language
for lng in $(ls $path)
do
    $drush btrp-import $origin $project $lng $path/$lng
done
