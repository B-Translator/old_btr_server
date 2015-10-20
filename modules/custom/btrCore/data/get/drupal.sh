#!/bin/bash

echo "===== GETTING Drupal ====="
cd $(dirname $0)
. ./inc.sh
change_dir Drupal

### get the directory of the downloaded PO files
#drupal_dir=$(drush drupal-directory)
#l10n_store=$(drush variable-get l10n_update_download_store | cut -d' ' -f2)
#l10n_store=${l10n_store//\"/}
#po_dir=$drupal_dir/$l10n_store

### get the latest translations
drush @btr --yes l10n-update-refresh
drush @btr --yes l10n-update
drush @bcl --yes l10n-update-refresh
drush @bcl --yes l10n-update

### copy PO files
po_dir=/var/www/btr/sites/all/translations
echo "Getting PO files from $po_dir ..."
cp $po_dir/*.po .
po_dir=/var/www/bcl/sites/all/translations
echo "Getting PO files from $po_dir ..."
cp $po_dir/*.po .

### PO files of Drupal have no empty lines between the entries
### and POParses.php sometimes fails to parse them correctly
### so they need to be converted to starndard PO format
echo "Converting PO files to standard format..."
for file in $(ls *.po)
do
  msgcat $file > $file.1
  mv $file.1 $file
done
