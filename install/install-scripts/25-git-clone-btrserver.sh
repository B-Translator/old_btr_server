#!/bin/bash -x
### Replace the profile btr_server with a version
### that is cloned from github, so that any updates
### can be retrieved easily (without having to
### reinstall the whole application).

### clone btr_server from github
cd $drupal_dir/profiles/
mv btr_server btr_server-bak
git clone https://github.com/B-Translator/btr_server.git

### copy contrib libraries and modules
cp -a btr_server-bak/libraries/ btr_server/
cp -a btr_server-bak/modules/contrib/ btr_server/modules/
cp -a btr_server-bak/themes/contrib/ btr_server/themes/

### copy db connection file
cp {btr_server-bak,btr_server}/modules/custom/btrCore/data/db/settings.php

### cleanup
rm -rf btr_server-bak/