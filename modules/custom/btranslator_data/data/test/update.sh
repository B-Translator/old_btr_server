#!/bin/bash

### go to the script directory
cd $(dirname $0)

### import test PO files
./import-pingus.sh
./import-kturtle.sh
#./import-kdeadmin.sh
#./import-office-desktop.sh
