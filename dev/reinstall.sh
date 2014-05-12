#!/bin/bash
### Reinstall btr_server from scratch.
### Useful for testing installation scripts.

### Reinstall btr_server.

export drupal_dir=/var/www/btr
export drush="drush --root=$drupal_dir"

mv $drupal_dir $drupal_dir-bak

cd $(dirname $0)
cd ../install/install-scripts/

./20-make-and-install-btrserver.sh
./25-git-clone-btrserver.sh
./30-separate-translation-data.sh
./40-configure-btrserver.sh

### Reinstall btr_client.

export drupal_dir=/var/www/bcl
export drush="drush --root=$drupal_dir"

mv $drupal_dir $drupal_dir-bak

cd /var/www/bcl_dev/install/install-scripts/
./20-make-and-install.sh
./30-git-clone.sh
./40-configure.sh

### Configure (both /var/www/btr/ and /var/www/bcl/).
../config.sh

