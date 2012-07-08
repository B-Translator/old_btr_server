#!/bin/bash

### go to the script directory
cd $(dirname $0)

### import test PO files
../import/purge-project.sh pingus
../import/purge-project.sh kturtle
#../import/purge-project.sh kdeadmin
#../import/purge-project.sh LibO-desktop
