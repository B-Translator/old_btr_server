#!/bin/bash

### make sure that we have the code of btr_client
if ! test -d /usr/local/src/btr_client
then
    cd /usr/local/src/
    git clone --branch=$bcl_git_branch https://github.com/B-Translator/btr_client
fi

### export drupal_dir
export drupal_dir=/var/www/bcl
export drush="drush --root=$drupal_dir"

### go to the directory of scripts
export code_dir=/usr/local/src/btr_client
cd $code_dir/install/scripts/

### make and install the drupal profile 'btr_client'
./drupal-make-and-install.sh

### additional configurations related to drupal
./drupal-config.sh

### change back $code_dir to btr_server
export code_dir=/usr/local/src/btr_server
