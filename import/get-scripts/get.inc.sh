#!/bin/bash

### get $data_root and $languages
. ../config.sh

function change_dir() {
    dir="$1"
    path="$data_root/$dir"
    if [ ! -d $path ]; then
	mkdir -p $path
    fi
    cd $path
}

function svn_checkout() {
    svn_url="$1"
    dir="$2"

    if test -d $dir
    then
	cd $dir

	echo -n "-- svn cleanup $dir... "
	svn cleanup > /dev/null || true
	echo "done."

	echo -n "-- svn update $dir... "
	svn update > /dev/null || true
	echo "done."

	cd ..
    else
	echo -n "-- svn checkout $dir... "
	svn checkout $svn_url $dir > /dev/null || true
	echo "done."
    fi
}

function git_clone() {
    git_url="$1"
    dir="$2"

    if test -d $dir
    then
	cd $dir
	echo -n "-- git pull $dir... "
	git pull > /dev/null || true
	echo "done."
	cd ..
    else
	echo -n "-- git clone $dir... "
	git clone $git_url $dir > /dev/null || true
	echo "done."
    fi
}

function hg_clone() {
    hg_url="$1"
    dir="$2"

    if test -d $dir
    then
	cd $dir
	echo -n "-- hg pull $dir... "
	hg pull -u > /dev/null || true
	echo "done."
	cd ..
    else
	echo -n "-- hg clone $dir... "
	hg clone $hg_url $dir > /dev/null || true
	echo "done."
    fi
}
