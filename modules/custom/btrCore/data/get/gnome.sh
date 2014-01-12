#!/bin/bash

echo "===== GETTING GNOME ====="

. ./inc.sh
change_dir GNOME

l10n_gnome='https://l10n.gnome.org/languages'
version='gnome-3-10'
for lng in $languages
do
    rm -rf $lng
    mkdir $lng
    cd $lng
    wget $l10n_gnome/$lng/$version/ui.tar.gz
    tar xfz ui.tar.gz
    rm ui.tar.gz
    cd ..
done
