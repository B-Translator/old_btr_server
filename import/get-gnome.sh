#!/bin/bash

echo "===== GETTING GNOME ====="

. ./get.inc.sh
change_dir GNOME

gnome_modules=$(wget -o /dev/null -O- http://svn.gnome.org/viewvc/ | grep 'a href="/viewvc/[^"]' | sed 's/.*\/viewvc\/\([^\/]*\)\/.*/\1/')

for module in $gnome_modules
do
    svn_checkout http://svn.gnome.org/svn/$module/trunk/po $module
done
