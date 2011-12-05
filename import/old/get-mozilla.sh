#!/bin/bash

data_root="$1"
mozilla_root="$data_root/comm-central"
mozilla_l10n="$data_root/mozilla-l10n"
mozilla_po="$data_root/mozilla-po"

cd $data_root

if [ ! -d $mozilla_root ]; then
    hg clone http://hg.mozilla.org/comm-central/
fi
cd $mozilla_root
python client.py checkout

cd $mozilla_l10n
for lang in `cat $mozilla_root/mozilla/browser/locales/all-locales`; do
    if [ ! -d $mozilla_l10n/$lang ]; then
	hg clone http://hg.mozilla.org/releases/l10n-mozilla-1.9.1/$lang
    else
	hg pull $lang
    fi
done

if [ ! -d $mozilla_po ]; then
    mkdir $mozilla_po
fi

rm -rf $mozilla_l10n/en-US
rm -rf $mozilla_po/*
mkdir $mozilla_l10n/en-US

moz_copy () {
    last=`basename $1`
    cp -r $mozilla_root/$1/locales/en-US $mozilla_l10n/en-US/$last
}

moz_copy2 () {
    last=`basename $1`
    if [ -z "$2" ]; then
	target=$1
    else
	target=$2
    fi
    first=`dirname $target`
    if [ ! -d $mozilla_l10n/en-US/$first ]; then
	mkdir $mozilla_l10n/en-US/$first
    fi
    cp -r $mozilla_root/$1/locales/en-US $mozilla_l10n/en-US/$target
}

set -e

moz_copy mozilla/browser
moz_copy calendar
moz_copy2 editor/ui
moz_copy mozilla/dom
moz_copy2 mozilla/extensions/irc extensions/irc
moz_copy2 mozilla/extensions/reporter extensions/reporter
moz_copy2 mozilla/extensions/venkman extensions/venkman
moz_copy mail
moz_copy mozilla/netwerk
moz_copy2 mozilla/security/manager security/manager
moz_copy suite
moz_copy mozilla/toolkit

cd $mozilla_l10n
for d in *; do
    if [ "$d" == "en-US" ]; then
	continue
    fi
    cd $data_root
    echo -n "$d..."
    moz2po --progress none -t "$mozilla_l10n/en-US" "$mozilla_l10n/$d" "$mozilla_po/$d" > /dev/null
    echo "done."
done
