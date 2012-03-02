
### Generate snapshots for a project that is imported.
### The first (initial) snapshot contains the original
### files that are imported, and it will not generate
### a diff. The second snapshot contains the export of
### the original files, and it will produce and store
### the first diff. This initial diff actually contains
### the differences that come as a result of formating
### changes between the original format and the exported
### format. It also contains the entries that are skipped
### during the import.

### suppress some of the log/debug messages
### which by default are displayed
export QUIET=true

function make-last-snapshot()
{
    ### get the parameters
    origin=$1
    project=$2
    lng=$3

    ### make a last snapshot before the import (useful in the case of re-import)
    export PO_EXPORT_MODE='most_voted'   ## set the export mode for po_export.php
    diff_comment="Contains the latest suggestions before import."
    ../export/make_snapshot.sh $origin $project $lng "$diff_comment"
}

function make-snapshot()
{
    ### get the parameters
    origin=$1 ;  shift
    project=$1 ;  shift
    lng=$1 ;  shift
    po_files=$@

    ### remove '$data_root/' from the path of the files
    po_files_relative=$(echo $po_files | sed -e "s,^$data_root/,,g" -e "s, $data_root/, ,g")

    ### make a tgz archive of the PO files
    snapshot_tgz=$origin-$project-$lng.tgz
    tar -C $data_root/ -cz --file=$snapshot_tgz $po_files_relative

    ### store the tgz file into the DB as a snapshot
    ../export/db_snapshot.php init $origin $project $lng $snapshot_tgz
    rm $snapshot_tgz  ## clean up

    ### make a second snapshot, which will generate a diff
    ### with the initial snapshot, and will save it into the DB
    export PO_EXPORT_MODE='original'   ## set the export mode for po_export.php
    diff_comment="Import diff. Contains formating changes, any skiped entries, etc."
    ../export/make_snapshot.sh $origin $project $lng "$diff_comment"

    ### make another snapshot, which will contain all the previous suggestions
    ### (before the import), in a single diff
    export PO_EXPORT_MODE='most_voted'   ## set the export mode for po_export.php
    diff_comment="Initial diff after import. Contains all the previous suggestions (before the last import)."
    ../export/make_snapshot.sh $origin $project $lng "$diff_comment"
}