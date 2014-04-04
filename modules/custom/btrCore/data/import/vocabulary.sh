#!/bin/bash
### import the vocabulary projects

cd $(dirname $0)

origin='vocabulary'
for file in $(ls vocabulary/*.po)
do
    filename=$(basename $file)
    project=${filename%.po}
    potname=$project
    lng=${project##*_}

    ./pot_import.php $origin $project $potname $file
    ./po_import.php $origin $project $potname $lng $file
done

