#!/bin/bash
### Import the translations of https://github.com/B-Translator/vocabulary-jquery

### go to the script directory
cd $(dirname $0)

### get config vars
. ../config.sh

### get the po files
rm -rf $data_root/vocabulary-jquery/
git clone https://github.com/B-Translator/vocabulary-jquery $data_root/vocabulary-jquery/

### set some variables
origin=dashohoxha
project=v.btranslator.org

### create the project and import the PO files of each language
echo -e "\n==========> $origin $project"
drush @btr btrp-add $origin $project $data_root/vocabulary-jquery/l10n/app.pot
drush @btr btrp-import $origin $project sq $data_root/vocabulary-jquery/l10n/po/sq.po
drush @btr btrp-import $origin $project de $data_root/vocabulary-jquery/l10n/po/de.po
drush @btr btrp-import $origin $project es $data_root/vocabulary-jquery/l10n/po/es.po

### set the author of translations
drush @btr btr-vote --user="Dashamir Hoxha" sq $data_root/vocabulary-jquery/l10n/po/sq.po
drush @btr btr-vote --user="OpenSrcKansas"  de $data_root/vocabulary-jquery/l10n/po/de.po
drush @btr btr-vote --user="jrosgiralt"     es $data_root/vocabulary-jquery/l10n/po/es.po
