#!/bin/bash
### Clone the dev branch from
### /var/www/btr_dev/profiles/btr_server/

### create a symlink /var/www/dev_btr_server to the git repo
cd /var/www/
test -h dev_btr_server || ln -s btr_dev/profiles/btr_server/ dev_btr_server

### on the repo create a 'dev' branch
cd dev_btr_server/
git branch dev master

### clone the dev branch
cd /var/www/btr/profiles/
rm -rf btr_server-bak
mv btr_server btr_server-bak
git clone -b dev /var/www/dev_btr_server

### copy contrib libraries and modules
cp -a btr_server-bak/libraries/ btr_server/
cp -a btr_server-bak/modules/contrib/ btr_server/modules/
cp -a btr_server-bak/modules/libraries/ btr_server/modules/
cp -a btr_server-bak/themes/contrib/ btr_server/themes/

### copy db connection file
cp {btr_server-bak,btr_server}/modules/custom/btrCore/data/db/settings.php
