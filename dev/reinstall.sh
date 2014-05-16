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
set -a
source  $settings
set +a

### Reinstall btr_client.

export drupal_dir=/var/www/btr
export drush="drush --root=$drupal_dir"

rm -rf $drupal_dir-bak
mv $drupal_dir $drupal_dir-bak

cd /var/www/github/btr_server/install/install-scripts/
./20-make-and-install-btrserver.sh
./25-git-clone-btrserver.sh
./30-separate-translation-data.sh
./40-configure-btrserver.sh

### Reinstall btr_client.

export drupal_dir=/var/www/bcl
export drush="drush --root=$drupal_dir"

rm -rf $drupal_dir-bak
mv $drupal_dir $drupal_dir-bak

cd /var/www/github/btr_client/install/install-scripts/
./20-make-and-install.sh
./30-git-clone.sh
./40-configure.sh

### Configure (both /var/www/btr/ and /var/www/bcl/).
cd /var/www/github/btr_server/install/
./config.sh

