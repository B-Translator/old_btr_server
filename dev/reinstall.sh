#!/bin/bash
### Reinstall btr and bcl from scratch.
### Useful for testing installation scripts.

### get config settings from a file
if [ "$1" = '' ]
then
    echo "Usage: $0 settings.sh"
    exit 1
fi
settings=$1
set -a ;   source  $settings ;   set +a

### backup existing dirs
rm -rf /var/www/btr-bak
mv /var/www/{btr,btr-bak}
rm -rf /var/www/bcl-bak
mv /var/www/{bcl,bcl-bak}

### reinstall
export drupal_dir=/var/www/btr
export drush="drush --root=$drupal_dir"
export code_dir=/usr/local/src/btr_server
cd $code_dir/install/scripts/
./drupal-make-and-install.sh
./separate-translation-data.sh
./drupal-config.sh

### install btr_client as well
./install-btr-client.sh

### btranslator configuration
$code_dir/install/config.sh

### restart mysql
/etc/init.d/mysql restart
