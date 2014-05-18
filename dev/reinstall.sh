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
cd /var/www/code/btr_server/install/install-scripts/
./20-make-and-install-btrserver.sh
./25-git-clone-btrserver.sh
./30-separate-translation-data.sh
./40-configure-btrserver.sh

./45-install-btrclient.sh

### configure (both /var/www/btr/ and /var/www/bcl/)
cd /var/www/code/btr_server/install/
./config.sh

