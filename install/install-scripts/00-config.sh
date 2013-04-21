#!/bin/bash -x

export DEBIAN_FRONTEND=noninteractive

cwd=$(dirname $0)

$cwd/10-install-additional-packages.sh

$cwd/20-make-and-install-btranslator.sh

$cwd/25-git-clone-btranslator.sh

$cwd/30-separate-translation-data.sh

$cwd/40-configure-btranslator.sh

### copy overlay files over to the system
cp -TdR $(dirname $cwd)/overlay/ /

$cwd/50-misc-config.sh
