#!/bin/bash
### drush may create some css/js files with wrong permissions
### fix them

for dir in /var/www/{btr,bcl}*/sites/default/files/{css,js}
do
    chown www-data: -R $dir
done
