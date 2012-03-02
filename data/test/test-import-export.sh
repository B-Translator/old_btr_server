#!/bin/bash

### go to the script directory
cd $(dirname $0)

### purge any data related to pingus
../import/purge-project.sh pingus

### import pingus data
../import/pingus.sh

### get the pingus diffs
../export/wget-diffs.sh misc pingus sq
../export/wget-diffs.sh misc pingus sq 1
../export/wget-diffs.sh misc pingus sq 2

### re-import
../import/pingus.sh

### get the pingus diffs
../export/wget-diffs.sh misc pingus sq
../export/wget-diffs.sh misc pingus sq 3
../export/wget-diffs.sh misc pingus sq 4

### clean up
echo "
To clean run:  rm misc-pingus-sq*
"

