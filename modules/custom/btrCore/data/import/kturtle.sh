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
project=kdeedu_kturtle
languages="fr sq"

### create the project
rm -f $tmpdir/*
cp $data_root/$origin/fr/messages/kdeedu/*kturtle* $tmpdir/
echo -e "\n==========> $origin $project"
$drush btrp-add $origin $project $tmpdir

### import the PO files of each language
for lng in $languages
do
    echo -e "\n----------> $origin $project $lng"  # ;  continue;  ## debug
    rm -f $tmpdir/*
    cp $data_root/$origin/$lng/messages/kdeedu/*kturtle* $tmpdir/
    $drush btrp-import $origin $project $lng $tmpdir
done

### set the author of Albanian translations
rm -f $tmpdir/*
cp $data_root/$origin/sq/messages/kdeedu/*kturtle* $tmpdir/
$drush btr-vote --user="Dashamir Hoxha" sq $tmpdir/

### cleanup the temp dir
rm -rf $tmpdir/
