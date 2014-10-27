#!/bin/bash

echo "===== GETTING MISC ====="
cd $(dirname $0)
. ./inc.sh
change_dir misc

svn_checkout svn://svn.d-i.alioth.debian.org/svn/d-i/trunk/packages/po debian-installer
svn_checkout https://inkscape.svn.sourceforge.net/svnroot/inkscape/inkscape/trunk/po inkscape-i18n
#svn_checkout svn://svn.berlios.de/opensuse-i18n/trunk opensuse-i18n
