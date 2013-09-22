#!/bin/bash
### Reinstall btranslator from scratch.
### Useful for testing installation scripts.

export drupal_dir=/var/www/btr
export drush="drush --root=$drupal_dir"

mv $drupal_dir $drupal_dir-bak

cd $(dirname $0)
cd ../install/install-scripts/

./20-make-and-install-btranslator.sh
./25-git-clone-btranslator.sh
./30-separate-translation-data.sh
./40-configure-btranslator.sh

../config.sh

