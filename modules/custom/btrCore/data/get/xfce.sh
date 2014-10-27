#!/bin/bash

echo "===== GETTING XFCE ====="
cd $(dirname $0)
. ./inc.sh
change_dir xfce

xfce_modules=$(wget -o /dev/null -O- http://git.xfce.org | grep 'sublevel-repo[^~]*$' | sed "s/^.*href='\([^']*\)'.*$/\1/")
for module in $xfce_modules
do
    dir=$(echo $module | sed 's/.*\/\(.*\)\/$/\1/')
    git_clone git://git.xfce.org$module $dir
done
