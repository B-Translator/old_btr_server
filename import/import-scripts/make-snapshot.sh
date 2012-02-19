### Generate snapshots for a project that is imported.
### The first (initial) snapshot contains the original
### files that are imported, and it will not generate
### a diff. The second snapshot contains the export of
### the original files, and it will produce and store
### the first diff.


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

    ### store the tgz file into the DB
    ../snapshot.php init $origin $project $lng $snapshot_tgz
    rm $snapshot_tgz  ## clean up

    ## make a second snapshot (which will generate and save a diff)
    export PO_EXPORT_MODE=original   ## set the export mode for po_export.php
    ../export-scripts/snapshot.sh $origin $project $lng
}