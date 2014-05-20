#!/bin/bash

### export drupal_dir
export drupal_dir=/var/www/bcl
export drush="drush --root=$drupal_dir"

### go to the directory of scripts
cd $code_dir/btr_client/install/scripts/

### make and install the drupal profile 'btr_client'
./drupal-make-and-install.sh

### additional configurations related to drupal
./drupal-config.sh
