#!/bin/bash

### go to this directory
cd $(dirname $0)

./gnome.sh
./kde.sh
./firefox-os.sh
./drupal.sh       # install languages on Drupal first
./office.sh       # needs to be fixed manually
./mozilla.sh      # needs to be fixed manually
./wordpress.sh    # needs to be fixed manually
./ubuntu.sh       # needs to be fixed manually
#./misc.sh        # deprecated
#./mandriva.sh    # deprecated
#./fedora.sh      # deprecated
#./xfce.sh        # deprecated

