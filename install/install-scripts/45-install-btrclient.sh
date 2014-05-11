#!/bin/bash

export drupal_dir=/var/www/bcl
export drush="drush --root=$drupal_dir"

### get a copy of 'btr_client' from github
mkdir -p /var/www/github/
cd /var/www/github/
git clone https://github.com/B-Translator/btr_client.git

### run install scripts of btr_client
cd btr_client/install/install-scripts/
./20-make-and-install.sh
./30-git-clone.sh
./40-configure.sh


