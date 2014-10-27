#!/bin/bash

echo "===== GETTING Mozilla ====="
cd $(dirname $0)
. ./inc.sh
change_dir Mozilla

### clone from the mercurial repository
mkdir -p moz/
cd moz/
hg_clone http://hg.mozilla.org/releases/l10n/mozilla-aurora/en-GB en-GB
for lng in $languages
do
    hg_clone http://hg.mozilla.org/releases/l10n/mozilla-aurora/$lng $lng
done
cd ..

### convert to PO format
rm -rf po/
mkdir -p po/
moz2po --pot --template=moz/en-GB --input=moz/en-GB --output=po/en-GB
for lng in $languages
do
    moz2po --template=moz/en-GB --input=moz/$lng --output=po/$lng
done
