#!/bin/bash
### The PO files of Pingus are synchronized with Launchpad:
### https://translations.launchpad.net/pingus/trunk/+pots/pingus/fr/+translate
### https://translations.launchpad.net/pingus/trunk/+pots/pingus/sq/+translate

### go to the script directory
cd $(dirname $0)

### import the template
../pot_import.php ubuntu pingus pingus ~/pingus-fr.po

### import the PO files
../po_import.php ubuntu pingus pingus fr ~/pingus-fr.po
../po_import.php ubuntu pingus pingus sq ~/pingus-sq.po

## make initial snapshots
. make-snapshot.sh
make-snapshot ubuntu pingus fr ~/pingus-fr.po
make-snapshot ubuntu pingus sq ~/pingus-sq.po

