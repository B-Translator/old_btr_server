#!/bin/bash -ex
### Replace the profile btranslator with a version
### that is cloned from github, so that any updates
### can be retrieved easily (without having to
### reinstall the whole application).

### clone btranslator from github
cd /var/www/btranslator/profiles/
mv btranslator btranslator-bak
git clone https://github.com/dashohoxha/B-Translator btranslator

### copy contrib libraries and modules
cp -a btranslator-bak/libraries/ btranslator/
cp -a btranslator-bak/modules/contrib/ btranslator/modules/
cp -a btranslator-bak/modules/libraries/ btranslator/modules/
cp -a btranslator-bak/themes/contrib/ btranslator/themes/

### copy db connection files
cp {btranslator-bak,btranslator}/modules/l10n_feedback/data/db/settings.php
cp {btranslator-bak,btranslator}/modules/l10n_feedback/data/db/sql-connect.txt

### cleanup
rm -rf btranslator-bak/