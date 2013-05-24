#!/bin/bash -ex
###
### Clones the dev branch from B-Translator.
###
### Assumes that B-Translator has already been
### cloned from github into /var/www/B-Translator
### Assumes also that the branch 'dev' is already
### created on /var/www/B-Translator
###
### These assumptions can be satisfied by running
### these commands (manually):
###
###    cd /var/www/
###    git clone git@github.com:dashohoxha/B-Translator.git
###    cd B-Translator/
###    git branch -f dev master
###

### clone the dev branch
cd /var/www/btranslator/profiles/
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
