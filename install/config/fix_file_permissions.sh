#!/bin/bash
### drush may create some files with wrong (root) permissions
### fix them (change owner to www-data)

for dir in /var/www/{btr,bcl}*/sites/default/files/*
do
    test -d $dir && chown www-data: -R $dir
done
