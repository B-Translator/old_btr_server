#!/bin/bash

### go to this directory
cd $(dirname $0)

### import all PO files
#./import-ubuntu-projects.sh
#./import-ubuntu-files.sh
./import-gnome-projects.sh
./import-gnome-files.sh
./import-kde-projects.sh
./import-kde-files.sh
