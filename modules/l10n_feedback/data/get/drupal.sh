#!/bin/bash

echo "===== GETTING Drupal ====="

. ./inc.sh
change_dir Drupal

### get the directory of the downloaded PO files
#drupal_dir=$(drush drupal-directory)
#l10n_store=$(drush variable-get l10n_update_download_store | cut -d' ' -f2)
#l10n_store=${l10n_store//\"/}
#po_dir=$drupal_dir/$l10n_store
po_dir=/var/www/btranslator/sites/all/translations

### get the latest translations
drush --yes l10n-update

### copy PO files
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
