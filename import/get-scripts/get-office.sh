#!/bin/bash

echo "===== GETTING LibreOffice ====="

. ./get.inc.sh
change_dir LibreOffice

### download all translations
translations_url="http://download.documentfoundation.org/libreoffice/src/3.4.5/libreoffice-translations-3.4.5.2.tar.bz2"
wget $translations_url

### the code of the language to be extracted, like: fr\|de\|en_GB\|sq
langs=$(echo $languages | sed -e 's/ /\\|/g')

### get the names of the files corresponding to the given languages
translations=$(basename $translations_url)
tar tvfj $translations | grep -e "/\($langs\)/" | gawk '{print $6}' > extract-files.txt

### extract these files from the translations archive
tar --extract --bzip2 --files-from=extract-files.txt --overwrite --file=$translations
mv libreoffice-translations-*/translations/source/* .
rm -rf libreoffice-translations-*/

### cleanup
rm extract-files.txt
