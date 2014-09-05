#!/bin/bash -x
### Import the vocabulary projects.

### go to the script directory
cd $(dirname $0)

### get the drush alias from the first argument
drush_alias=${1:-@btr_dev}
drush="drush $drush_alias"

origin='vocabulary'
for file in $(ls vocabulary/*.po)
do
    ### get project and lng from the name of the PO file
    filename=$(basename $file)
    project=${filename%.po}
    lng=${project##*_}

    ### create a project and import translations
    $drush btrp-add $origin $project $(pwd)/$file
    $drush btrp-import $origin $project $lng $(pwd)/$file
done
