#!/bin/bash
### Export the translation files of a given origin/project/lng
### If project==all, then all the projects of the given origin
### will be exported.

### get the parameters
if [ $# -lt 4 ]
then
    echo "Usage: $0 origin project lng output_dir"
    echo ""
    exit 1
fi
origin=$1
project=$2
lng=$3
output_dir=$4
test "$QUIET" = '' && echo $0 $origin $project $lng $output_dir

### go to the script directory
cd $(dirname $0)

### get the DB connection parameters
mysql_params="$($(which php) ../db/get-connection.php bash)"
#echo $mysql_params;  exit;  # debug

### get from the DB the names of the templates and the filenames
sql="SELECT t.tplname, f.filename FROM l10n_suggestions_files f
     LEFT JOIN l10n_suggestions_templates t ON (f.potid = t.potid)
     LEFT JOIN l10n_suggestions_projects p ON (t.pguid = p.pguid)
     WHERE p.origin = '$origin' AND p.project = '$project' AND f.lng = '$lng'"
#echo $sql | mysql $mysql_params --skip-column-names | sed -e 's/\t/,/g' ;  exit;  # debug
result_rows=$(echo $sql | mysql $mysql_params --skip-column-names | sed -e 's/\t/,/g')

### export all the PO files of the project
for row in $result_rows
do
    tplname=$(echo $row | cut -d, -f1)
    filename=$(echo $row | cut -d, -f2)
    #echo $origin, $project, $tplname, $filename;  continue;  # debug
    po_file=$output_dir/$origin/$filename
    mkdir -p $(dirname $po_file)
    test "$QUIET" = '' &&  echo ./po_export.php $origin $project $tplname $lng $po_file
    ./po_export.php $origin $project $tplname $lng $po_file
done
