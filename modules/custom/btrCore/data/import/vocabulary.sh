#!/bin/bash -x
### Import the vocabulary projects.

### go to the script directory
cd $(dirname $0)

### get $languages
source ../config.sh

### set drush site
drush="drush $1"

### create a vocabulary for each language
for lng in $languages
do
    if test $($drush btrv-ls --name=ICT_$lng) ; then continue ; fi

    echo "Creating vocabulary ICT_$lng."
    $drush btrv-add ICT $lng
done
