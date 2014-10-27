#!/bin/bash

echo "===== GETTING FirefoxOS ====="
cd $(dirname $0)
. ./inc.sh
change_dir FirefoxOS/Gaia

### clone from the mercurial repository
mkdir -p moz/
cd moz/
hg_clone http://hg.mozilla.org/gaia-l10n/en-US en-US
for lng in $languages
do
    hg_clone http://hg.mozilla.org/gaia-l10n/$lng $lng
done
cd ..

### convert to PO format
rm -rf po/
mkdir -p po/
moz2po --pot --template=moz/en-US --input=moz/en-US --output=po/en-US
for lng in $languages
do
    moz2po --template=moz/en-US --input=moz/$lng --output=po/$lng
done
