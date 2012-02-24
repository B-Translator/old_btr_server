#!/bin/bash

### go to this directory
cd $(dirname $0)

### import all PO files
./gnome-templates.sh
./gnome-files.sh
./mozilla-templates.sh
./mozilla-files.sh
./ubuntu-templates.sh
./ubuntu-files.sh
./office-templates.sh
./office-files.sh
./kde-templates.sh
./kde-files.sh
