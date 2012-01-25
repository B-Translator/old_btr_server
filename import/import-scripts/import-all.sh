#!/bin/bash

### go to this directory
cd $(dirname $0)

### import all PO files
./import-gnome-templates.sh
./import-gnome-files.sh
./import-kde-templates.sh
./import-kde-files.sh
./import-ubuntu-templates.sh
./import-ubuntu-files.sh
