#!/bin/bash

### go to the script directory
cd $(dirname $0)

### purge any data related to pingus
../import/purge-project.sh pingus

### import pingus data
../import/pingus.sh

### make another snapshot
../export/make_snapshot.sh misc pingus sq
../export/make_snapshot.sh misc pingus fr

### get the pingus diffs
../export/wget-diffs.sh misc pingus sq
../export/wget-diffs.sh misc pingus sq 1
../export/wget-diffs.sh misc pingus sq 2

