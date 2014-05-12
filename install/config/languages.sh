#!/bin/bash

### read $default_lang
echo "
===> Default translation language of B-Translator Server

The code of the default language (like 'fr' or 'fr_FR').
"
default_lang='fr'
read -p "Enter the language code [$default_lang]: " input
default_lang=${input:-$default_lang}

### read $other_langs
echo "
===> Other languages of B-Translator Server

The codes of the other languages supported by the server,
separated by a space (like 'fr de it').
"
other_langs='fr'
read -p "Enter the language codes [$other_langs]: " input
other_langs=${input:-$other_langs}

### set the list of languages for import
languages="$default_lang $other_langs"
sed -i /var/www/data/config.sh \
    -e "/^languages=/c languages=\"$languages\""

### set drupal variable btr_translation_lng
$(dirname $0)/mysqld.sh start
drush @btr --yes --exact vset btr_translation_lng $default_lang

### modify the list of languages
file_inc='/var/www/btr/profiles/btr_server/modules/custom/btrCore/includes/languages.inc'
echo "
===> Edit the file '$file_inc' and modify the list of languages appropriately.
"
read -p "Press Enter to continue..." input
nano --syntax=php +23,5 $file_inc

### add the Drupal translations of each language
for lng in $languages
do
    drush @btr language-add $lng
done
drush @btr --yes l10n-update
