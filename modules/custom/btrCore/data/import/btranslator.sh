#!/bin/bash

### go to the script directory
cd $(dirname $0)

origin=Drupal
project=btranslator
lng=sq

#drupal_dir=$(drush dd)
drupal_dir=/var/www/btr
btrserver_pot=$drupal_dir/profiles/btr_server/l10n/btrserver.pot
btrserver_po=$drupal_dir/profiles/btr_server/l10n/btrserver.$lng.po

### include snapshot functions
. make-snapshot.sh

### make last snapshots before re-import
make-last-snapshot $origin $project $lng

### import the templates
potpl=$project
./pot_import.php $origin $project $potpl $btrserver_pot

### import the PO files
./po_import.php $origin $project $potpl $lng $btrserver_po

## make initial snapshots after (re)import
make-snapshot $origin $project $lng $btrserver_po

