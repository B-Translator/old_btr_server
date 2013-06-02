#!/bin/bash
### Clone the dev branch from
### /var/www/btranslator_dev/profiles/btranslator/

### create a symlink /var/www/B-Translator to the git repo
cd /var/www/
test -h B-Translator || ln -s btranslator_dev/profiles/btranslator/ B-Translator

### on the repo create a 'dev' branch
cd B-Translator/
git branch dev master

### clone the dev branch
cd /var/www/btranslator/profiles/
rm -rf btranslator-bak
mv btranslator btranslator-bak
git clone -b dev /var/www/B-Translator btranslator

### copy contrib libraries and modules
cp -a btranslator-bak/libraries/ btranslator/
cp -a btranslator-bak/modules/contrib/ btranslator/modules/
cp -a btranslator-bak/modules/libraries/ btranslator/modules/
cp -a btranslator-bak/themes/contrib/ btranslator/themes/

### copy db connection file
cp {btranslator-bak,btranslator}/modules/l10n_feedback/data/db/settings.php

### fix the links to PO_files
PO_files=/var/www/PO_files
data=/var/www/btranslator_data
ln -sf $PO_files $data/get/
ln -sf $PO_files $data/import/
