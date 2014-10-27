#!/bin/bash

echo "===== GETTING KDE ====="
cd $(dirname $0)
. ./inc.sh
change_dir KDE

#kde_modules=$(svn ls svn://anonsvn.kde.org/home/kde/trunk/l10n-kf5)
for lng in $languages
do
    svn_checkout svn://anonsvn.kde.org/home/kde/trunk/l10n-kf5/$lng $lng
done
