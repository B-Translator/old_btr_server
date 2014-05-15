#!/bin/bash -x

export DEBIAN_FRONTEND=noninteractive

export drupal_dir=/var/www/btr
export drush="drush --root=$drupal_dir"

cwd=$(dirname $0)

### get config settings from etc/config.sh
set -a
.  $(dirname $cwd)/etc/config.sh
set +a

$cwd/10-install-additional-packages.sh
$cwd/20-make-and-install-btrserver.sh
$cwd/25-git-clone-btrserver.sh
$cwd/30-separate-translation-data.sh
$cwd/40-configure-btrserver.sh

### install btr_client as well
$cwd/45-install-btrclient.sh

### copy overlay files over to the system
cp -TdR $(dirname $cwd)/overlay/ /

$cwd/50-misc-config.sh
