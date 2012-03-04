#!/bin/bash

### go to this directory
cd $(dirname $0)

### import all projects
./gnome.sh
./mozilla.sh
./ubuntu.sh
./office.sh
./kde.sh
./pingus.sh