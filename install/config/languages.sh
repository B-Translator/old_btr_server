#!/bin/bash

### read $main_lang
echo "
===> Main translation language of B-Translator

This is the code of the main translation language
of your site (something like 'sq' or 'sq_AL').
"
main_lang='sq'
read -p "Enter the language code [$main_lang]: " input
main_lang=${input:-$main_lang}

### read $other_langs
echo "
===> Auxiliary languages of B-Translator

These are the codes of helping (auxiliary) languages,
separated by space (like 'fr de it').
"
other_langs='fr'
read -p "Enter the language codes [$other_langs]: " input
other_langs=${input:-$other_langs}

### set the list of languages for import
languages="$main_lang $other_langs"
sed -i /var/www/btranslator_data/config.sh \
    -e "/^languages=/c languages=\"$languages\""

### set drupal variable l10n_feedback_translation_lng
$(dirname $0)/mysqld.sh start
drush --yes --exact vset l10n_feedback_translation_lng $main_lang

### modify the list of languages
file_inc='/var/www/btranslator/profiles/btranslator/modules/l10n_feedback/includes/common.inc'
echo "
===> Edit the file '$file_inc' and modify the list of languages appropriately.
"
read -p "Press Enter to continue..." input
nano --syntax=php +20,5 $file_inc
