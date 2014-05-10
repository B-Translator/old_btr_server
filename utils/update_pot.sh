#/bin/bash
### Extract translatable strings of B-Translator Server and update the
### file 'btrserver.pot'.
###
### Run it on a copy of B-Translator Server that is just cloned from
### git, don't run it on an installed copy of B-Translator, otherwise
### 'potx-cli.php' will scan also the other modules that are on the
### directory 'modules/'.

### go to the btr_server directory
cd $(dirname $0)
cd ..

### extract translatable strings
utils/potx-cli.php

### concatenate files 'general.pot' and 'installer.pot' into 'btrserver.pot'
msgcat --output-file=btrserver.pot general.pot installer.pot
rm -f general.pot installer.pot
mv -f btrserver.pot l10n/

### merge/update with previous translations
for po_file in $(ls l10n/btrserver.*.po)
do
    msgmerge --update --previous $po_file l10n/btrserver.pot
done

