#!/bin/bash
### Export the current state of translation files of
### a project-language and make a diff with the last snapshot.
### If project==all, then all the projects of the given origin
### will be exported and compared with the corresponding snapshots.

### get the parameters
if [ $# -lt 3 ]
then
    echo "
Usage: $0 origin project lng [output_dir [filename]]

Export the current state of translation files of a project-language
and make a diff with the last snapshot.
If project==all, then all the projects of the given origin
will be exported and compared with the corresponding snapshots.

"
    exit 1
fi
origin=$1
project=$2
lng=$3
output_dir=${4:-/tmp}
filename=${5:-"$origin-$project-$lng"}
#echo $0 $origin $project $lng $output_dir $filename;  exit;  # debug

### go to the script directory
cd $(dirname $0)

### get the list of the projects to be exported
if [ "$project" != 'all' ]
then
    project_list=$project
else
    dbname=${BTR_DATA:-btr_data}
    connect=$(php ../db/sql-connect.php)
    mysql="mysql $connect -B --skip-column-names"
    sql="SELECT project FROM btr_projects WHERE origin = '$origin'"
    project_list=$($mysql -D $dbname -e "$sql")
fi

### export the PO files of all the projects in project_list
pid=$$
export_dir=$output_dir/${pid}_export
for proj in $project_list
do
    ./export.sh $origin $proj $lng $export_dir
done

### get the last snapshots from DB
snapshot_dir=$output_dir/${pid}_snapshot
mkdir -p $snapshot_dir
for proj in $project_list
do
    snapshot_file=$output_dir/${pid}_${proj}.tgz
    test "$QUIET" = '' && echo "./db_snapshot.php get $origin $proj $lng $snapshot_file"
    ./db_snapshot.php get $origin $proj $lng $snapshot_file
    if [ -f $snapshot_file ]
    then
	tar -C $snapshot_dir -xz --file=$snapshot_file
	rm $snapshot_file
    fi
done

### if directory $snapshot_dir is not empty
if test "$(ls -A "$snapshot_dir" 2>/dev/null)"
then
    ### make the unified diff (diff -u) with the previous snapshot
    file_diff=$output_dir/$filename.diff
    test "$QUIET" = '' && echo "diff -rubB $snapshot_dir $export_dir > $file_diff"
    diff -rubB $snapshot_dir $export_dir > $file_diff

    ### make the embedded diff (poediff) with the previous snapshot
    pology=pology/bin/poediff
    file_ediff=$output_dir/$filename.ediff
    test "$QUIET" = '' && echo "$pology -n $snapshot_dir $export_dir > $file_ediff"
    $pology -n $snapshot_dir $export_dir > $file_ediff
fi

### if directory $export_dir is not empty
if test "$(ls -A "$export_dir" 2>/dev/null)"
then
    ### create a tarball with the latest export
    export_file=$output_dir/$filename.tgz
    tar -C $export_dir -cz --file=$export_file .
fi

### clean up
rm -rf $snapshot_dir
rm -rf $export_dir

### output the name of the generated files
if [ "$QUIET" = '' ]
then
    echo "--> $export_file"
    echo "--> $file_diff"
    echo "--> $file_ediff"
fi
