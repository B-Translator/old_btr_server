#!/bin/bash 
### Import the vocabulary projects.

### go to the script directory
cd $(dirname $0)

### set drush site
drush="drush $1"

for file in $(ls vocabulary/*_*.po)
do
    ### get vocabulary and lng from the name of the PO file
    filename=$(basename $file)
    name=${filename%.po}
    lng=${name##*_}
    vocabulary=${name%_*}

    if test $($drush btrv-ls --name=$name)
    then
        echo "Vocabulary $name already exists; skipping."
        continue
    fi

    echo "Importing $name."
    ### create a vocabulary and import translations
    $drush btrv-add $vocabulary $lng $(pwd)/$file
    #$drush btr-vote-import --user=dasho $lng $(pwd)/$file
done
