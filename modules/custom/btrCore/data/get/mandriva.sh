#!/bin/bash

echo "===== GETTING MANDRIVA ====="
cd $(dirname $0)
. ./inc.sh
change_dir mandriva

### get a list of .po files for our languages
svn_url=http://svn.mandriva.com/svn/soft
svn ls -R $svn_url > svn_mandriva.txt
langs=$(echo $languages | sed -e 's/ /\\|/g')
cat svn_mandriva.txt | grep -e "\($langs\)\.po" > svn_mandriva_po.txt

### export them from the svn repository
while read file
do
  dir=$(dirname $file)
  mkdir -p $dir
  svn export $svn_url/$file $file
done < svn_mandriva_po.txt svn_mandriva_po.txt

### cleanup
rm svn_mandriva.txt
