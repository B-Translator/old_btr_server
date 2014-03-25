#!/bin/bash
### Make the diff with the last snapshot and store it in DB.
### Save in DB the current snapshot.

### get the parameters
if [ $# -lt 3 ]
then
    echo "
Usage: $0 origin project lng [diff_comment]

Make the diff with the last snapshot and store it in DB.
Save in DB the current snapshot.
"
    exit 1
fi
origin=$1
project=$2
lng=$3
diff_comment=$4
#echo "$origin $project $lng '$diff_comment'";  exit;  # debug

### go to the script directory
cd $(dirname $0)

### make the diff with the last snapshot
output_dir=/tmp
filename="$origin-$project-$lng"
./make_diff.sh $origin $project $lng $output_dir $filename

### files that are created by make_diff.sh
snapshot_file=$output_dir/$filename.tgz
file_diff=$output_dir/$filename.diff
file_ediff=$output_dir/$filename.ediff

### if $file_diff or $file_ediff is not empty
### store them in the DB and save the snapshot as well
if [ -s $file_diff -o -s $file_ediff ]
then
    ./db_diff.php add $origin $project $lng $file_diff $file_ediff "$diff_comment"
    ./db_snapshot.php update $origin $project $lng $snapshot_file
fi

### clean up
rm -f $snapshot_file
rm -f $file_diff
rm -f $file_ediff
