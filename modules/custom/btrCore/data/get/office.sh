#!/bin/bash

echo "===== GETTING LibreOffice ====="

. ./inc.sh
change_dir LibreOffice

### download all translations
### find the propper url on this page:
### http://download.documentfoundation.org/libreoffice/src/
translations_url="http://download.documentfoundation.org/libreoffice/src/4.2.0/libreoffice-translations-4.2.0.1.tar.xz"
wget $translations_url

### the code of the language to be extracted, like: fr\|de\|en_GB\|sq
langs=$(echo $languages | sed -e 's/ /\\|/g')

### get the names of the files corresponding to the given languages
translations=$(basename $translations_url)
tar -tvJf $translations | grep -e "/\($langs\)/" | gawk '{print $6}' > extract-files.txt

### extract these files from the translations archive
rm -rf $languages
tar --extract --xz --files-from=extract-files.txt --overwrite --file=$translations
mv libreoffice-*/translations/source/* .
rm -rf libreoffice-translations-*/

### cleanup
rm extract-files.txt
