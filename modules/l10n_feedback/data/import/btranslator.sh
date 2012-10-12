#!/bin/bash

### go to the script directory
cd $(dirname $0)

origin=Drupal
project1=btranslator
project2=l10n_feedback

drupal_dir=$(drush dd)
btranslator_pot=$drupal_dir/profiles/btranslator/l10n/btranslator.pot
l10n_feedback_pot=$drupal_dir/profiles/btranslator/modules/l10n_feedback/l10n/l10n_feedback.pot

lng=sq
btranslator_po=$drupal_dir/profiles/btranslator/l10n/btranslator.$lng.po
l10n_feedback_po=$drupal_dir/profiles/btranslator/modules/l10n_feedback/l10n/l10n_feedback.$lng.po

### include snapshot functions
. make-snapshot.sh

### make last snapshots before re-import
make-last-snapshot $origin $project1 $lng
make-last-snapshot $origin $project2 $lng

### import the templates
potpl1=$project1
potpl2=$project2
./pot_import.php $origin $project1 $potpl1 $btranslator_pot
./pot_import.php $origin $project2 $potpl2 $l10n_feedback_pot

### import the PO files
./po_import.php $origin $project1 $potpl1 $lng $btranslator_po
./po_import.php $origin $project2 $potpl2 $lng $l10n_feedback_po

## make initial snapshots after (re)import
make-snapshot $origin $project1 $lng $btranslator_po
make-snapshot $origin $project2 $lng $l10n_feedback_po

