#!/bin/bash 
### Import the vocabulary projects.

### go to the script directory
cd $(dirname $0)

### set drush site
drush="drush $1"

origin='vocabulary'
for file in $(ls vocabulary/*.po)
do
    ### get project and lng from the name of the PO file
    filename=$(basename $file)
    project=${filename%.po}
    lng=${project##*_}

    if test $($drush btrp-ls --origin=$origin --project=$project)
    then
        echo "Project $origin/$project already exists; skipping."
        continue
    fi

    echo "Importing $origin/$project."
    ### create a project and import translations
    $drush btrp-add $origin $project $(pwd)/$file
    $drush btrp-import $origin $project $lng $(pwd)/$file
done
