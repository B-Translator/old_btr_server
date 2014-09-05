#!/bin/bash -x
### Import B-Translator translations.

### go to the script directory
cd $(dirname $0)

### get the drush alias from the first argument
drush_alias=${1:-@btr_dev}

### set some variables
drush="drush $drush_alias"
drupal_dir=$($drush dd)
l10n_dir=$drupal_dir/profiles/btr_server/l10n
origin=Drupal
project=btranslator

### create a temporary directory
tmpdir=$(mktemp -d)

### import the POT file
cp $l10n_dir/btrserver.pot $tmpdir/
$drush btrp-add $origin $project $tmpdir

### import the PO file of each language
languages="sq"
for lng in $languages
do
    rm -f $tmpdir/*
    cp $l10n_dir/btrserver.$lng.po $tmpdir/btrserver.po
    $drush btrp-import $origin $project $lng $tmpdir
done

### cleanup the temp dir
rm -rf $tmpdir/
