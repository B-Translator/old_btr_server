#!/bin/bash -x
### Replace the profile btranslator with a version
### that is cloned from github, so that any updates
### can be retrieved easily (without having to
### reinstall the whole application).

### clone btranslator from github
cd /var/www/btr/profiles/
mv btranslator btranslator-bak
git clone https://github.com/dashohoxha/B-Translator btranslator

### copy contrib libraries and modules
cp -a btranslator-bak/libraries/ btranslator/
cp -a btranslator-bak/modules/contrib/ btranslator/modules/
cp -a btranslator-bak/modules/libraries/ btranslator/modules/
cp -a btranslator-bak/themes/contrib/ btranslator/themes/

### copy db connection file
cp {btranslator-bak,btranslator}/modules/custom/btr_data/data/db/settings.php

### cleanup
rm -rf btranslator-bak/