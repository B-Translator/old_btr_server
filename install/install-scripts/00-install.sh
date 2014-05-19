#!/bin/bash -x

export DEBIAN_FRONTEND=noninteractive

export drupal_dir=/var/www/btr
export drush="drush --root=$drupal_dir"

cd $code_dir/btr_server/install/install-scripts/

./10-install-additional-packages.sh
./20-make-and-install-btrserver.sh
./25-git-clone-btrserver.sh
./30-separate-translation-data.sh
./40-configure-btrserver.sh

### install btr_client as well
./45-install-btrclient.sh

### copy overlay files over to the system
cp -TdR ../overlay/ /

./50-misc-config.sh
