#!/bin/bash

### go to the script directory
cd $(dirname $0)

### purge any data related to pingus
../import-scripts/purge-project.sh pingus

### import pingus data
../import-scripts/import-pingus.sh

### make another snapshot
../export-scripts/snapshot.sh misc pingus sq
../export-scripts/snapshot.sh misc pingus fr

### get the pingus diffs
../export-scripts/wget-diffs.sh misc pingus sq
../export-scripts/wget-diffs.sh misc pingus sq 1
../export-scripts/wget-diffs.sh misc pingus sq 2

