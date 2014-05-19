#!/bin/bash

export drupal_dir=/var/www/bcl
export drush="drush --root=$drupal_dir"

### run install scripts of btr_client
cd $code_dir/btr_client/install/scripts/
./20-make-and-install.sh
./30-git-clone.sh
./40-configure.sh
