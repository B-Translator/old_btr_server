#!/bin/bash

### read $languages
echo "
===> Languages supported by B-Translator Server

Do not remove 'fr', because sometimes French translations
are used instead of template files (when they are missing).
"
if [ -z "${languages+xxx}" -o "$languages" = '' ]
then
    languages='fr'
    read -p "Enter language codes [$languages]: " input
    languages=${input:-$languages}
fi

### set the list of languages for import
sed -i /var/www/data/config.sh \
    -e "/^languages=/c languages=\"$languages\""

### add these languages to drupal and import their translations
for lng in $languages
do
    drush @btr language-add $lng
done
drush @btr --yes l10n-update
