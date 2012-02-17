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
## https://translations.launchpad.net/ubuntu/natty/+language-packs
##
## Get the base pack and the latest update:
## wget http://launchpadlibrarian.net/70194188/ubuntu-natty-translations.tar.gz
## wget http://launchpadlibrarian.net/71172166/ubuntu-natty-translations-update.tar.gz
######################################################################################

echo "===== GETTING UBUNTU ====="

. ./get.inc.sh
change_dir ubuntu

### Get the base pack and the latest update:
#wget http://launchpadlibrarian.net/70194188/ubuntu-oneiric-translations.tar.gz
#wget http://launchpadlibrarian.net/71172166/ubuntu-oneiric-translations-update.tar.gz


### downloaded language packs
translations="./ubuntu-oneiric-translations.tar.gz"
translations_update="./ubuntu-oneiric-translations-update.tar.gz"

### the code of the language to be extracted, like: fr\|de\|en_GB\|sq
langs=$(echo $languages | sed -e 's/ /\\|/g')

### get the names of the files corresponding to the given languages
tar tvfz $translations | grep -e "/\($langs\)/" | gawk '{print $6}' > extract-files.txt

### extract these files from the language pack archives
tar --extract --gunzip --files-from=extract-files.txt --overwrite --file=$translations
tar --extract --gunzip --files-from=extract-files.txt --overwrite --file=$translations_update 2>/dev/null

### after the extraction, there will be directories like:
### rosseta-oneiric/$lng/LC_MESSAGES
mv rosseta-oneiric/* .
rmdir rosseta-oneiric/

### cleanup
rm extract-files.txt