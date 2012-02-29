#!/bin/bash
### Export the current state of translation files of
### a project-language and make a diff with the last snapshot.

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

### export the project
pid=$$
export_dir=tmp_$pid
mkdir -p $export_dir
./export.sh $origin $project $lng $export_dir

### get the last snapshot from DB
snapshot_dir=tmp1_$pid
mkdir -p $snapshot_dir
snapshot_file=$origin-$project-$lng.tgz
./db_snapshot.php get $origin $project $lng $snapshot_file
if [ -f $snapshot_file ]
then
    tar -C $snapshot_dir -xz --file=$snapshot_file
    rm $snapshot_file
fi

### make the unified diff (diff -u) with the previous snapshot
file_diff="$origin-$project-$lng.diff"
echo "diff -rubB $snapshot_dir $export_dir > $file_diff"
diff -rubB $snapshot_dir $export_dir > $file_diff

### make the embedded diff (poediff) with the previous snapshot
pology=pology/bin/poediff
file_ediff="$origin-$project-$lng.ediff"
echo "$pology -n $snapshot_dir $export_dir > $file_ediff"
$pology -n $snapshot_dir $export_dir > $file_ediff

### create a tarball with the latest export
tar -C $export_dir -cz --file=$snapshot_file .

### clean up
rm -rf $snapshot_dir
rm -rf $export_dir

### output the name of the generated files
echo "--> $snapshot_file"
echo "--> $file_diff"
echo "--> $file_ediff"
