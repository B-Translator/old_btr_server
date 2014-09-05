#!/bin/bash
### Import FirefoxOS projects and translations.

### go to the script directory
cd $(dirname $0)

### get config vars
. ../config.sh

### set some variables
origin=FirefoxOS
project=Gaia
po_dir=$data_root/$origin/$project/po

### create the project (using the en-US files as templates)
echo -e "\n==========> $origin $project"
$drush btrp-add $origin $project $po_dir/en-US

### import the PO files of each language
for lng in $languages
do
    echo -e "\n----------> $origin $project $lng"  # ;  continue;  ## debug
    $drush btrp-import $origin $project $lng $po_dir/$lng
done
