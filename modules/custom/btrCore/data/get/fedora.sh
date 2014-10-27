#!/bin/bash

echo "===== GETTING FEDORA ====="
cd $(dirname $0)
. ./inc.sh
change_dir fedora

# This is a dummy run that should make wget avoid a refresh
wget -o /dev/null -O /dev/null http://git.fedorahosted.org/git/?a=project_index

fedora_modules=$(wget -o /dev/null -O- http://git.fedorahosted.org/git/?a=project_index | sed 's/ .*//')
for module in $fedora_modules
do
    git_clone git://git.fedorahosted.org/$module $module
done
