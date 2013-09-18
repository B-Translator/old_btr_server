#!/bin/bash
### Make a snapshot of all the projects.

### go to the script directory
cd $(dirname $0)

### get the variable $languages
. ../config.sh

### get a list of all the projects
#base_url='https://fr.btranslator.org'
base_url='https://dev.btranslator.org'
wget --no-check-certificate -O project_list.txt $base_url/translations/project/list

### make a snapshot for each project and for each language
while read line
do
    origin=$(echo $line | cut -d'/' -f1)
    project=$(echo $line | cut -d'/' -f2)
    for lng in $languages
    do
	echo ./make_snapshot.sh $origin $project $lng
	./make_snapshot.sh $origin $project $lng
    done
done < project_list.txt

### clean up
rm project_list.txt

