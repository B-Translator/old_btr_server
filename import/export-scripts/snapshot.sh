#!/bin/bash
### Export the current state of translation files of a project-language
### Make also the diff with the last snapshot and store it in DB.

### get the parameters
if [ $# -lt 3 ]
then
    echo "Usage: $0 origin project lng [original]"
    echo ""
    exit 1
fi
origin=$1
project=$2
lng=$3
algorithm=$4
#echo $origin $project $lng;  exit;  # debug

### go to the script directory
cd $(dirname $0)

### export the project
pid=$$
export_dir=tmp_$pid
mkdir -p $export_dir
./export.sh $origin $project $lng $export_dir $algorithm

### get the project path
case $origin in
    'KDE' )
	project_path=KDE/$lng/messages/$project
	;;
    'GNOME' )
	project_path=GNOME/$lng/$project.master.$lng.po
	;;
    'ubuntu' )
	project_path=ubuntu/$lng/LC_MESSAGES/$project.po
	;;
    'LibreOffice' )
	project_path=LibreOffice/$lng/$project
	;;
    'Mozilla' )
	project_path=Mozilla/po/$lng/$project
	;;
esac

### get the last snapshot from DB
snapshot_dir=tmp1_$pid
mkdir -p $snapshot_dir
snapshot_file=$origin-$project-$lng.tgz
../snapshot.php get $origin $project $lng $snapshot_file
tar -C $snapshot_dir -xz --file=$snapshot_file

### make the difference with the previous snapshot
pology=pology/bin/poediff
fname_ediff="$origin-$project-$lng.ediff"
snapshot_path=$snapshot_dir/$project_path
export_path=$export_dir/$project_path
echo $pology -n -o $fname_ediff $snapshot_path $export_path
$pology -n -o $fname_ediff $snapshot_path $export_path

### store the difference in the DB
../po_diff.php add $origin $project $lng $fname_ediff

### replace the previous snapshot with the latest export
rm $snapshot_file
tar -C $export_dir -cz --file=$snapshot_file .
../snapshot.php update $origin $project $lng $snapshot_file

### clean up
rm $fname_ediff
rm $snapshot_file
rm -rf $snapshot_dir
rm -rf $export_dir
