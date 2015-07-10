#!/bin/bash -x
### Synchronize LibreOffice translations.

pootle=https://translations.documentfoundation.org
lng=sq
project=libo_ui
subproj=${1:-sw}
name=$lng-$project-$subproj

set -e
cd /tmp/

### download from pootle and unzip
rm -rf $name.zip $name/
wget -O $name.zip $pootle/export/?path=/$lng/$project/$subproj/
unzip $name.zip

### import to b-translator
drush @btr btr-project-delete --origin=sync --project=$name --purge --erase
drush @btr btr-project-add     sync $name       $(pwd)/$name/
drush @btr btr-project-import  sync $name $lng  $(pwd)/$name/
drush @btr btr-vote-import  --user=indrit $lng  $(pwd)/$name/

### export from b-translator (with preferencies)
rm -rf $name.zip $name/
drush @btr btr-project-export  sync $name $lng  $(pwd)/$name/ \
    --export-mode=preferred --preferred-voters="indrit,Belinda,Dashamir Hoxha"
drush @btr btr-project-delete --origin=sync --project=$name --purge --erase
zip -r $name.zip $name/
rm -rf $name/

### upload to pootle
rm -f /var/www/downloads/$name.zip
mv $(pwd)/$name.zip  /var/www/downloads/
set +x
echo 
echo "There is no automatic upload yet."
echo
echo "Upload manually 'https://btranslator.org/downloads/$name.zip'"
echo "to '$pootle/$lng/$project/$subproj/'"
echo
