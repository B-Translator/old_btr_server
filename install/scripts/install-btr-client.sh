#!/bin/bash

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
