#/bin/bash
### Extract translatable strings of B-Translator
### and update the file 'btranslator.pot'.
###
### Run it on a copy of B-Translator that is just
### cloned from git, don't run it on an installed
### copy of B-Translator, otherwise 'potx-cli.php'
### will scan also the other modules that are on
### the directory 'modules/'. 

### go to the btranslator directory
cd $(dirname $0)
cd ..

### extract translatable strings
utils/potx-cli.php

### concatenate files 'general.pot' and 'installer.pot' into 'btranslator.pot'
msgcat --output-file=btranslator.pot general.pot installer.pot
rm -f general.pot installer.pot
mv -f btranslator.pot l10n/

### merge/update with previous translations
for po_file in $(ls l10n/btranslator.*.po)
do
    msgmerge --update --previous $po_file l10n/btranslator.pot
done

