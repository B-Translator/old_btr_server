#!/bin/bash

echo "===== GETTING KDE ====="

. ./get.inc.sh
change_dir KDE

#kde_modules=$(svn ls svn://anonsvn.kde.org/home/kde/trunk/l10n-kde4)
for lng in $languages
do
    svn_checkout svn://anonsvn.kde.org/home/kde/trunk/l10n-kde4/$lng $lng
done
