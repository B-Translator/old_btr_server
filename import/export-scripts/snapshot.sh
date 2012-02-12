#!/bin/bash
### Export the current state of translation files of a project-language
### Make also the diff with the last snapshot and store it in DB.

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
./export.sh $origin $project $lng $export_dir

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

if [ -d snapshot/$project_path -o -f snapshot/$project_path ]
then
    ### make the difference with the previous snapshot
    pology=pology/bin/poediff
    fname_ediff="$origin-$project-$lng.ediff"
    snapshot_path=snapshot/$project_path
    export_path=$export_dir/$project_path
    $pology -o $fname_ediff $snapshot_path $export_path

    ### store the difference in the DB
    ../po_diff.php $origin $project $lng $fname_ediff
fi

### replace the previous snapshot with the latest one
rm -rf snapshot/$project_path
mv -a $export_dir/$project_path snapshot/
