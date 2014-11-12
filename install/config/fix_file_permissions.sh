#!/bin/bash
### drush may create some css/js files with wrong permissions
### fix them

for dir in /var/www/{btr,bcl}*/sites/default/files/{css,js}
do
    chroot www-data: -R $dir
done
