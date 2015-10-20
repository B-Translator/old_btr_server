#!/bin/bash

######################################################################################
## How to get all the translations from the Launchpad
######################################################################################
##
## Reference:
## https://wiki.ubuntu.com/Translations/KnowledgeBase/Exporting#Full
## See also: https://wiki.ubuntu.com/UpstreamToKDE
##
## Where to get them:
## https://translations.launchpad.net/ubuntu/trusty/+language-packs
##
## Get the base pack and the latest update:
## wget https://translations.launchpad.net/ubuntu/trusty/+latest-full-language-pack
## wget http://launchpadlibrarian.net/109392762/ubuntu-trusty-translations-update.tar.gz
######################################################################################

echo "===== GETTING UBUNTU ====="
cd $(dirname $0)
. ./inc.sh
change_dir ubuntu

### Get the base pack and the latest update:
release="trusty"
wget https://translations.launchpad.net/ubuntu/$release/+latest-full-language-pack
mv +latest-full-language-pack ubuntu-$release-translations.tar.gz
## Note: Find the URL of the latest update on this page:
##       https://translations.launchpad.net/ubuntu/$release/+language-packs
wget http://launchpadlibrarian.net/221189838/ubuntu-trusty-translations-update.tar.gz

### downloaded language packs
translations="./ubuntu-$release-translations.tar.gz"
translations_update="./ubuntu-$release-translations-update.tar.gz"

### the code of the language to be extracted, like: fr\|de\|en_GB\|sq
langs=$(echo $languages | sed -e 's/ /\\|/g')

### get the names of the files corresponding to the given languages
tar tvfz $translations | grep -e "/\($langs\)/" | gawk '{print $6}' > extract-files.txt

### extract these files from the language pack archives
tar --extract --gunzip --files-from=extract-files.txt --overwrite --file=$translations
tar --extract --gunzip --files-from=extract-files.txt --overwrite --file=$translations_update 2>/dev/null

### after the extraction, there will be directories like:
### rosetta-$release/$lng/LC_MESSAGES
rm -rf $languages
mv rosetta-$release/* .
rmdir rosetta-$release/

### cleanup
rm extract-files.txt
