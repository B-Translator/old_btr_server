#!/bin/bash
### Export the translation files of a given origin/project/lng
### as a tgz archive. Output the path of the created archive.
### If project==all, then all the projects of the given origin
### will be exported.

### get the parameters
if [ $# -lt 3 ]
then
    echo "Usage: $0 origin project lng [output_dir]"
    echo ""
    exit 1
fi
origin=$1
project=$2
lng=$3
output_dir=${4:-/tmp}
#echo $origin $project $lng $output_dir;  exit;  # debug

### go to the script directory
cd $(dirname $0)

### get the DB connection parameters
mysql="$(drush sql-connect)"
#echo $mysql;  exit;  # debug

### get the list of the projects to be exported
if [ "$project" != 'all' ]
then
    project_list=$project
else
    sql="SELECT project FROM l10n_feedback_projects WHERE origin = '$origin'"
    project_list=$(echo $sql | $mysql --skip-column-names)
fi

### export the PO files of all the projects in project_list
pid=$$
export_dir=$output_dir/$pid
for proj in $project_list
do
    ./export.sh $origin $proj $lng $export_dir
done

### create the tgz archive on the output dir
tgz_file=$output_dir/$origin-$project-$lng.tgz
tar -C $export_dir --create --gzip --file=$tgz_file $origin

### clean up
rm -rf $export_dir

### output the path/name of the tgz file
echo $tgz_file
