#!/bin/bash
### Import the translations of the documentation of kdeedu/kturtle.

### go to the script directory
cd $(dirname $0)

### create a temporary directory
tmpdir=$(mktemp -d)

### get config vars
. ../config.sh

### set some variables
origin=KDE
project=doc_kdeedu_kturtle
languages="fr sq"

### create the project
rm -f $tmpdir/*
cp $data_root/$origin/fr/docmessages/kdeedu/kturtle* $tmpdir/
echo -e "\n==========> $origin $project"
$drush btrp-add $origin $project $tmpdir

### import the PO files of each language
for lng in $languages
do
    echo -e "\n----------> $origin $project $lng"  # ;  continue;  ## debug
    rm -f $tmpdir/*
    cp $data_root/$origin/$lng/docmessages/kdeedu/kturtle* $tmpdir/
    $drush btrp-import $origin $project $lng $tmpdir
done

### cleanup the temp dir
rm -rf $tmpdir/
