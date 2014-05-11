#!/bin/bash -x

### get a copy of 'btr_server' to /var/www/github/btr_server/
mkdir -p /var/www/github/
cd /var/www/github/
test -d btr_server || git clone https://github.com/B-Translator/btr_server.git
cd btr_server/
git pull

### make a clone of /var/www/btr to /var/www/btr_dev
dev/clone.sh btr dev

### comment out the configuration of the database 'btr_db' so that
### the internal test database can be used instead for translations
sed -i /var/www/btr_dev/sites/default/settings.php \
    -e '/$databases..btr_db/,+8 s#^/*#//#'