#!/bin/bash
### Make the diff with the last snapshot and store it in DB.
### Save in DB the current snapshot.

### get the parameters
if [ $# -lt 3 ]
then
    echo "Usage: $0 origin project lng"
    echo ""
    exit 1
fi
origin=$1
project=$2
lng=$3
#echo $origin $project $lng;  exit;  # debug

### go to the script directory
cd $(dirname $0)

### make the diff with the last snapshot
./diff.sh $origin $project $lng

### files that are created by diff.sh
snapshot_file="$origin-$project-$lng.tgz"
file_diff="$origin-$project-$lng.diff"
file_ediff="$origin-$project-$lng.ediff"

### if $file_diff or $file_ediff is not empty
### store them in the DB and save the snapshot as well
if [ -s $file_diff -o -s $file_ediff ]
then
    ../po_diff.php add $origin $project $lng $file_diff $file_ediff
    ../snapshot.php update $origin $project $lng $snapshot_file
fi

### clean up
rm $snapshot_file
rm $file_diff
rm $file_ediff
