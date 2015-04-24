#!/bin/bash
### drush may create some css/js files with wrong permissions
### fix them

for dir in /var/www/{btr,bcl}*/sites/default/files/{css,js}
do
    test -d $dir && chown www-data: -R $dir
done
exit 0  # it is ok even if something above failed
