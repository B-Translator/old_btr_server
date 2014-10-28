#!/bin/bash -x
### Import B-Translator translations.

### go to the script directory
cd $(dirname $0)

### get config vars
. ../config.sh

### import the POT files
code_dir='/usr/local/src'
$drush btrp-add Drupal btr_server $code_dir/btr_server/l10n/btrserver.pot
$drush btrp-add Drupal btr_client $code_dir/btr_client/l10n/btrclient.pot

### import the PO file of each language
for lng in $languages
do
    $drush btrp-import Drupal btr_server $lng $code_dir/btr_server/l10n/btrserver.$lng.po
    $drush btrp-import Drupal btr_client $lng $code_dir/btr_client/l10n/btrclient.$lng.po
done
