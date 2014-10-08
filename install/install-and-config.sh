#!/bin/bash -x

### go to the directory of scripts
cd $code_dir/install/scripts/

### additional packages and software
./packages-and-software.sh

### make and install the drupal profile 'btr_server'
export drupal_dir=/var/www/btr
export drush="drush --root=$drupal_dir"
./drupal-make-and-install.sh

### move translation tables on their own database
./separate-translation-data.sh

### additional configurations related to drupal
./drupal-config.sh

### install btr_client as well
./install-btr-client.sh

### system level configuration (services etc.)
./system-config.sh

### btranslator configuration
$code_dir/install/config.sh
